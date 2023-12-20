import os
import argparse
import subprocess
import git
import platform
from colorama import Fore

def replace_forward_slashes(input_string):
    result_string = input_string.replace('/', '\\')
    return result_string

parser = argparse.ArgumentParser(prog="ConfigBuild",
                                 description="Configures and builds the project")
is_windows = "Windows" in platform.system()
move_cmd = "move" if is_windows else "mv"
python_interpreter = "python" if is_windows else "python3"

## !!!!!! CHANGE THIS PATH TO YOUR ST-LIB PATH !!!!!!
stlib_path = "C:/ST-LIB/tools/build.py" if is_windows else "/opt/ST-LIB/tools/build.py"
## !!!!!! CHANGE THIS PATH TO YOUR ST-LIB PATH !!!!!!


parser.add_argument('-bb','--build_behaviour',choices=['Release','Debug'],required=True)
parser.add_argument('-target','--target',choices=['NUCLEO','BOARD'],required=True)
parser.add_argument('-eth','--ethernet_config',choices=['ON','OFF'],required=True)
parser.add_argument('-f','--flash',choices=['True','False'],required=False)

args = parser.parse_args()

class ConfigBuild:
    def find_repo_root(self):
        current_directory = os.getcwd()
        repo = git.Repo(current_directory, search_parent_directories=True)
        git_root = repo.git.rev_parse("--show-toplevel")
        self.repo_root = git_root
    def __init__(self):
        self.buildconfig = args.build_behaviour
        self.target = args.target
        self.ethernet = args.ethernet_config
        if args.flash == None:
            self.flash = "False"
        else:
            self.flash = args.flash
        self.output_dir = self.buildconfig         
        self.find_repo_root()
        self.printConfiguration()
        self.args = []
    def find_file(self,search_path):
        for root, _, files in os.walk(search_path):
            for file in files:
                if file.endswith(".elf"):
                    return file

    def flash_target(self):
        location = self.repo_root + "/build/" + self.output_dir +"/bin/"
        file_name = self.find_file(location)
        print("File location: " + file_name)
        elf_src = location + file_name
        binary_target = location + file_name.strip(".elf") + ".bin"
        print(Fore.GREEN + "Elf name:\t" + elf_src)
        print("Binary target:\t" +binary_target +"\n\n" + Fore.YELLOW)

        ret = subprocess.call(["arm-none-eabi-objcopy","-O","binary", elf_src, binary_target ])
        if ret != 0:
            print(Fore.RED + "Error when calling arm-none-eabi-objcopy, check it is installed")
            raise Exception()
        print("Flashing the code to the target\n")
        ret2 = subprocess.call(["st-flash","write",binary_target,"0x8000000"])
        if ret2 != 0:
            print(Fore.RED + "Error when flashing to the board, check st-flash is installed")
            raise Exception()
        else:
            print("\nSuccessfully flashed the code to the target\n")
            print(Fore.LIGHTMAGENTA_EX + "\nStarting program execution\n")
            subprocess.call(["st-flash","reset"])

    def build(self):
        try:
            os.makedirs(self.repo_root + "/build/" + self.output_dir)
        except FileExistsError:
            pass

        output = self.repo_root + "/build/" + self.output_dir
        stlib = subprocess.call([python_interpreter,stlib_path, "-bb", self.buildconfig, "-t" , self.target, "-eth",self.ethernet])
        if stlib != 0:
            raise Exception("STLIB build failed")
        
        self.args.append("cmake")
        self.args.append(self.repo_root)
        self.args.append("-B")
        self.args.append(output)
        if self.buildconfig == "Release":
            self.args.append("-DRELEASE=TRUE")
        else:
            self.args.append("-DRELEASE=FALSE")
        if self.target == "BOARD":
            self.args.append("-DNUCLEO=FALSE")
        else:
            self.args.append("-DNUCLEO=TRUE")
        self.args.append("-G")
        self.args.append("Unix Makefiles")
        cmake_ret_val = subprocess.call(self.args)      
        if cmake_ret_val != 0:
            print(Fore.RED + "ERRORS OCCURED\n")
            raise Exception("error invoking cmake")                      
        threads = os.cpu_count()
        print( Fore.BLUE +  "\n\nCalling make with {} threads\n\n".format(threads))
        retval = subprocess.call(["make","-j",str(threads),"-C", output])
        if retval != 0:
            print(Fore.RED + "ERRORS OCCURED\n")
            raise Exception("error invoking make")
        
        print(Fore.GREEN + "\nBuild completed successfully!!\n" + Fore.YELLOW)
        try:
            os.makedirs(self.repo_root + "/build/" + self.output_dir + "/bin")
        except FileExistsError:
            pass
        elf_ori = self.repo_root + "/build/" + self.output_dir  + "/" + self.find_file(self.repo_root + "/build/" + self.output_dir)
        elf_dir = self.repo_root + "/build/" + self.output_dir + "/bin"
        if is_windows:
            elf_ori = replace_forward_slashes(elf_ori)
            elf_dir = replace_forward_slashes(elf_dir)
        if is_windows:
            subprocess.call([move_cmd,elf_ori,elf_dir],shell=True)
        else:
            subprocess.call([move_cmd,elf_ori,elf_dir])
        print("Flash value: " + str(self.flash))

        if self.flash == "False":
            self.printConfiguration()
            exit()
        else:
            self.flash_target()
            self.printConfiguration()

    def printConfiguration(self):
        print(Fore.CYAN +"\n\tConfiguration used:\n")
        print(Fore.CYAN +"\t\tBuild configuration: [DEBUG, RELEASE]: {} ".format(self.buildconfig).upper())
        print(Fore.CYAN +"\t\tTarget [BOARD,NUCLEO]: {} ".format(self.target))
        print(Fore.CYAN +"\t\tEthernet [ON,OFF]: {} \n\n".format(self.ethernet))          



obj = ConfigBuild()
obj.build()



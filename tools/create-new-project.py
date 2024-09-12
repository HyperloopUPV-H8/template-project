#!/usr/bin/python3
import os
import re
from typing import Union
import git
import argparse
import shutil

from git import Repo
from tqdm import tqdm
from colorama import Fore


class CloneProgress:
    operation_display = {
        git.RemoteProgress.COUNTING: {
            "description": "Counting       ",
            "units": "",
        },
        git.RemoteProgress.COMPRESSING: {
            "description": "Compressing    ",
            "units": "",
        },
        git.RemoteProgress.WRITING: {
            "description": "Writing        ",
            "units": "",
        },
        git.RemoteProgress.RECEIVING: {
            "description": "Receiving      ",
            "units": "",
        },
        git.RemoteProgress.RESOLVING: {
            "description": "Resolving      ",
            "units": "",
        },
        git.RemoteProgress.FINDING_SOURCES: {
            "description": "Finding Sources",
            "units": "",
        },
        git.RemoteProgress.CHECKING_OUT: {
            "description": "Checking Out   ",
            "units": "",
        },
    }

    def __init__(self):
        self.progress = None
        self.op_code = None
        self.prev_count = 0

    @property
    def _description(self):
        return self.operation_display[self.op_code]["description"]

    @property
    def _units(self):
        return self.operation_display[self.op_code]["units"]

    def __call__(self,
        op_code: int,
        cur_count: Union[str, float],
        max_count: Union[str, float, None] = None,
        _message: str = "",):

        if (self.op_code and (op_code & self.op_code) == 0):
            print("WARNING: Different OP Code received before an end")

        if (op_code & git.RemoteProgress.BEGIN != 0):
            self.op_code = op_code & 0b111111100
            self.current_progress = tqdm(
                desc=self._description,
                unit=self._units,
                total=float(max_count)
            )
            self.prev_count = 0
        
        self.current_progress.update(cur_count - self.prev_count)
        self.prev_count = cur_count

        if (op_code & git.RemoteProgress.END != 0):
            self.current_progress.close()
            self.op_code = None


# ----------------------
# Create argument parser
# ----------------------

parser = argparse.ArgumentParser(
    prog="Create New Project",
    description="Configures a new project from a template"
)

parser.add_argument(
    "project_name"
)
parser.add_argument(
    "-t",
    "--template",
    default="git@github.com:HyperloopUPV-H8/template-project.git",
    help="Original template project",
)
parser.add_argument(
    "-o",
    "--output_dir",
    default=os.getcwd(),
    help="Directory where the project will be created"
)
parser.add_argument(
    "--ioc",
    default="template-project.ioc",
    help="Name of the original template IOC file"
)

args = parser.parse_args()

project_path = os.path.join(args.output_dir, args.project_name)
if (os.path.isdir(project_path) and len(os.listdir(project_path)) != 0):
    print(Fore.RED + f"Output path {project_path} already contains files")
    print(Fore.RESET, end="")
    exit(1)

# --------------
# Clone template
# --------------

print(Fore.BLUE + f"Cloning template project:")
print(Fore.BLUE + f"\tRepository:  {args.template}")
print(Fore.BLUE + f"\tOutput path: {project_path}")
print(Fore.RESET)

try:
    template_project = Repo.clone_from(args.template, project_path, progress=CloneProgress());
    print()
except Exception as clone_error:
    print()
    print(Fore.RED + f"Failed to clone: {clone_error}")
    print(Fore.RESET, end="")
    exit(1)

# -------------
# Prepare files
# -------------

os.rename(
    os.path.join(project_path, args.ioc),
    os.path.join(project_path, f"{args.project_name}.ioc")
)

cmake_lists_path = os.path.join(project_path, "CMakeLists.txt")
with open(cmake_lists_path) as cmake_lists:
    template_cmake_lists = cmake_lists.read()

project_cmake_lists = re.sub(r"project *\( *[\w-]+ *ASM *C *CXX *\)", f"project({args.project_name} ASM C CXX)", template_cmake_lists)

with open(cmake_lists_path, "w") as cmake_lists:
    cmake_lists.write(project_cmake_lists)

# TODO: check if something else needs to be changed

# ---------------------------
# Create new project git repo
# ---------------------------

shutil.rmtree(os.path.join(project_path, ".git"))
new_project = Repo.init(project_path, mkdir=False)
new_project.index.add([os.path.join(project_path, "*")])
new_project.index.commit(f"Create {args.project_name} project")

print(Fore.GREEN + f"Successfuly created {args.project_name} project")
print(Fore.RESET, end="")
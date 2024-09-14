#!/usr/bin/python3
import os
import re
from typing import Union
import argparse
import shutil

# Requirements:
# git-python==1.0.3
# tqdm==4.66.5
# colorama==0.4.6
from git import Repo, RemoteProgress
from tqdm import tqdm
from colorama import Fore


class CloneProgress:
    operation_display = {
        RemoteProgress.COUNTING: {
            "description": "Counting       ",
            "units": "",
        },
        RemoteProgress.COMPRESSING: {
            "description": "Compressing    ",
            "units": "",
        },
        RemoteProgress.WRITING: {
            "description": "Writing        ",
            "units": "",
        },
        RemoteProgress.RECEIVING: {
            "description": "Receiving      ",
            "units": "",
        },
        RemoteProgress.RESOLVING: {
            "description": "Resolving      ",
            "units": "",
        },
        RemoteProgress.FINDING_SOURCES: {
            "description": "Finding Sources",
            "units": "",
        },
        RemoteProgress.CHECKING_OUT: {
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

        if (op_code & RemoteProgress.BEGIN != 0):
            self.op_code = op_code & 0b111111100
            self.current_progress = tqdm(
                desc=self._description,
                unit=self._units,
                total=float(max_count)
            )
            self.prev_count = 0
        
        self.current_progress.update(cur_count - self.prev_count)
        self.prev_count = cur_count

        if (op_code & RemoteProgress.END != 0):
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

def main(args: argparse.Namespace):
    project_path = os.path.join(args.output_dir, args.project_name)
    if (os.path.isdir(project_path) and len(os.listdir(project_path)) != 0):
        print(Fore.RED + f"Output path {project_path} already contains files")
        print(Fore.RESET, end="")
        return 1

    # --------------
    # Clone template
    # --------------

    print(Fore.BLUE + f"Cloning template project:")
    print(Fore.BLUE + f"\tRepository:  {args.template}")
    print(Fore.BLUE + f"\tOutput path: {project_path}")
    print(Fore.RESET)

    try:
        Repo.clone_from(args.template, project_path, progress=CloneProgress());
        print()
    except Exception as clone_error:
        print()
        print(Fore.RED + f"Failed to clone: {clone_error}")
        print(Fore.RESET, end="")
        return 1

    # -------------
    # Prepare files
    # -------------

    # IOC configuration
    os.rename(
        os.path.join(project_path, args.ioc),
        os.path.join(project_path, f"{args.project_name}.ioc")
    )

    # CMakeLists configuration
    cmake_lists_path = os.path.join(project_path, "CMakeLists.txt")
    with open(cmake_lists_path) as cmake_lists:
        template_cmake_lists = cmake_lists.read()

    project_cmake_lists = re.sub(r"project *\( *[\w-]+ *ASM *C *CXX *\)", f"project({args.project_name} ASM C CXX)", template_cmake_lists)

    with open(cmake_lists_path, "w") as cmake_lists:
        cmake_lists.write(project_cmake_lists)

    # VSCode workspace configuration
    vscode_workspace_path = os.path.join(project_path, "template-project.code-workspace")
    with open(vscode_workspace_path) as vscode_workspace:
        template_vscode_workspace = vscode_workspace.read()

    stlib_path = os.environ.get('STLIB_PATH')
    if stlib_path:
        project_vscode_workspace = re.sub(
            r"\"name\"\s*:\s*\"ST-LIB\"\s*,\s*\"path\"\s*:\s*\".*\"",
            f"\"name\": \"ST-LIB\",\n\t\t\"path\": \"{stlib_path}\"",
            template_vscode_workspace
        )
    else:
        project_vscode_workspace = template_vscode_workspace
        print(Fore.YELLOW + "Couldn't find STLIB_PATH, VSCode code workspace needs to be manually configured")
        print(Fore.RESET)


    with open(os.path.join(project_path, f"{args.project_name}.code-workspace"), "w") as vscode_workspace:
        vscode_workspace.write(project_vscode_workspace)
    os.remove(vscode_workspace_path)

    # Remove this script from output
    os.remove(os.path.join(project_path, "tools", "create-new-project.py"))

    build_script_path = os.path.join(project_path, "tools", "build.py")
    with open(build_script_path) as build_script:
        template_build_script = build_script.read()
    
    project_build_script = re.sub(
        r"PROJECT_NAME[ \t]*=[ \t]*\"template-project\"",
        f"PROJECT_NAME = \"{args.project_name}\"",
        template_build_script
    )

    with open(build_script_path, "w") as build_script:
        build_script.write(project_build_script)

    # ---------------------------
    # Create new project git repo
    # ---------------------------

    shutil.rmtree(os.path.join(project_path, ".git"))
    new_project = Repo.init(project_path, mkdir=False)
    new_project.git.add(project_path, all=True)
    new_project.index.commit(f"Create {args.project_name} project")

    print(Fore.GREEN + f"Successfuly created {args.project_name} project")
    print(Fore.RESET, end="")

    return 0

if __name__ == "__main__":
    exit(main(parser.parse_args()))
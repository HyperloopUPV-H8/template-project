#!/usr/bin/python3
import importlib.util
import os
import argparse
import shutil
import subprocess
import sys

# Requirements:
# colorama==0.4.6
from colorama import Fore


parser = argparse.ArgumentParser(
    prog="ConfigBuild",
    description="Configures and builds the project"
)

parser.add_argument(
    '-bb',
    '--build_behaviour',
    choices=['Release', 'ReleaseDebug', 'Debug'],
    required=True
)
parser.add_argument(
    '-target',
    '--target',
    choices=['NUCLEO', 'BOARD'],
    required=True
)
parser.add_argument(
    '-eth',
    '--ethernet_config',
    choices=['ON', 'OFF'],
    required=True
)

stlib_path = os.environ.get('STLIB_PATH')

PROJECT_NAME = "template-project"


def find_project():
    current_path = os.getcwd()
    while current_path:
        for entry in os.listdir(current_path):
            if entry == "CMakeLists.txt":
                return current_path
        current_path, _ = os.path.split(current_path)
    raise "Not inside a project"

def main(args: argparse.Namespace):
    if not stlib_path:
        print(Fore.RED + "STLIB_PATH env variable is missing")
        print(Fore.RESET, end="")
        return 1

    # This can only be resolved at runtime due to the STLIB_PATH env variable 
    stlib_build_path = os.path.join(stlib_path, "tools", "build.py")
    stlib_build_spec = importlib.util.spec_from_file_location("stlib_build", stlib_build_path)
    stlib_build = importlib.util.module_from_spec(stlib_build_spec)
    stlib_build_spec.loader.exec_module(stlib_build)

    stlib_build_exit_code = stlib_build.main(argparse.Namespace(
        build_behaviour=args.build_behaviour,
        target=args.target,
        ethernet_config=args.ethernet_config,
    ))

    if stlib_build_exit_code != 0:
        return stlib_build_exit_code
    
    print()

    try:
        project_dir = find_project()
    except Exception as find_error:
        print(Fore.RED + f"Could not find project directory: {find_error}")
        print(Fore.RESET, end="")
        return 1

    print(Fore.BLUE + f"Building {PROJECT_NAME}:")
    print(Fore.BLUE + f"\tST-LIB path:     {stlib_path}")
    print(Fore.BLUE + f"\tTarget:          {args.target}")
    print(Fore.BLUE + f"\tBuild Behaviour: {args.build_behaviour}")
    print(Fore.BLUE + f"\tEthernet:        {args.ethernet_config}")
    print(Fore.RESET)

    output_dir = os.path.join(project_dir, "build")
    os.makedirs(output_dir, exist_ok=True)

    cmake_exit_code = subprocess.call([
        "cmake",
        project_dir,
        "-B", output_dir,
        f"-DRELEASE={args.build_behaviour}",
        f"-DNUCLEO={'TRUE' if args.target == 'NUCLEO' else 'FALSE'}",
        f"-DETHERNET={'TRUE' if args.ethernet_config == 'ON' else 'FALSE'}",
        "-G", "Unix Makefiles"
    ])

    if (cmake_exit_code != 0):
        print(Fore.RED, "\nCMake failed, aborted")
        print(Fore.RESET, end="")
        return cmake_exit_code

    make_exit_code = subprocess.call([
        "make",
        "-j", str(os.cpu_count()),
        "-C", output_dir
    ])

    if (make_exit_code != 0):
        print(Fore.RED + "\nMake failed, aborted")
        print(Fore.RESET, end="")
        return make_exit_code

    final_project_location = os.path.join(output_dir, args.build_behaviour)
    os.makedirs(final_project_location, exist_ok=True)
    shutil.copyfile(
        os.path.join(output_dir, f"{PROJECT_NAME}.elf"),
        os.path.join(final_project_location, f"{PROJECT_NAME}.elf")
    )
    shutil.copyfile(
        os.path.join(output_dir, f"{PROJECT_NAME}.elf"),
        os.path.join(output_dir, f"latest.elf")
    )

    print()
    print(Fore.GREEN + f"{PROJECT_NAME} built successfuly!")
    print(Fore.GREEN + f"\tOutput path:     {final_project_location}")
    print(Fore.GREEN + f"\tTarget:          {args.target}")
    print(Fore.GREEN + f"\tBuild Behaviour: {args.build_behaviour}")
    print(Fore.GREEN + f"\tEthernet:        {args.ethernet_config}")
    print(Fore.RESET, end="")

    return 0

if __name__ == "__main__":
    exit(main(parser.parse_args()))
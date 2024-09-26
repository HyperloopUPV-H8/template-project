# Template Project

HyperloopUPV's Template project for STM32 development with LwIP.

Designed using CMake with defaults for development with VSCode.

## Requirements

* [CMake](https://cmake.org/download/)
* [STM32CubeCTL](https://www.st.com/en/development-tools/stm32cubeclt.html#get-software)

## Creating a new project from the template

The template project ships with a python script inside `tools` called `create-new-project.py` which does what the name implies.

This script will create a new project with the name the user provides already configured and ready to go using VSCode.

There are a few extra options, all with default values:

* `-o`, `--output_dir`: Specify the directory where the project will be created (defaults to the current directory)
* `-t`, `--template`: Specify the git repository from where to clone the template
* `--ioc`: Specify the name of the template `.ioc` file used for code generation

It is also advised to have preconfigured the `STLIB_PATH` env variable beforehand, this way the project will include a ready to go VSCode code workspace.

# Template Project

HyperloopUPV's Template project for STM32 development with LwIP.

Designed using CMake with defaults for development with VSCode.

## Requirements

* [Podman](https://podman.io)

## Creating a new project from the template

The template project ships with a python script inside `tools` called `create-new-project.py` which does what the name implies.

This script will create a new project with the name the user provides already configured and ready to go using VSCode and Dev Containers extension.

There are a few extra options, all with default values:

* `-o`, `--output_dir`: Specify the directory where the project will be created (defaults to the current directory)
* `-t`, `--template`: Specify the git repository from where to clone the template
* `--ioc`: Specify the name of the template `.ioc` file used for code generation

## Setup
To use it you must install [Dev Containers Visual Studio Code extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) and [Podman](https://podman.io) (you can try to use docker, but it hasn't been tested), and set dev containers extension to use Podman (you can see how [here](https://code.visualstudio.com/remote/advancedcontainers/docker-options#_podman)). 
Then, you must configure podman machine to increase memory (by default is 2GB) to 4 - 8 GB (the more the better). This step can be done through the GUI or using command line like this: 
```sh
podman machine stop
podman machine set --cpus 2 --memory 4096
podman machine start
```

## Notes
If you are going to develop OUTSIDE the container, you MUST change `template-project.code-workspace` file after project creation if you DON'T have STLIB on ../ST-LIB relative path. This template is intended for you to develop always inside the container, so you should not be concerned about this.
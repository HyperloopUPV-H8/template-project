FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-24.04
RUN apt-get update && apt-get -y install git
RUN mkdir -p /workspaces/ST-LIB && chown vscode:vscode /workspaces/ST-LIB
USER vscode
RUN git clone https://github.com/HyperloopUPV-H8/ST-LIB.git /workspaces/ST-LIB
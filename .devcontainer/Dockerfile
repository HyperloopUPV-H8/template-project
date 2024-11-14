FROM ubuntu:24.04

# Install git, git-lfs, pip and colorama, and create workspace directory
RUN curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | bash && \
    apt-get update && apt-get -y install git git-lfs python3-colorama cmake && \
    git lfs install && \
    mkdir -p /workspaces/ST-LIB

# Install cubeclt
RUN mkdir /temp && cd /temp && git clone https://github.com/HyperloopUPV-H8/cubeclt.git && \
    cd cubeclt && git lfs pull && chmod +x cubeclt_1.16.0_installer.sh && \
    echo | LICENSE_ALREADY_ACCEPTED=1 ./cubeclt_1.16.0_installer.sh

# Clone and config ST-LIB
RUN git clone https://github.com/HyperloopUPV-H8/ST-LIB.git /workspaces/ST-LIB
ENV STLIB_PATH=/workspaces/ST-LIB
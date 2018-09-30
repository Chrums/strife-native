# Container for building and testing cmake-examples with default cmake v3.5.1
FROM ubuntu
MAINTAINER Jake Chrumka, Michael Schroder

RUN apt-get update && apt-get install -y \
    build-essential \
    sudo \
    cmake \
    libboost-all-dev \
    libprotobuf-dev \
    protobuf-compiler \
    clang \
    clang-format \
    ninja-build \
    wget \
    git \
    nodejs \
    python-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
    && pip install conan
    
RUN conan remote add public-conan https://api.bintray.com/conan/bincrafters/public-conan

WORKDIR /home/environment

CMD ["/bin/bash"]
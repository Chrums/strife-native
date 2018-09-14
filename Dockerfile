# Container for building and testing cmake-examples with default cmake v3.5.1
FROM ubuntu
MAINTAINER Michael Schroder

RUN apt-get update && apt-get install -y build-essential \
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
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

VOLUME ["/home/ec2-user/environment"]

RUN chmod +x /home/ec2-user/environment/build.sh

CMD ["/bin/bash"]
ENTRYPOINT ["/home/ec2-user/environment/setup.sh"]
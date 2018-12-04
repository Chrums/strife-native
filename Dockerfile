# Container for building and testing cmake-examples with default cmake v3.5.1
FROM ubuntu
MAINTAINER Jake Chrumka, Michael Schroder

# Install dependencies...
RUN apt-get update && apt-get install -y \
    gnupg \
    ca-certificates \
    build-essential \
    sudo \
    cmake \
    curl \
    default-jre \
    clang \
    clang-format \
    wget \
    git \
    nodejs \
    python2.7 \
    python-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
    && pip install conan

WORKDIR /home


# Install Emscripten...

ARG EMSDK_ROOT=/home/emsdk

RUN git clone https://github.com/juj/emsdk.git \
    && ./emsdk/emsdk install latest \
    && ./emsdk/emsdk activate latest
    
# Build Boost

ARG BOOST_LINK=https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2
ARG BOOST_ROOT=/home/boost
ARG BOOST_LIBS=system,filesystem

RUN mkdir -p boost \
    && cd boost \
    && wget ${BOOST_LINK} -O ./boost.tar.bz2 \
    && tar --bzip2 -xf ./boost.tar.bz2 --strip-components 1 \
    && ./bootstrap.sh --with-libraries=${BOOST_LIBS} \
    && /bin/bash -c "source ${EMSDK_ROOT}/emsdk_env.sh && ./b2 toolset=emscripten"
    
WORKDIR /home/environment

CMD ["/bin/bash"] #&& source ${EMSDK_ROOT}/emsdk_env.sh"]
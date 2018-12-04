#!/bin/bash

set -e

source /home/emsdk/emsdk_env.sh
mkdir -p build
pushd build
emcmake cmake -DCMAKE_BUILD_TYPE=DEBUG -DBOOST_ROOT=/home/boost ..
emmake make
node main.js
popd
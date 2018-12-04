#!/bin/bash

set -e

if [[ $* == *--emscripten* ]]
then
    source /home/emsdk/emsdk_env.sh
    build="emcmake cmake"
    compile="emmake make"
    run="node main.js"
else
    build="cmake"
    compile="make"
    run="./main"
fi

mkdir -p build
pushd build
eval $build -DCMAKE_BUILD_TYPE=DEBUG -DBOOST_ROOT=/home/boost ..
eval $compile
eval $run
popd
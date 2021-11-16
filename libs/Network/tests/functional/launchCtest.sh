#!/bin/bash

DIR=$( basename `pwd` )

if [[ "$DIR" != "build" ]]; then
   mkdir -p build && cd build
fi

if [[ $1 == "conan" ]]; then
    CONAN_PROFILE="default"
    if (( $# >= 2 )); then
        CONAN_PROFILE=$2
    fi
    conan install .. -pr "$CONAN_PROFILE"
fi

find . -name "CMakeCache\.txt" -type f -delete

export CXX=clang++

cmake .. && make -j 10

ctest
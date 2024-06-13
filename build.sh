#!/bin/sh

set -xe

mkdir -p ./bin/
cc -Wall -Wextra -ggdb -o ./bin/main main.c
clang -Wall -Wextra --target=wasm32 --include-directory=/opt/homebrew/Cellar/llvm/18.1.6/include/c++/v1 -o wasm.o -c ./wasm.c
wasm-ld -m wasm32 --no-entry --export-all --allow-undefined -o wasm.wasm wasm.o

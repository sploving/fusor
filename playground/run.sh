#!/bin/sh
clang++ -Xclang -load -Xclang /root/fusor/build/data_fusor/libEncodingPass.so $1 -o bin 
clang++ -S -emit-llvm -Xclang -load -Xclang /root/fusor/build/data_fusor/libEncodingPass.so $1 -o bin.ll

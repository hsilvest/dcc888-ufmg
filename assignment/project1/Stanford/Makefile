clang -c -emit-llvm Treesort.c -o Treesort.bc
opt -load Bc2Opt.so -bc2opt -disable-output Treesort.bc

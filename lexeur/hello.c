//
// Created by Clement on 2019-01-21.
//
#include "string.h"
#include "library.c"

uint64_t main(uint64_t argc, uint64_t *argv){
    init_library();
    printf1("%s\n", "Hello world 2");
}
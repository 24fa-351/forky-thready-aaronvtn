#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    printf("Hello world!");
    int num_things = atoi(argv[1]);
    int pattern_num = atoi(argv[2]);


    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    int things = atoi(argv[1]);
    int pattern = atoi(argv[2]);
    int random;
    srand(time(NULL));

    printf("Pattern %d:\n** Pattern %d: creating %d processes\n", pattern, pattern, things);

    pid_t pids[things];

    for (int ix = 0; ix < things; ix++) {
        int random = (rand() % 8) + 1;
        pids[ix] = fork();
    
        if (pids[ix] == 0) {
            printf("Process %d (pid %d) created: will sleep for %d seconds\n", ix, getpid(), random);
            sleep(random);
            exit(EXIT_SUCCESS);
        } else if (pids[ix] > 0) {
            printf("Parent: created child %d (pid %d)\n", ix, pids[ix]);
        } else {
            perror("Fork failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int ix = 0; ix < things; ix++) {
        int status;
        waitpid(pids[ix], &status, 0);
        if(WIFEXITED(status)) {
            printf("Process %d (pid: %d): exiting\n", ix, pids[ix]);
        }
    }

    printf("Pattern %d: All children have exited\n", pattern);

    // Pattern 2

    printf("Pattern 2:\n** Pattern 2: creating %d processes\n", things);
    pid_t pid2;

    for (int ix = 0; ix < things; ix++) {
        int random = (rand() % 8) + 1;
        pid2 = fork();
    
        if (pid2 < 0) {
            perror("Fork failed\n");
            exit(EXIT_FAILURE);
        } else if (pid2 > 0) {
            printf("Child %d (pid %d): starting %d seconds after creating child %d (pid %d)\n", ix, getpid(), random, ix + 1, pid2);
            sleep(random);
            continue;
        } else {
            break;
        }
    }

    if (pid2 > 0) {
        wait(NULL);
        printf("Parent: child 0 (pid %d) has exiting\n** Pattern 2: All children have exited\n", pid2);
        }

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int num_args = argc;
    
    char *args[num_args];
    
    for (int idx = 0; idx != num_args; ++idx) {
        args[idx] = argv[idx];
    }
    
    args[num_args] = NULL;


    pid_t child_pid = fork();
    
    if (child_pid == 0) {
        execv("./sort", args);
    } else if (child_pid > 0) {
        wait(NULL);
        execv("./oddeven", args);
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t childer_pid, nati1_pid1, nati2_pid2, nati3_pid3;

    
    printf("1. Parent process ID: %d\n", getpid()); //parent process er jnno

    childer_pid = fork(); //child process banalam

    if (childer_pid < 0) {
        perror("Fork failed for child");
        exit(1);
    }

    if (childer_pid == 0) {
        // child process er vetor
        printf("2. Child process ID: %d\n", getpid());

        // first nati banalam
        nati1_pid1 = fork();
        if (nati1_pid1 == 0) {
            printf("3. Grand Child process ID: %d\n", getpid());
            exit(0); // First nati ber hoye gelo
        }

        // first nati sesh hobe tai waiting 
        wait(NULL);

        // second nati banalam
        nati2_pid2 = fork();
        if (nati2_pid2 == 0) {
            printf("4. Grand Child process ID: %d\n", getpid());
            exit(0); // Second nati ber hoye gelo
        }

        // second nati sesh hobe tai waiting 
        wait(NULL);

        // third nati banalam
        nati3_pid3 = fork();
        if (nati3_pid3 == 0) {
            printf("5. Grand Child process ID: %d\n", getpid());
            exit(0); 
        }

        wait(NULL);

        // Child process ber hoy jokhon sob nati done
        exit(0);
    } else {
        // Parent process wait kortese for the child process
        wait(NULL);
    }

    return 0;
}


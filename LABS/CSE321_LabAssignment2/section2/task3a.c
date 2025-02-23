#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global counter 
int process_count = 1; // initial parent process er jnno 1

void check_and_create_child(pid_t pid) {
    if (pid % 2 != 0) {
        pid_t new_child = fork(); //  odd hole notun create
        if (new_child < 0) {
            perror("Fork failed");
            exit(1);
        } else if (new_child == 0) {
            // In the new child process
            exit(0); 
        } else {
            process_count++;
            wait(NULL); 
        }
    }
}

int main() {
    pid_t original_parent_pid = getpid(); 
    pid_t a, b, c;

    
    a = fork();
    if (a < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (a > 0) process_count++; 

    if (a == 0) {
        check_and_create_child(getpid());
    }

   
    b = fork();
    if (b < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (b > 0) process_count++;

    if (b == 0) {
        check_and_create_child(getpid());
    }


    c = fork();
    if (c < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (c > 0) process_count++; 

    if (c == 0) {
        check_and_create_child(getpid());
    }


    while (wait(NULL) > 0);


    if (getpid() == original_parent_pid) {
        printf("Total number of processes created: %d\n", process_count);
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child, grandchild;

    
    child = fork();//first baccha create

    if (child < 0) {
        perror("Fork failed for child");
        exit(1);
    }

    if (child == 0) { 
        //child process er vetore ebar
        grandchild = fork(); // baccha r baccha create

        if (grandchild < 0) {
            perror("Fork failed for grandchild");
            exit(1);
        }

        if (grandchild == 0) {
            // grandchild er vetore ebar
            printf("I am grandchild\n");
            exit(0); // grandchild theke ber hoye gelam
        } else {
            // child process er vetor grandchild er jnno wait krchi
            wait(NULL); 
            printf("I am child\n");
            exit(0); //  child process theke ber hoye gelam
        }
    } else {
        // parent process er vetor child er wait krchi
        wait(NULL); 
        printf("I am parent\n");
    }

    return 0;
}


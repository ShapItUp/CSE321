#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

struct shared {
    char sel[100];
    int balance;
};

int main() {
    pid_t pid;
    int pipefd[2];
    struct shared *shm;
    int shared_id_memory;
    char buff[200];
    int amount;

    
    shared_id_memory= shmget((key_t)8461, sizeof(struct shared), 0666 | IPC_CREAT);
    if (shared_id_memory == -1) {
        perror("shmget");
        exit(1);
    }
    shm = (struct shared *)shmat(shared_id_memory, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    
    shm->balance = 1000;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }


    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        close(pipefd[1]);  
        read(pipefd[0], buff, sizeof(buff)); 
        close(pipefd[0]);  

        switch (buff[0]) {
            case 'a':
                printf("Enter amount to be added:\n");
                fgets(buff, sizeof(buff), stdin);
                amount = atoi(buff);
                if (amount > 0) {
                    shm->balance += amount;
                    printf("Balance added successfully\n");
                    printf("Updated balance after addition: %d\n", shm->balance);
                } else {
                    printf("Adding failed, Invalid amount\n");
                }
                break;
            case 'w':
                printf("Enter amount to be withdrawn:\n");
                fgets(buff, sizeof(buff), stdin);
                amount = atoi(buff);
                if (amount > 0 && amount <= shm->balance) {
                    shm->balance -= amount;
                    printf("Balance withdrawn successfully\n");
                    printf("Updated balance after withdrawal: %d\n", shm->balance);
                } else {
                    printf("Withdrawal failed, Invalid amount\n");
                }
                break;
            case 'c':
                printf("Your current balance is: %d\n", shm->balance);
                break;
            default:
                printf("Invalid selection\n");
                break;
        }

        strcpy(buff, "Thank you for using\n");
        write(pipefd[1], buff, strlen(buff) + 1);
        close(pipefd[1]); 

        shmdt(shm);

        exit(0);
    } else {
        close(pipefd[0]);  

        printf("Provide Your Input From Given Options:\n");
        printf("1. Type a to Add Money\n");
        printf("2. Type w to Withdraw Money\n");
        printf("3. Type c to Check Balance\n");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = '\0';  

        
        strcpy(shm->sel, buff);
        printf("Your selection: %s\n", shm->sel);

        
        write(pipefd[1], shm->sel, strlen(shm->sel) + 1);
        close(pipefd[1]); 

        wait(NULL);

        memset(buff, 0, sizeof(buff));

        
        read(pipefd[0], buff, sizeof(buff));
        close(pipefd[0]);  
        printf("%s", buff);

        
        shmdt(shm);
        shmctl(shared_id_memory, IPC_RMID, NULL);
	printf("Thank you for using.\n");

    }

    return 0;
}




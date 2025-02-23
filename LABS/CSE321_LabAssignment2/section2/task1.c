#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;                 
    char input[1024];       // user input er jonno buffer nilam
    ssize_t p;  // `write` system call er jonno return value 

    
    if (argc != 2) { // file name disi kina check krbo
        printf("Error: Provide the file name as a command-line argument.\n");
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    
    printf("Opening or creating the file '%s'...\n", argv[1]); //append e file create krbo 
    fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error: Could not open the file");
        return 1;
    }

    printf("File '%s' opened/created successfully.Now enter strings.\n", argv[1]);
    printf("Enter '-1' to stop entering strings.\n");

    
    while (1) { //user input dibo
        printf("Enter a string: ");
        fgets(input, sizeof(input), stdin);       
        input[strcspn(input, "\n")] = '\0';      

        
        if (strcmp(input, "-1") == 0) { //-1 dile terminate hoye jabe
            printf("Exiting input loop. Closing the file...\n");
            break;
        }

   
        p = write(fd, input, strlen(input));
        if (p < 0) {
            perror("Error: Failed to write to the file");
            close(fd);
            return 1;
        }

        write(fd, "\n", 1);
        printf("String '%s' written to the file successfully.\n", input);
    }


    if (close(fd) == 0) {
        printf("File '%s' closed successfully.\n", argv[1]);
    } else {
        perror("Error: Could not close the file");
    }

    return 0;
}


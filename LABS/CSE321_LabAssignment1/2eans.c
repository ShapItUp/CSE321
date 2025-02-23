
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char palindrome[100];

    printf("Enter a string: ");
    scanf("%s", palindrome);

 
    const char *leftt = palindrome;  //pointer making                  
    const char *rightt = palindrome + strlen(palindrome) - 1; 
    while (leftt < rightt) {
        char startingChar = tolower(*leftt);   
        char endingChar = tolower(*rightt);   

        if (startingChar == endingChar) {       
            leftt=leftt+1;                      
            rightt=rightt-1;                     
        } else {                          
            printf("Not palindrome\n");
            return 0;                     
        }
    }


    printf("Palindrome\n");
    return 0;
}



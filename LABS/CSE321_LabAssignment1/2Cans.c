#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main() {
    char pass[100];
    int len;
    bool Lower_ones = false, Upper_ones = false, Digit_nums = false, Special_ones = false;
    printf("Enter the password here: ");
    scanf("%s", pass);
    len = strlen(pass);

    for (int i = 0; i<len; i++) {
        if (islower(pass[i])) {
            Lower_ones = true;
        } else if (isupper(pass[i])) {
            Upper_ones = true;
        } else if (isdigit(pass[i])) {
            Digit_nums = true;
        } else if (strchr("_$#@", pass[i])) {
            Special_ones = true;
        }
    }



if (Lower_ones && Upper_ones  && Digit_nums && Special_ones) {
    printf("OK\n");
    return 0;
}


if (!Lower_ones) 
    printf("Lowercase character missing\n");

if (!Upper_ones) 
    printf("Uppercase character missing\n");

if (!Digit_nums) 
    printf("Digit missing\n");

if (!Special_ones) 
    printf("Special character missing\n");

return 0;
}


#include <stdio.h>
#include <string.h>

int main() {
    char email[100];

    printf("Enter the email: ");
    scanf("%s", email);
  
    char *domain;
    domain= strchr(email, '@');

    if (domain != NULL) {
        if (strstr(domain, "@sheba.xyz")) {
            printf("Email address is okay\n");
        }
        else if (strstr(domain, "@kaaj.com")) {
            printf("Email address is outdated\n");
        }
        else {
            printf("Invalid email address\n");
        }
    } else {
        // Handle case where '@' is missing
        printf("Invalid email address\n");
    }

    return 0;
}


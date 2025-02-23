#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int string_to_int(char *number_str) {
    int result = 0;
    int is_neg = 1;
    int current_ind = 0;

    if (*number_str == '-') {
        is_neg = -1;
        ++current_ind;
    }

    for (; number_str[current_ind] != '\0'; current_ind++) {
        if (number_str[current_ind] < '0' || number_str[current_ind] > '9') {
            printf("Invalid number: %s\n", number_str);
            exit(1);
        }
        result = result * 10 + (number_str[current_ind] - '0');
    }

    return result * is_neg;
}


void check_odd_even(int array[], int total_numb) {
    for (int idx = 0; idx < total_numb; idx++) {
        if (array[idx] % 2 == 0) {
            printf("%d is even.\n", array[idx]);
        } else {
            printf("%d is odd.\n", array[idx]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide numbers as command line arguments.\n");
        return 1;
    }

    int total_numb = argc - 1; 
    int numbers_array[total_numb];


    for (int idx = 0; idx < total_numb; idx++) {
        numbers_array[idx] = string_to_int(argv[idx + 1]);
    }

    check_odd_even(numbers_array, total_numb);

    return 0;
}


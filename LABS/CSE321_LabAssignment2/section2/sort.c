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


void sort_descending(int array[], int total_numb) {
    for (int last_unsorted = total_numb - 1; last_unsorted > 0; last_unsorted--) {
        for (int current_post = 0, boundary = last_unsorted; current_post < boundary; current_post++) {
            if (array[current_post] < array[current_post + 1]) {
          
                int temporary = array[current_post];
                array[current_post] = array[current_post + 1];
                array[current_post + 1] = temporary;
            }
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


    for (int index = 0; index < total_numb; index++) {
        numbers_array[index] = string_to_int(argv[index + 1]);
    }


    sort_descending(numbers_array, total_numb);


    printf("Sorted array in descending order: ");
    for (int index = 0; index < total_numb; index++) {
        printf("%d ", numbers_array[index]);
    }
    printf("\n");

    return 0;
}


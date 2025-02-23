#include <stdio.h>

int main() {
    int inputt1, inputt2, total_result;
    printf("Entering Both the numbers: ");
    scanf("%d %d", &inputt1, &inputt2); 

    if (inputt1>inputt2) {
        total_result = inputt1 - inputt2; 
        printf("Subtraction result is: %d\n", total_result);
    } 
    else if (inputt1 < inputt2) {
        total_result = inputt1 + inputt2; 
        printf("Addition result is: %d\n",total_result);
    } 
    else {
        total_result = inputt1 * inputt2; 
        printf("Multiplication result is: %d\n", total_result);
    }

    return 0; 
}


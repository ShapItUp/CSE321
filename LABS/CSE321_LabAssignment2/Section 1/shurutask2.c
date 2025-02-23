#include <stdio.h>

struct Range {
    int lower;
    int upper;
};

int isPerfect(int num) {
    int sum_of_divisors = 0;
    int divisor = 1; //smallest divisor diye shuru krbo

    
    while (divisor < num) { //// sum of divisors ber krbo
        if (num % divisor == 0) {
            sum_of_divisors += divisor;
        }
        divisor++; // Increment krchi divisor ke
    }

    // Check korte hobe sum of divisors number er soman kina
    return sum_of_divisors == num;
}

int main() {
    struct Range range;
    int current_number; // Variable rakhlam for  storing the current number being checked

    // Input the range
    printf("Enter the lower limit: ");
    scanf("%d", &range.lower);
    printf("Enter the upper limit: ");
    scanf("%d", &range.upper);

    printf("Perfect numbers between %d and %d are:\n", range.lower, range.upper);

    // Iterate through the range using a do-while loop
    current_number = range.lower;
    do {
        if (isPerfect(current_number)) {
            printf("%d\n", current_number);
        }
        current_number++; // Increment the current number
    } while (current_number <= range.upper);

    return 0;
}


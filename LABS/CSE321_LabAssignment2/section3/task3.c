#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

#define Max_Length 100
#define num_user 3


typedef struct {
    char username[Max_Length];
    int id;
} UserData;


int ascii_total[num_user];


void *evaluate_comparison(void *para) {
    int *totals = (int *)para;
    int first, second, third;
    first = totals[0];
    second = totals[1];
    third = totals[2];


    if (first == second && second == third) {
        printf("Youreka\n");
    } else if (first == second || second == third || first == third) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n"); 
    }

    return NULL;
}


void *compute_ascii_total(void *para) {
    UserData *user_data = (UserData *)para;
    int ascii_sum = 0;
    char *username = user_data->username;


    int name_len = strlen(username);
    for (int i = 0; i < name_len;) {
        ascii_sum += (unsigned char)username[i];
        i += 1;  
    }

    printf("Thread %d computed ASCII sum: %d\n", user_data->id + 1, ascii_sum);
    pthread_exit((void *)(intptr_t)ascii_sum);  
}

int main() {
    pthread_t threads[num_user + 1];
    UserData user_data[num_user];


    for (int i = 0; i < num_user; i++) {
        printf("Please enter username %d: ", i + 1);
        if (fgets(user_data[i].username, Max_Length, stdin) != NULL) {
            size_t length = strlen(user_data[i].username);
            if (length > 0 && user_data[i].username[length - 1] == '\n') {
                user_data[i].username[length - 1] = '\0';  
            }
            user_data[i].id = i;
        } else {
            fprintf(stderr, "Error reading input.\n");
            return 1;
        }
    }


    for (int i = 0; i < num_user;) {
        pthread_create(&threads[i], NULL, compute_ascii_total, (void *)&user_data[i]);
        i += 1; 
    }

     for (int i = 0; i < num_user;) {
        void *result;
        pthread_join(threads[i], &result);
        ascii_total[i] = (int)(intptr_t)result;  
        i += 1;  
    }



    pthread_create(&threads[num_user], NULL, evaluate_comparison, (void *)ascii_total);


    pthread_join(threads[num_user], NULL);

    return 0;
}




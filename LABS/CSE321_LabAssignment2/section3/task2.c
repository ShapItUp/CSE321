#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function banalam
void *print_thenumbers(void *arg) {
    int thread_id = *(int *)arg; 
    for (int i = 0; i < 5; i++) {
        int num_print = thread_id * 5 + i + 1;  // loop er vetor calculation
        printf("Thread %d prints %d\n", thread_id, num_print);
    }

    return NULL; 
}


int main() {
    pthread_t threads[5];      
    int thread_ids[5];        
    
    // thread id assign and create
    int count = 0;
    for (int i = 0; i < 5; i++, count++) {
        thread_ids[i] = count; //
        pthread_create(&threads[i], NULL, print_thenumbers, &thread_ids[i]);
        pthread_join(threads[i], NULL);
       
    }

    return 0;
}


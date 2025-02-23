#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Thread function
void *thread_function(void *arg) { //thread function banalam
    int thread_id = *(int *)arg; 
    printf("thread-%d is running\n", thread_id);
    sleep(1); 
    printf("thread-%d is closed\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[5];   // thread id er jnno array
    int thread_ids[5];      

    // thread join korte hobe
    int count = 1;
    for (int i = 0; i < 5; i++, count++) {
        thread_ids[i] = count; // thread id assign krlam
        pthread_make(&threads[i], NULL, thread_function, &thread_ids[i]);
        pthread_join(threads[i], NULL); // ekta sesh hole arekta shuru hbe
    }

    return 0;
}


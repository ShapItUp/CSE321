#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 

#define MAX 10 
#define BUFLEN 6 
#define NUMTHREAD 2 

void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN];
char source[BUFLEN]; 
int pCount = 0;
int cCount = 0;
int buflen;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_id[NUMTHREAD] = {0, 1};
int i = 0;
int j = 0;

int main()
{
    int i;
    pthread_t thread[NUMTHREAD];
    strncpy(source, "abcdef",BUFLEN);
    source[BUFLEN ] = '\0'; 
    buflen = strlen(source);

    pthread_create(&thread[0], NULL, producer, (void *)&thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, (void *)&thread_id[1]);

    
    for (i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void *producer(void *id)
{
    int thread_id = *(int *)id;
    while (pCount < MAX) {
        pthread_mutex_lock(&count_mutex);

        while ((pCount - cCount) == BUFLEN) {
            pthread_cond_wait(&full, &count_mutex);
        }

        buffer[i] = source[pCount % buflen];
        printf("%d produced %c by Thread %d\n", pCount, buffer[i], thread_id);
        pCount++;
        i = (i + 1) % BUFLEN;

        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);

        sleep(1); 
    }
    pthread_exit(0);
}

void *consumer(void *id)
{
    int thread_id = *(int *)id;
    while (cCount < MAX) {
        pthread_mutex_lock(&count_mutex);

        while (pCount == cCount) {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        printf("%d consumed %c by Thread %d\n", cCount, buffer[j], thread_id);
        cCount++;
        j = (j + 1) % BUFLEN;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);

        sleep(1); 
    }
    pthread_exit(0);
}


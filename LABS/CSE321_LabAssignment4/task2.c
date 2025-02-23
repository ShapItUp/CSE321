#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxCrops 5 
#define warehouseSize 5 

sem_t empty;
sem_t full;
int in = 0;
int out = 0;

char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'}; 
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'}; 

pthread_mutex_t mutex;

void *Farmer(void *far) {
    int num_of_farmers = *(int *)far;
    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 

        // Critical section for farmers
        warehouse[in] = crops[in];
        printf("Farmer %d: Inserted crops %c at %d\n", num_of_farmers, crops[in], in);
        in = (in + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex); 
        sem_post(&full); 

        pthread_mutex_lock(&mutex);
        printf("Warehouse: ");
        for (int j = 0; j < warehouseSize; j++) {
            printf("%c ", warehouse[j]);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
    }
}

void *ShopOwner(void *sho) {
    int num_of_owners = *(int *)sho;
    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&full); 
        pthread_mutex_lock(&mutex); 

        // Critical section for shopowners
        char crop_here = warehouse[out];
        warehouse[out] = 'N';
        printf("Shop owner %d: Removed crops %c from %d\n", num_of_owners, crop_here, out);
        out = (out + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex); 
        sem_post(&empty); 

        pthread_mutex_lock(&mutex);
        printf("Warehouse: ");
        for (int j = 0; j < warehouseSize; j++) {
            printf("%c ", warehouse[j]);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize);
    sem_init(&full, 0, 0); 

    int a[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_create(&Far[i], NULL, Farmer, &a[i]);
        pthread_create(&Sho[i], NULL, ShopOwner, &a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}


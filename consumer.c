#include "table.h"

int main() {

    // shared is initialized in producer.c

    int shared = shm_open("/SharedMemory2", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shared == -1)
        printf("error on shm_open()\n");

    struct table *consumer;
    consumer = mmap(0, sizeof(struct table), PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0);
    if (consumer == MAP_FAILED)
        printf("error on mmap()\n");

    int turn = 0;
    while(turn < iteration) { // three iterations (defined in table.h)

        // if table is still full of 0, then producer hasn't finished, busy wait
        while(consumer->buffer[0] == 0 && consumer->buffer[1] == 0); 

        sleep(1);
        sem_wait(&consumer->filled);

        for (int i = 0; i < tableSize; ++i) {
            printf("consumer removed %d\n", consumer->buffer[i]);
            consumer->buffer[i] = 0; // 'reset' the removed number
        }
   
        ++turn;
        printf("turn number: %i\n", turn);
        sem_post(&consumer->empty);
        // printf("hello %i\n", turn);

    }
    
    return 0;
}
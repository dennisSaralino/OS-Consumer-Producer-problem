#include "table.h"
#include <errno.h>
#include <string.h>
    

int main(int argc, char* argv[]) {
    srand(time(NULL)); // random seed for project

    // create a shared memory location, give read and write access

    int shared = shm_open("/SharedMemory2", O_CREAT | O_RDWR, S_IXUSR | S_IRUSR | S_IWUSR);
    if (shared == -1)
        printf("error on shm_open()\n");
    printf("hello. %i\n", shared);
    printf("error: %i\n", errno);
    printf("error: %s\n", strerror(errno));

    if (ftruncate(shared, sizeof(struct table)) == -1)
        printf("error on ftruncate()");
    else
        ftruncate(shared, sizeof(struct table)); // resize shared memory


    struct table *producer;
    producer = mmap(0, sizeof(struct table), PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0); // get pointer to shared memory

    if (producer == MAP_FAILED)
        printf("error on mmap()");


    // Initialize semaphores and initial value of 0 for table

    sem_init(&(producer->empty), 1, tableSize);
    sem_init(&(producer->filled), 1, 0);

    for (int i = 0; i < tableSize; ++i) {
        producer->buffer[i] = 0;
    }


    int turn = 0;
    while (turn < iteration) { // three iterations (defined in table.h)
        
        // if table isn't zero, consumer isn't done consuming, busy wait
        while (producer->buffer[0] != 0 && producer->buffer[1] != 0);

        // printf("prod before crit");
        sleep(1);
        sem_wait(&producer->empty);

        int item;
        for (int i = 0; i < tableSize; ++i) {
            item = rand() % 100 + 1; // create item
            if (item == 0) { 
                item = 1;
            }
            producer->buffer[i] = item;
            printf("producer produced %d\n", item);
        }
        ++turn;

        sem_post(&producer->filled);
        printf("hello %i\n", turn);
    }
    
    return 0;
}
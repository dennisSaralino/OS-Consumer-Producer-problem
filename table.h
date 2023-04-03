#ifndef CS33211_TABLE_H
#define CS33211_TABLE_H

#include <sys/mman.h>
#include <sys/stat.h>      
#include <fcntl.h> 
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tableSize = 2;
int iteration = 3;

struct table {
    int   buffer[2];
    sem_t empty;
    sem_t filled;
};

#endif
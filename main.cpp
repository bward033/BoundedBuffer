#include<iostream>
#include<pthread.h>
#include<ctime>
#include <unistd.h>
#include "BoundedBuffer.hpp"

const int buf_size = 10;
BoundedBuffer *bf = new BoundedBuffer(buf_size);

int sum;

void* consume(void* v) {
    while(true) {
        char *s = (char *) bf->pop();
        if (s != NULL) std::cout << s << std::endl;
        sleep(2); // sleep for 2s
    }
    return NULL;
}

void* produce(void * v) {
    while(true) {
        time_t epoch;
        time(&epoch);
        bf->push((char *)ctime(&epoch));
        sleep(2); // sleep for 2s
    }
    return NULL;
}

int main()
{
    int num_threads = 10; 
    pthread_t t[num_threads];
    int mid = num_threads / 2;
    for( int i = 0; i < mid; i++ )
        pthread_create(&t[i], NULL, produce, NULL);
    for( int i = mid; i < num_threads; i++ )
        pthread_create(&t[i], NULL, consume, NULL);

    for (int i = 0; i < num_threads; i++)
        pthread_join(t[i], NULL);

    return 0;
}


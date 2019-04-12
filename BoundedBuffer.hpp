#ifndef __BoundedBuffer
#define __BoundedBuffer

#include<assert.h>
#include<pthread.h>

class BoundedBuffer {
    
public:
    BoundedBuffer( int limit );
    ~BoundedBuffer();
    void push( char *record );
    void *pop();
    int numItems();
    
private:
    char** _queue;
    int _oldest, _next;

    unsigned int _limit;
    pthread_mutex_t _mutex;
};

#endif //  __BoundedBuffer


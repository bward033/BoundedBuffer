#include "BoundedBuffer.hpp"
#include <iostream>

BoundedBuffer::BoundedBuffer( int limit ): _limit( limit ) 
{
    _queue = new char*[_limit];
    _oldest = _next = 0;
    pthread_mutex_init( &_mutex, NULL );
}

BoundedBuffer::~BoundedBuffer() {
    delete [] _queue;
}

int BoundedBuffer::numItems() {
    return _next - _oldest;
}

void BoundedBuffer::push( char *record ) 
{
    int status = pthread_mutex_lock( &_mutex );
    assert( status == 0 );
    //std::cout << "push" << std::endl;

    if (numItems() <= _limit) {
        _queue[_next++ % _limit] = record;
    }
    else {
    //    std::cerr << "NOPE! Queue full" << std::endl;
    }
    
    status = pthread_mutex_unlock( &_mutex );
    assert( status == 0 ); 
}

void *BoundedBuffer::pop() 
{
    char * record = NULL;
    int status = pthread_mutex_lock( &_mutex );
    assert( status == 0 );
    //std::cout << "pop" << std::endl;

    if (numItems() > 0) {
        record = _queue[_oldest++ % _limit];
    }
    else {
 //       std::cerr << "NOPE! Queue empty" << std::endl;
    }

    status = pthread_mutex_unlock( &_mutex );
    assert( status == 0 );
    return record;
}


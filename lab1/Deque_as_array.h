#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H

/******************************************
 * UW User ID:  z324liu
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 ******************************************/

#include "Exception.h"


class Deque_as_array {
private:
    int array_size;
    int*array;
    int ihead;
    int itail;
    int count;
    
public:
    Deque_as_array( int = 10 );
    ~Deque_as_array();
    
    int head() const;
    int tail() const;
    int size() const;
    bool empty() const;
    int capacity() const;
    
    void enqueue_head( int const & );
    void enqueue_tail( int const & );
    int dequeue_head();
    int dequeue_tail();
    void clear();
    
    
};

/**
 *  Deque_as_array constructor
 *  
 *  Construct a circular array of size n with properties of a double ended queue
 */
Deque_as_array::Deque_as_array( int n ):
array_size( std::max( 1, n ) ),
array( new int[array_size] ),
ihead( 0 ),
itail( 0 ),
count( 0 ) {
    // empty
}


Deque_as_array::~Deque_as_array() {
    delete[] array;
}


int Deque_as_array::size() const {
    return count;
}


int Deque_as_array::capacity() const {
    return array_size;
}

/**
 *  Checks if the queue is empty
 *
 *  Returns true if there are no elements in the array
 */
bool Deque_as_array::empty() const {
    return count == 0;
}

/**
 *  Returns the value at the head of the queue
 *
 *  Throws underflow exception if queue is empty
 */
int Deque_as_array::head() const {
    
    if ( !empty() ) {
        return array[(array_size + (ihead % array_size)) % array_size];
    } else {
        throw underflow();
    }

    return 0;     // This returns a default object
}

/**
 *  Returns the value at the tail of the queue
 *
 *  Throws underflow exception if queue is empty
 */
int Deque_as_array::tail() const {
    
    if ( !empty() ) {
        return array[(array_size + ((itail - 1) % array_size)) % array_size];
    } else {
        throw underflow();
    }
    
    return 0;     // This returns a default object
}

/**
 *  Adds the given element to the beginning of the queue
 *
 *  Throws overflow exception if the queue is full
 */
void Deque_as_array::enqueue_head( int const &obj ) {
    
    if ( count < array_size ) {
        array[(array_size + (--ihead % array_size)) % array_size] = obj;
        ++count;
    } else {
        throw overflow();
    }
}

/**
 *  Adds the given element to the end of the queue
 *
 *  Throws overflow exception if the queue is full
 */
void Deque_as_array::enqueue_tail( int const &obj ) {
    
    if ( count < array_size ) {
        array[((array_size + (itail++ % array_size)) % array_size) % array_size]
            = obj;
        ++count;
    } else {
        throw overflow();
    }
}

/**
 *  Removes and returns the first element of the queue
 *
 *  Throws underflow exception if the queue is empty
 */
int Deque_as_array::dequeue_head() {
    
    if ( !empty() ) {
        ++ihead;
        --count;
        return array[(array_size + ((ihead - 1) % array_size)) % array_size];
    } else {
        throw underflow();
    }
    
    return 0;     // This returns a default object
}

/**
 *  Removes and returns the last element of the queue
 *
 *  Throws underflow exception if the queue is empty
 */
int Deque_as_array::dequeue_tail() {
    
    if ( !empty() ) {
        --count;
        return array[(array_size + (--itail % array_size)) % array_size];
    } else {
        throw underflow();
    }
    
    return 0;     // This returns a default object
}

/**
 *  Clears the array by resetting head and tail counters to their original
 *  poisitions and set the count to 0
 */
void Deque_as_array::clear() {
    
    ihead = itail = 0;
    count = 0;
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
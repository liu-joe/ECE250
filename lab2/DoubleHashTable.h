#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
#include <iostream>

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
private:
    int count;
    int power;
    int array_size;
    T *array;
    state *array_state;
    
    int h1( T const & ) const; // first hash function
    int h2( T const & ) const; // second hash function
    
public:
    DoubleHashTable( int = 5 );
    ~DoubleHashTable();
    int size() const;
    int capacity() const;		
    bool empty() const;
    bool member( T const & ) const;
    T bin( int ) const;
    
    void print() const;
    
    void insert( T const & );
    bool remove( T const & );
    void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
    
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete[] array;
    delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    return count == 0;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    return ((static_cast<int> (obj) % array_size) + array_size) % array_size;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    return (((static_cast<int> (obj) / array_size) % array_size) + array_size) 
            % array_size;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    if ( count == array_size ) { return false; }
    
    int i = 0;
    int h1key = h1(obj);
    int h2key = h2(obj) + (h2(obj) + 1) % 2;
    
    for (int idx = 0; idx < array_size; ++idx) {
        if ( array[(h1key + idx * h2key) % array_size] == obj ) {
            if ( array_state[(h1key + idx * h2key) % array_size] == OCCUPIED) {
                return true;
            }
        }
    }
    return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    
    if ( array_state[n] == OCCUPIED ) {
        return array[n];
    }
    return T();

}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    
    if ( count == array_size ) { return ; }
    
    int i = 0;
    int h1key = h1(obj);
    int h2key = h2(obj) + (h2(obj) + 1) % 2;
    
    while (array_state[(h1key + i * h2key) % array_size] == OCCUPIED) {
        ++i;
    }
    std::cout << i << std::endl;
    array[(h1key + i * h2key) % array_size] = obj;
    array_state[(h1key + i * h2key) % array_size] = OCCUPIED;
    ++count;
    return ; 
    
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    if ( count == 0 ) { return false; }
    
    int h1key = h1(obj);
    int h2key = h2(obj) + (h2(obj) + 1) % 2;
    
    for (int idx = 0; idx < array_size; ++idx) {
        if ( array[(h1key + idx * h2key) % array_size] == obj ) {
            if ( array_state[(h1key + idx * h2key) % array_size] == OCCUPIED) {
                array_state[(h1key + idx * h2key) % array_size] = DELETED;
                --count;
                return true;
            } else {
                return false;
            }
        }
    }
    
    return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
}

template<typename T >
void DoubleHashTable<T >::print() const {
    for (int idx = 0; idx < array_size; ++idx) {
        std::cout << idx << " " << bin(idx) << std::endl;
    }
    return;
}

#endif
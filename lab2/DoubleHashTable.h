#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  z324liu
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2016
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

/*
 *  Return the number of elements in the hashtable
 */
template<typename T >
int DoubleHashTable<T >::size() const {
    return count;
}

/*
 *  Return the capacity of the hash table
 */
template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
}

/*
 *  Checks if the array is empty, return true if empty, return false otherwise
 */
template<typename T >
bool DoubleHashTable<T >::empty() const {
    return count == 0;
}

/*
 *  Returns the result of the first hash function, always positive
 */
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    return ((static_cast<int> (obj) % array_size) + array_size) % array_size;
}

/*
 *  Returns the result of the second hash function, always positive
 */
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    return (((static_cast<int> (obj) / array_size) % array_size) + array_size) 
            % array_size;
}

/*
 *  Checks if the obj exists within the hashtable, return true if it exists,
 *  and return false otherwise
 */
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    if ( count == 0 ) { return false; }
    
    
    // Get values of first and second hash function, and make sure that the
    // result of the second hash function is odd
    int h1key = h1(obj);
    int h2key = h2(obj) + (h2(obj) + 1) % 2;
    int i = 0;
    
    for (int idx = 0; idx < array_size; ++idx) {
        if ( array[(h1key + idx * h2key) % array_size] == obj ) {
            if ( array_state[(h1key + idx * h2key) % array_size] == OCCUPIED) {
                return true;
            } else if (array_state[(h1key + idx * h2key) % array_size] == EMPTY) {
                return false;
            }
        }
    }
    return false;
}

/*
 *  Returns the content of the specified bin
 */
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    
    if ( array_state[n] == OCCUPIED ) {
        return array[n];
    }
    return T();

}

/*
 *  Inserts the given object at index based on the results of the hash functions
 */
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    
    if ( count == array_size ) { 
        throw overflow();
        return ; 
    }
    
    // Get values of first and second hash function, and make sure that the
    // result of the second hash function is odd
    int h1key = h1(obj);
    int h2key = h2(obj) + (h2(obj) + 1) % 2;
    int i = 0;
    
    while (array_state[(h1key + i * h2key) % array_size] == OCCUPIED) {
        if (array[(h1key + i * h2key) % array_size] == obj) {
            return ;
        }
        ++i;
    }
    array[(h1key + i * h2key) % array_size] = obj;
    array_state[(h1key + i * h2key) % array_size] = OCCUPIED;
    ++count;
    return ; 
    
}

/*
 *  Removed the object from the hash table, return true if object removed,
 *  return false of the object is not in the table
 */
template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    if ( count == 0 ) { return false; }
    
    // Get values of first and second hash function, and make sure that the
    // result of the second hash function is odd
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

/*
 *  Clear the table by reseting all the array states to empty
 */
template<typename T >
void DoubleHashTable<T >::clear() {
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
}

/*
 *  Prints out the content of the hashtable
 */
template<typename T >
void DoubleHashTable<T >::print() const {
    for (int idx = 0; idx < array_size; ++idx) {
        std::cout << idx << " " << bin(idx) << std::endl;
    }
    return;
}

#endif
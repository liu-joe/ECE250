#ifndef QUADTREE_H
#define QUADTREE_H

/***************************************
 * UW User ID:  z324liu
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ***************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
private:
    Quadtree_node<T> *tree_root;
    int count;
    
public:
    Quadtree();
    ~Quadtree();
    
    // Accessors
    
    int size() const;
    bool empty() const;
    
    T min_x() const;
    T min_y() const;
    
    T max_x() const;
    T max_y() const;
    
    T sum_x() const;
    T sum_y() const;
    
    Quadtree_node<T> *root() const;
    bool member( T const &, T const & ) const;
    
    // Mutators
    
    void insert( T const &, T const & );
    void clear();
    
    
};

template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
    // empty constructor
}

template <typename T>
Quadtree<T>::~Quadtree() {
}

template <typename T>
int Quadtree<T>::size() const {
    return 0;
}

template <typename T>
bool Quadtree<T>::empty() const {
    return true;
}

template <typename T>
T Quadtree<T>::min_x() const {
    return T();
}

template <typename T>
T Quadtree<T>::min_y() const {
    return T();
}

template <typename T>
T Quadtree<T>::max_x() const {
    return T();
}

template <typename T>
T Quadtree<T>::max_y() const {
    return T();
}

template <typename T>
T Quadtree<T>::sum_x() const {
    return T();
}

template <typename T>
T Quadtree<T>::sum_y() const {
    return T();
}

template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
    return 0;
}

template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
    return false;
}

template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {
}

template <typename T>
void Quadtree<T>::clear() {
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
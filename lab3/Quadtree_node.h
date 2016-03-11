#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/****************************************
 * UW User ID:  z324liu
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "ece250.h"

template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {
private:
    T       x_value;
    T       y_value;
    
    Quadtree_node *north_west;
    Quadtree_node *north_east;
    Quadtree_node *south_west;
    Quadtree_node *south_east;
    
public:
    Quadtree_node( T const & = T(), T const & = T() );
    
    T retrieve_x() const;
    T retrieve_y() const;
    
    Quadtree_node *nw() const;
    Quadtree_node *ne() const;
    Quadtree_node *sw() const;
    Quadtree_node *se() const;
    
    T min_x() const;
    T min_y() const;
    
    T max_x() const;
    T max_y() const;
    
    T sum_x() const;
    T sum_y() const;
    
    bool member( T const &, T const & ) const;
    
    bool insert( T const &, T const & );
    void clear();
    
    friend class Quadtree<T>;
};

template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
    // empty constructor
}

template <typename T>
T Quadtree_node<T>::retrieve_x() const {
    return x_value;
}

template <typename T>
T Quadtree_node<T>::retrieve_y() const {
    return y_value;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
    return north_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
    return north_east;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
    return south_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
    return south_east;
}

template <typename T>
T Quadtree_node<T>::min_x() const {
    // you may use std::min
    return T();
}

template <typename T>
T Quadtree_node<T>::min_y() const {
    // you may use std::min
    return T();
}

template <typename T>
T Quadtree_node<T>::max_x() const {
    // you may use std::max
    return T();
}

template <typename T>
T Quadtree_node<T>::max_y() const {
    // you may use std::max
    return T();
}

template <typename T>
T Quadtree_node<T>::sum_x() const {
    if ( this == 0 ) {
        // hint...
        return 0;
    } else {
        return 0;
    }
}

template <typename T>
T Quadtree_node<T>::sum_y() const {
    if ( this == 0 ) {
        // hint...
        return 0;
    } else {
        return 0;
    }
}

template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
    if ( this == 0 ) {
        return false;
    }
    
    return false;
}

template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
    return false;
}

template <typename T>
void Quadtree_node<T>::clear() {
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
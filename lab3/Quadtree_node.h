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
    if ( north_west == 0 ) {
        if ( south_west == 0 ) {
            return x_value;
        } else {
            return north_west->min_x();
        }
    } else {
        if ( south_west == 0 ) {
            return north_west->min_x();
        } else {
            return std::min(north_west->min_x(), south_west->min_x());
        }
    }
}

template <typename T>
T Quadtree_node<T>::min_y() const {
    if ( south_west == 0 ) {
        if ( south_east == 0 ) {
            return y_value;
        } else {
            return south_east->min_y();
        }
    } else {
        if ( south_east == 0 ) {
            return south_west->min_y();
        } else {
            return std::min(south_west->min_y(), south_east->min_y());
        }
    }
}

// TODO: fix the max values
template <typename T>
T Quadtree_node<T>::max_x() const {
    if ( north_east == 0 ) {
        if ( south_east == 0 ) {
            return x_value;
        } else {
            return south_east->max_x();
        }
    } else {
        if ( south_east == 0 ) {
            return north_east->max_x();
        } else {
            return std::max(north_east->max_x(), south_east->max_x());
        }
    }
}

template <typename T>
T Quadtree_node<T>::max_y() const {
    //T max = std::max(north_east->max_y(), north_west->max_y());
    if ( north_west == 0 ) {
        if ( north_east == 0 ) {
            return y_value;
        } else {
            return north_east->max_y();
        }
    } else {
        if ( north_east == 0 ) {
            return north_west->max_y();
        } else {
            return std::max(north_west->max_y(), north_east->max_y());
        }
    }
    return T();
}

template <typename T>
T Quadtree_node<T>::sum_x() const {
    if ( this == 0 ) {
        return 0;
    } else {
        T sum = 0;
        sum += north_east->sum_x();
        sum += south_east->sum_x();
        sum += south_west->sum_x();
        sum += north_west->sum_x();
        sum += x_value;
        return sum;
    }
}

template <typename T>
T Quadtree_node<T>::sum_y() const {
    if ( this == 0 ) {
        return 0;
    } else {
        T sum = 0;
        sum += north_east->sum_y();
        sum += south_east->sum_y();
        sum += south_west->sum_y();
        sum += north_west->sum_y();
        sum += y_value;
        return sum;
    }
}

template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
    
    if ( x_value == x && y_value == y) {
        return true;
    }
    
    if ( x_value <= x ) { 
        if ( y_value <= y ) {
            if ( north_east == 0 ) {
                return false;
            } else {
                return north_east->member(x, y);
            }
        } else {
            if ( south_east == 0 ) {
                return false;
            } else {
                return south_east->member(x, y);
            }
        }
    } else {
        if ( y_value <= y ) {
            if ( north_west == 0 ) {
                return false;
            } else {
                return north_west->member(x, y);
            }
        } else {
            if ( south_west == 0) {
                return false;
            } else {
                return south_west->member(x, y);
            }
        }
    }
}

template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
    
    if ( x_value == x && y_value == y) {
        return false;
    }
    
    if ( x_value <= x ) {
        if ( y_value <= y ) {
            if ( north_east == 0 ) {
                north_east = new Quadtree_node<T>(x, y);
            } else {
                return north_east->insert(x, y);
            }
        } else {
            if ( south_east == 0 ) {
                south_east = new Quadtree_node<T>(x, y);
            } else {
                return south_east->insert(x, y);
            }
        }
    } else {
        if ( y_value <= y ) {
            if ( north_west == 0 ) {
                north_west = new Quadtree_node<T>(x, y);
            } else {
                return north_west->insert(x, y);
            }
        } else {
            if ( south_west == 0 ) {
                south_west = new Quadtree_node<T>(x, y);
            } else {
                return south_east->insert(x, y);
            }
        }
    }
    return true;
}

template <typename T>
void Quadtree_node<T>::clear() {
    if ( north_east != 0 ) {
        north_east->clear();
        delete north_east;
    }
    if ( north_west != 0 ) {
        north_west->clear();
        delete north_west;
    }
    if ( south_east != 0 ) {
        south_east->clear();
        delete south_east;
    }
    if ( south_west != 0 ) {
        south_west->clear();
        delete south_west;
    }
    north_east = 0;
    north_west = 0;
    south_east = 0;
    south_west = 0;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
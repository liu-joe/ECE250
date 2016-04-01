#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

class Weighted_graph {
private:
    static const double INF;
    // your choice
    
    double **graph_matrix;
    int *graph_degree;
    int size;
    int numEdge;
    
    void testIndex( int, bool* );
    
public:
    Weighted_graph( int = 50 );
    ~Weighted_graph();
    
    int degree( int ) const;
    int edge_count() const;
    double adjacent( int, int ) const;
    double minimum_spanning_tree( int ) const;
    bool is_connected() const;
    
    void insert( int, int, double );
    
    // Friends
    
    friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Enter definitions for all public functions here

//TODO: add exception
Weighted_graph::Weighted_graph( int n ) {
    graph_matrix = new double*[n];
    for (int idx = 0; idx < n; ++idx) {
        graph_matrix[idx] = new double[n];
    }
    
    graph_degree = new int[n];
    
    size = n;
    
    numEdge = 0;
}

//TODO: add exception
int Weighted_graph::degree( int index ) {
    return graph_degree[index];
}

//TODO: add exception
int Weighted_graph::edge_count() {
    return numEdge;
}

//TODO: add exception 
double Weighted_graph::adjacent( int m, int n ) {
    if ( m == n ) {
        return 0;
    }
    
    if ( m < 0 || n < 0 || m >= size || n >= size ) {
        // throw exception
    }
    
    return graph_matrix[m][n]; 
}

bool Weighted_graph::is_connected() {
    bool* connected = new bool[size];
    connected[0] = true;
    for ( int idx = 1; idx < size; ++idx ) {
        connected[1] = false;
    }
    
    for ( int idx = 1; idx < size; ++idx ) {
        if ( graph_matrix[0][idx] != 0)  {
            testIndex( idx, connected );
        }
    }
    
    for ( int idx = 0; idx < size; ++idx ) {
        if ( connected[idx] == 0 ) {
            return false;
        }
    }
    
    return true;
}

void Weighted_graph::testIndex( int m, bool* connected ) {
    if ( connected[m] == 0 ) {
        connected[m] = 1;
        
        for ( int n = 0; n < size; ++n ) {
            if ( graph_matrix[m][n] != 0 ) {
                testIndex( n, connected );
            }
        }
    }
}

//TODO
Weighted_graph::minimum_spanning_tree( int m ) {
    
}

//TODO: add exception
void Weighted_graph::insert( int m, int n, double w ) {
    if ( m < 0 || n < 0 || m >= size || n >= size || m == n) {
        // Excpetion
    }
    
    if ( w < 0 || w == INF ) {
        // Exception
    }
    
    graph_matrix[m][n] = w;
    
    // If point already exists
    if ( graph_matrix[m][n] != 0 ) {
        if ( w == 0 ) {
            --numEdge;
            --graph_degree[n];
            --graph_degree[m];
        }
    } 
    
    // If point doesn't exist yet
    else {
        if ( w != 0 ) {
            ++numEdge;
            ++graph_degree[n];
            ++graph_degree[m];
        }
    }
}

std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
    // Your implementation
    
    return out;
}

#endif
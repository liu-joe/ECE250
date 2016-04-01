#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/****************************************
 * UW User ID:  z324liu
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 2016
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
    
    void testIndex( int, bool* ) const;
    double findMin( bool* ) const;
    
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

//TODO
Weighted_graph::~Weighted_graph() {
    for ( int idx = 0; idx < size; ++idx ) {
        delete[] graph_matrix[idx];
    }
    delete[] graph_matrix;
    delete[] graph_degree;
}

Weighted_graph::Weighted_graph( int n ) {
    
    if ( n < 0 ) {
        throw illegal_argument();
    }
    
    graph_matrix = new double*[n];
    for (int idx = 0; idx < n; ++idx) {
        graph_matrix[idx] = new double[n];
    }
    
    graph_degree = new int[n];
    
    size = n;
    
    numEdge = 0;
}

int Weighted_graph::degree( int index ) const {
    if ( index < 0 || index >= size ) {
        throw illegal_argument();
    }
    return graph_degree[index];
}

int Weighted_graph::edge_count() const {
    return numEdge;
}

double Weighted_graph::adjacent( int m, int n ) const {
    if ( m == n ) {
        return 0;
    }
    
    if ( m < 0 || n < 0 || m >= size || n >= size ) {
        throw illegal_argument();
    }
    
    if ( graph_matrix[m][n] == 0 ) {
        return INF;
    }
    
    return graph_matrix[m][n]; 
}

bool Weighted_graph::is_connected() const {
    bool* connected = new bool[size];
    connected[0] = true;
    for ( int idx = 1; idx < size; ++idx ) {
        connected[idx] = false;
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
    
    delete[] connected;
    return true;
}

void Weighted_graph::testIndex( int m, bool* connected ) const {
    if ( connected[m] == 0 ) {
        connected[m] = 1;
        
        for ( int n = 0; n < size; ++n ) {
            if ( graph_matrix[m][n] != 0 ) {
                testIndex( n, connected );
            }
        }
    }
}

double Weighted_graph::minimum_spanning_tree( int m ) const {
    
    if ( m < 0 || m >= size ) {
        throw illegal_argument();
    }
    
    bool* currentTree = new bool[size];
    for ( int idx = 0; idx < size; ++idx ) {
        currentTree[idx] = false;
    }
    currentTree[m] = true;
    
    double totalWeight = 0;
    
    for ( int idx = 0; idx < size - 1; ++idx ) {
        totalWeight += findMin( currentTree );
    }
    
    delete[] currentTree;
    return totalWeight;
    
}

double Weighted_graph::findMin( bool* currentTree ) const {
    double minValue = INF;
    int minX = -1;
    int minY = -1;
    
    for ( int x = 0; x < size; ++x ) {
        for ( int y = 0; y < size; ++y ) {
            if ( graph_matrix[x][y] != 0 && graph_matrix[x][y] < minValue ) {
                if ( currentTree[x] == false && currentTree[y] == true ) {
                    minX = x;
                    minY = y;
                    minValue = graph_matrix[x][y];
                }
            }
        }
    }
    
    if ( minValue != INF ) {
        currentTree[minX] = true;
        return minValue;
    } else {
        return 0;
    }
}

void Weighted_graph::insert( int m, int n, double w ) {
    if ( m < 0 || n < 0 || m >= size || n >= size || m == n) {
        throw illegal_argument();
    }
    
    if ( w < 0 || w == INF ) {
        throw illegal_argument();
    }
    
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
    
    graph_matrix[m][n] = w;
    graph_matrix[n][m] = w;
}

std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
    // Your implementation
    
    return out;
}

#endif
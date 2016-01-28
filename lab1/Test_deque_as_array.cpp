
/**
 *  Main.cpp
 *  Author:     Joe Liu
 *  Created:    January 20, 2016
 *
 *  Testing the functions of Dequeue_as_array.h as well as showing examples of
 *  its usage
 */

#include <iostream>

#include "Deque_as_array.h"

using namespace std;

int main() {
    Deque_as_array a(10);
    
    // Testing underflow exception when accessing empty array
    try {
        cout << a.head() << endl;
    } catch ( underflow e ) {
        cout << "Array empty" << endl;
    }
    
    // Testing overflow exception when enqueueing to full array
    // Populating the array using enqueue head
    for (int idx = 0; idx < 11; ++idx) {
        try {
            a.enqueue_head(idx + 1);
        } catch ( overflow e ) {
            cout << "Array full" << endl;
        }
        
        try {
            cout << a.head() << " " << a.tail() << endl;
        } catch ( underflow e ) {
            cout << "Array empty" << endl;
        }
    }
    
    int size = a.size();
    
    // Testing dequeue_tail function by itself
    for (int idx = 0; idx < size; ++idx) {
        try {
            cout << a.dequeue_tail() << endl;
        } catch ( underflow e ) {
            cout << "Array empty" << endl;
        }
    }
    
    // Testing clear function
    cout << "Clearing Queue" << endl;
    a.clear();
    
    // Populating the array using enqueue_tail
    for (int idx = 0; idx < 10; ++idx) {
        try {
            a.enqueue_tail(idx + 1);
        } catch ( overflow e ) {
            cout << "Array full" << endl;
        }
        
        try {
            cout << a.head() << " " << a.tail() << endl;
        } catch ( underflow e ) {
            cout << "Array empty" << endl;
        }
    }
    
    size = a.size();
    
    // Testing dequeue_head function by itself
    for (int idx = 0; idx < size; ++idx) {
        try {
            cout << a.dequeue_head() << endl;
        } catch ( underflow e ) {
            cout << "Array empty" << endl;
        }
    }
    
    cout << endl << endl << endl;
    Deque_as_array b(10);
    
    // Testing a mixture of enqueue_head and enqueue_tail used together
    // and also dequeue_head and dequeue_tail used together
    for (int idx = 0; idx < 5; ++idx) {
        try {
            a.enqueue_head(idx);
            a.enqueue_tail(idx * 10);
            
            cout << a.head() << " " << a.tail() << endl;
        } catch ( overflow e ) {
            cout << "Array full" << endl;
        } catch ( underflow e ) {
            cout << "Array empty" << endl;
        }
    }
}

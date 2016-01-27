/**
 *  Main.cpp
 *  Author:     Joe Liu
 *  Created:    January 13, 2016
 *
 *  Test cases for array.h
 */

#include <iostream>
#include <cassert>

#include "Exception.h"
#include "Array.h"

using namespace std;


int main() {

    // Initialize arrays of different types
    Array<int> a(20);
    Array<double> b(20);

    // Testing exception
    try {
        cout << "Sum: " << a.sum() << endl;
    } catch ( underflow e ) {
        cout << "Array size 0" << endl;
    }

    for (int idx = 0; idx < 20; ++idx) {
        a.append(idx);
    }
    
    for (double idx = 0; idx < 20; ++idx) {
        b.append(idx);
    }

    cout << a[10] << endl;
    cout << b[15] << endl;
    cout << a << endl;
    cout << "Sum: " << a.sum() << endl;
    a.clear();

    // Testing out of bound case
    cout << a.get(1000) << endl;

    return 0;
}

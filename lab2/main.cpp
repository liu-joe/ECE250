
#include <iostream>
#include "DoubleHashTable.h"
#include "Exception.h"

int main() {
    DoubleHashTable<int> ht;
    try {
         ht.insert(123);
         ht.insert(1543);
    } catch (overflow e) {
        std::cout << "overflow" << std::endl;
    }
         
    std::cout << ht.bin(1) << std::endl;
    std::cout << ht.bin(2) << std::endl;
    std::cout << ht.bin(3) << std::endl;
    std::cout << ht.bin(4) << std::endl;
    std::cout << ht.bin(5) << std::endl;
    for (int idx = 1; idx < 35; ++idx) {
        try {
            ht.insert(34 * idx);
        } catch (overflow e) {
            std::cout << "overflow" << std::endl;
        }
    }
    
    ht.print();
    std::cout << ht.member(124) << std::endl;
    std::cout << ht.member(123) << std::endl;
    std::cout << ht.bin(10) << std::endl;
}

#include "DoubleHashTable.h"

int main() {
    DoubleHashTable<int> ht;
    ht.insert(123);
    ht.insert(1543);
    for (int idx = 1; idx < 31; ++idx) {
        ht.insert(34 * idx);
    }
    
    ht.print();
    std::cout << ht.member(124) << std::endl;
    std::cout << ht.member(123) << std::endl;
    std::cout << ht.bin(10) << std::endl;
}
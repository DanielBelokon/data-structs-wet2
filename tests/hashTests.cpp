#include "../src/HashTable.h"
#include <iostream>

int main()
{
    // test for hash table
    HashTable<int> ht;
    ht.insert(1, 1);
    ht.insert(2, 2);
    ht.insert(3, 3);
    ht.insert(4, 4);
    ht.insert(5, 5);
    ht.insert(6, 6);
    ht.insert(7, 7);
    ht.insert(8, 8);
    ht.insert(9, 9);
    ht.insert(10, 10);
    ht.insert(11, 11);
    ht.insert(12, 12);
    ht.insert(13, 13);
    ht.insert(14, 14);
    ht.insert(15, 15);
    ht.insert(16, 16);
    ht.insert(17, 17);
    ht.insert(18, 18);
    ht.insert(19, 19);
    ht.insert(20, 20);
    ht.insert(21, 21);
    ht.insert(22, 22);
    ht.insert(23, 23);
    ht.insert(24, 24);
    ht.insert(25, 25);
    ht.insert(26, 26);
    ht.insert(27, 27);
    ht.insert(28, 28);
    ht.insert(29, 29);
    ht.insert(30, 30);
    ht.remove(1);
    ht.remove(2);
    ht.remove(3);
    ht.remove(4);
    ht.remove(5);
    ht.remove(6);
    ht.remove(7);
    ht.remove(8);
    ht.remove(9);
    ht.remove(10);
    ht.remove(11);
    ht.remove(12);
    ht.remove(13);
    ht.remove(14);
    ht.remove(15);
    ht.remove(16);
    ht.remove(17);
    ht.remove(18);
    ht.remove(19);
    ht.remove(20);
    ht.remove(21);
    ht.remove(22);
    ht.remove(23);
    ht.remove(24);
    ht.remove(25);
    ht.remove(26);

    std::cout << "size of table: " << ht.getCapacity() << std::endl;
    int *hist = new int[60];
    for (auto var : ht)
    {
        // std::cout << var << std::endl;
        hist[var]++;
    }

    for (int i = 0; i < ht.getCapacity(); i++)
    {
        std::cout << i << ": " << hist[i] << std::endl;
    }

    // union of two hash tables
    HashTable<int> ht2;
    ht2.insert(10, 31);
    ht2.insert(20, 32);
    ht2.insert(30, 33);
    ht2.insert(40, 34);
    ht2.insert(50, 35);
    ht2.insert(60, 36);
    ht2.insert(70, 37);
    ht2.insert(80, 38);
    ht2.insert(90, 39);
    // merge hashes
    ht.merge(&ht2);
    for (auto var : ht)
    {
        // std::cout << var << std::endl;
        hist[var] = 1;
    }

    for (int i = 0; i < 60; i++)
    {
        std::cout << i << ": " << hist[i] << std::endl;
    }
}
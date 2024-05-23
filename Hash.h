#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <list>
#include <cstring>
#include "Dato.h"
using namespace std;

// Hashtable to implement hotel management

class HashTable
{
private:
    static const int totRooms = 16;
    list<pair<int, Dato>> table[totRooms];

public:
    bool checkList(); // method to see if the list is empty or not
    int hashFunction(int roomNum);
    void insertItem(int roomNum, Dato& dato);
    void removeItem(int roomNum);
    //string searchTable(int roomNum);
    void printTable();
};

#endif
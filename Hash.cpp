#include "Hash.h"
#include <utility>   // For std::pair
#include <algorithm> // For std::lower_bound
using namespace std;

bool HashTable::checkList()
{
    int sum = 0;
    for (int i = 0; i < totRooms; i++)
    {
        sum += table[i].size();
        if (sum == 0)
        {
            return true;
        }
    }
    return false;
}

int HashTable::hashFunction(int roomNum)
{
    return roomNum % totRooms; // Key 905, in return, this func will spit out 9.
}

void HashTable::insertItem(int roomNum, Dato &dato)
{
    int hashValue = hashFunction(roomNum);
    auto &edi = table[hashValue];
    auto iterator = begin(edi);
    bool roomExist = false;
    for (iterator; iterator != end(edi); iterator++)
    {
        if(iterator->first == roomNum){
            roomExist = true;
            iterator->second = dato;
            cout<< "Hey, room exist, owner replaced"<<endl;
            break;
        }
    }
    if(!roomExist){
        edi.emplace_back(roomNum, dato);
    }
    return;
}

void HashTable::removeItem(int roomNum)
{
    int hashValue = hashFunction(roomNum);
    auto &edi = table[hashValue];

    for (auto iterator = edi.begin(); iterator != edi.end(); ++iterator)
    {
        if (iterator->first == roomNum)
        {
            edi.erase(iterator);
            cout << "Item was removed!" << endl;
            return;
        }
    }
    cout << "Item not found, try again." << endl;
}

void HashTable::printTable()
{
    for (int i = 0; i < totRooms; i++)
    {
        if (table[i].empty())
            continue;

        for (const auto &item : table[i])
        {
            cout << "Room Number: " << item.first << ", Name: " << item.second.name << endl;
        }
    }
}

int main()
{
    HashTable HT;

    if (HT.checkList())
    {
        cout << "it works!" << endl;
    }
    else
    {
        cout << "pailas";
    }

    Dato pepe("Pepe", 400);
    HT.insertItem(400, pepe);

    Dato tom("Tom", 201);
    HT.insertItem(201, tom);

    Dato bob("Bob", 332);
    HT.insertItem(332, bob);

    Dato j("J", 332);
    HT.insertItem(332, j);

    HT.printTable();

    HT.removeItem(400);

    HT.printTable();

    return 0;
}
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

int HashTable::hashFunction(int id) // We add the sum of each digit of the id
{
    int sumOfId = 0;
    int sumOfDigits = 0;
    while (id > 0)
    {
        sumOfDigits += id % 10; // take the last number of the ID and added to the sum
        id /= 10;               // that same number is eliminated to continue with the others
    }
    return sumOfDigits % totRooms;
}

void HashTable::insertItem(Dato &dato)
{
    int hashValue = hashFunction(dato.id);
    auto &edi = table[hashValue];
    edi.emplace_back(dato.id, dato);
}

void HashTable::removeItem(int id)
{
    int hashValue = hashFunction(id);
    auto &edi = table[hashValue];

    for (auto iterator = edi.begin(); iterator != edi.end(); ++iterator)
    {
        if (iterator->first == id)
        {
            edi.erase(iterator);
            cout << "Item was removed!" << endl;
            return;
        }
    }
    cout << "Item not found, try again." << endl;
}

bool HashTable::searchItem(int id)
{
    int hashValue = hashFunction(id);
    auto &edi = table[hashValue];

    for (auto iterator = edi.begin(); iterator != edi.end(); ++iterator)
    {
        if (iterator->first == id)
        {
            cout<< "ID was founded!" << endl;
            cout << "Name: " << iterator->second.name << endl;
            cout << "ID: " << iterator->second.id << endl;
            cout << "Room Number: " << iterator->second.roomNum << endl;
            return true;
        }
    }
    cout << "ID not founded, try again!" << endl;
    return false;
}

void HashTable::printTable()
{
    for (int i = 0; i < totRooms; i++)
    {
        if (table[i].empty())
            continue;

        for (const auto &item : table[i])
        {
            cout << "ID: " << item.first << ", Name: " << item.second.name
                 << ", Room Number: " << item.second.roomNum << endl;
        }
    }
}
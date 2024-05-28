#ifndef DATO_H
#define DATO_H

#include <iostream>
#include <string>

class Dato
{
public:
    std::string name;
    int roomNum;
    int id;

    Dato(std::string name, int roomNum, int id);
};

#endif
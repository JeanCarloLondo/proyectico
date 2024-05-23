#ifndef DATO_H
#define DATO_H

#include <iostream>
#include <string>

class Dato
{
public:
    std::string name;
    int roomNum;

    Dato(std::string name, int roomNum);
};

#endif
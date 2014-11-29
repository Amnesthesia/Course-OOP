#include "../include/adult.h"

#ifndef io
#define io
#include <iostream>
#endif // io

#ifndef MAXTXT
#define MAXTXT
const int MAX_TEXT = 80;
#endif

char* readChar(char* t);
adult::adult()
{
    last_name = new char[MAX_TEXT];

    std::cout << "\n\tLast name: ";
    std::cin.getline(last_name,MAX_TEXT);
}

adult::~adult()
{
    delete last_name;
}

adult::adult(std::ifstream &in) : individual(in)
{
    last_name = new char[MAX_TEXT];
    in.getline(last_name,MAX_TEXT);
}

void adult::toFile(std::ofstream &out)
{
    individual::toFile(out);
    out << last_name << "\n";
}

void adult::display()
{
    individual::display();
    std::cout << "\nLast name: " << last_name;
}

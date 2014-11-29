#include "../include/child.h"

#ifndef io
#define io
#include <iostream>
#endif // io

char readChar(char* t, char alternative1 ='x', char alternative2 = 'z');

child::child()
{
    if(readChar("Gender ( [m]ale/[f]emale): ", 'm', 'f') == 'm')
        gender = male;
    else
        gender = female;
}

child::~child()
{
    //dtor
}

void child::toFile(std::ofstream &out)
{
    out << gender;
}

void child::display()
{
    individual::display();
    if(gender == male)
        std::cout << "\nGender: Male\n";
    else
        std::cout << "\nGender: Female\n";
}

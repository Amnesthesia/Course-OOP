#include "../include/partner.h"

#ifndef io
#define io
#include <iostream>
#endif // io

int readNum(char* t);
char readChar(char* t, char alternative1, char alternative2);

partner::partner()
{
    phone1 = readNum("Phone number ");
    if(readChar("Add a secondary phone number? ",'y','n') == 'y')
        phone2 = readNum("Secondary phone number ");
    else
        phone2 = 0;
}

partner::~partner()
{
    //dtor
}

partner::partner(std::ifstream &in) : adult(in)
{
    in >> phone1;
    in >> phone2;
}

void partner::toFile(std::ofstream &out)
{
    out << 1 << "\n";
    adult::toFile(out);
    out << phone1 << "\n" << phone2 << "\n";
}


void partner::display()
{
    adult::display();
    std::cout << "\nPrimary phone: " << phone1;

    if(phone2>0)
        std::cout << "\nSecondary phone: " << phone2;
}

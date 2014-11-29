#include "../include/employee.h"

#ifndef io
#define io
#include <iostream>
#endif // io

int readNum(char* t);
char readChar(char* t, char alternative1, char alternative2);
char* readChar(char* t);

employee::employee()
{
    std::cout << "\nWarning: This constructor should not be run.";
}

employee::employee(int n)
{
    id = n;
    address = new char[MAX_TEXT];

    std::cout << "\n\tAddress: ";
    std::cin.getline(address,100);

    // Ask if the employee has a partner, and if so, continue adding said partner
    if(readChar("Does the employee have a partner?",'y','n') == 'y')
        partnr = new partner();


    // If more than 0, continue adding each kid
    if(amntChildren > 0)
        for(int i = 0; i < readNum("How many children does the employee have?"); i++)
            addChild();
}

employee::~employee()
{
    delete address;
    for(int i = amntChildren; i>0; i--)
        delete kid[i];
}

employee::employee(int n, std::ifstream &in) : adult(in)
{
 int hasPartnr;

 id = n;

 address = new char[MAX_TEXT];
 in.getline(address,MAX_TEXT);

 in >> hasPartnr;
 if(hasPartnr)
     partnr = new partner(in);

 in >> amntChildren;
 for(int i = 0; i<amntChildren;i++)
    kid[i] = new child(in);
}

void employee::toFile(std::ofstream &out)
{
    out << id << "\n";
    adult::toFile(out);
    out << address << "\n";

    if(partnr != NULL)
        partnr->toFile(out);
    else
        out << "0\n";

    if(amntChildren)
    {
        out << amntChildren << "\n";
        for(int i=0;i<amntChildren;i++)
            kid[i]->toFile(out);
    }

}

void employee::display()
{
    adult::display();
    std::cout << "\n\nEmployee ID: " << id;
    std::cout << "\nAddress: " << address;
    std::cout << "\n\nPartner: ";
    std::cout << "\n-----------";

    if(partnr != NULL)
        partnr->display();
    std::cout << "\n\nChildren: ";
    std::cout << "\n-----------";

    for(int i=0; i<amntChildren;i++)
        kid[i]->display();
}


// This method increments amntChildren by one and adds a new kid for this employee
void employee::addChild()
{
    kid[amntChildren++] = new child();
}

// This method loops through all the employees children and returns true if the employee
// has a child born the year specified by the parameter, else false.
bool employee::hasChildBornYear(int year)
{

    for(int i = 0; i<amntChildren; i++)
        if(kid[i]->bornYear(year))
            return true;

    return false;
}

// This method prints only the parent-class' information, such as names and DOB,
// skipping employee ID and address
void employee::printParent()
{
    adult::display();
}


// Operator overloading for ID comparison

bool employee::operator <(int i)
{
    return (id < i);
}

bool employee::operator >(int i)
{
    return (id > i);
}

#include "../include/individual.h"
#include <cstring>

#ifndef io
#define io
#include <iostream>
#endif // io

#ifndef MAXTXT
#define MAXTXT
const int MAX_TEXT = 80;
#endif

char readChar(char* t, char alternative1, char alternative2);
char* readChar(char* t);
int readNum(char* t, int min, int max);

individual::individual()
{
    first_name = new char[MAX_TEXT];

    std::cout << "\n\n\tDate of Birth (YYYYMMDD): ";
    std::cin.getline(dob,7);

    std::cout << "\n\tFirst name: ";
    std::cin.getline(first_name,MAX_TEXT);
}

individual::~individual()
{
    delete first_name;
}

individual::individual(std::ifstream &in)
{

}

bool individual::operator == (char date[7])
{
    return (strcmp(dob,date) == 0);
}

void individual::display()
{
    std::cout << "\nDOB: " << dob;
    std::cout << "\nFirst name: " << first_name;
}

// Print dob and first_name to file
void individual::toFile(std::ofstream &out)
{
    out << dob << "\n";
    out << first_name << "\n";
}

// Check if an individual is born a certain year
bool individual::bornYear(int year)
{
    // Extract first 2 characters from DOB (yy)
    char cYear[2]= {dob[0],dob[1]};

    // Turn char-year into an integer and compare to parameter year
    if(atoi(cYear) == year)
        return true;
    return false;
}


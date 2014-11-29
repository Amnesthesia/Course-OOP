#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <fstream>
#include  <stdio.h>          //  itoa
#include  <stdlib.h>

const int DATE_LENGTH = 7;

class individual
{
    public:
        individual();
        individual(std::ifstream &in);
        ~individual();

        // Comparing this object with == to a char date[7] will compare date of birth
        bool operator == (char date[7]);
        void display();

        void toFile(std::ofstream &out);
        bool bornYear(int year);

    protected:
        char* first_name;
        char dob[DATE_LENGTH];

};

#endif // INDIVIDUAL_H

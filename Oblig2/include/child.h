#ifndef CHILD_H
#define CHILD_H

#include "individual.h"

enum Gender{ female, male };

class child : public individual
{
    public:
        child();
        child(std::ifstream &in) : individual(in){ int i; in >> i; if(i == male) gender = male; else gender = female; };
        ~child();

        void toFile(std::ofstream &out);
        void display();


    private:
        Gender gender;
};

#endif // CHILD_H

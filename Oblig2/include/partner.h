#ifndef PARTNER_H
#define PARTNER_H

#include "adult.h"


class partner : public adult
{
    public:
        partner();
        partner(std::ifstream &in);
        ~partner();

        void toFile(std::ofstream &out);
        void display();


    private:
        int phone1;
        int phone2;
};

#endif // PARTNER_H

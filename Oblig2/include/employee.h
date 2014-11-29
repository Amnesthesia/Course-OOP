#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "adult.h"



#ifndef PARTNER_H
#include "partner.h"
#endif

#ifndef CHILD_H
#include "child.h"
#endif

const int MAX_CHILD = 20;

#ifndef MAXTXT
#define MAXTXT
const int MAX_TEXT = 80;
#endif


class employee : public adult
{
    public:
        employee();
        employee(int n);
        employee(int n, std::ifstream &in);
        ~employee();

        bool operator >(int i);
        bool operator <(int i);

        void toFile(std::ofstream &out);
        void display();
        void addChild();
        void printParent();
        bool hasChildBornYear(int year);

        int getID(){ return id; }

        // Rebuild the employee's partner by recreating it.
        void updatePartner(){ delete partnr; partnr = new partner(); };

    private:
        int id;
        int amntChildren;
        char* address;
        partner* partnr;
        child* kid[MAX_CHILD];

};

#endif // EMPLOYEE_H

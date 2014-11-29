#ifndef SHELLFISH_H
#define SHELLFISH_H

#include "aquatic_species.h"


class shellfish : public aquatic_species
{
    public:
        shellfish();
        virtual ~shellfish();

        // Will print all data contained within this class
        void print();

        // Setters
        void setParasitic(bool p);
        void setGastropod(bool g);

        // Getters
        bool getParasitic(){ return isParasitic; };
        bool getGastropod(){ return isGastropod; };
    private:
        bool isParasitic;
        bool isGastropod;
};

#endif // SHELLFISH_H

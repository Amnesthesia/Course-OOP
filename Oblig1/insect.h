#ifndef INSECT_H
#define INSECT_H

#include "aerial_species.h"

class insect : public aerial_species
{
    public:
        insect();
        virtual ~insect();

        // Will print data contained within this class
        void print();

        // Setters
        void setProtein(int p);

        // Getters
        int getProtein(){ return proteins; };
    private:
        int proteins;
};

#endif // INSECT_H

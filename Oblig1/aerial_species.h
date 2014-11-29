#ifndef AERIAL_SPECIES_H
#define AERIAL_SPECIES_H


#include "animal.h"

class aerial_species : public animal
{
    public:
        // Constructor & destructor
        aerial_species();
        virtual ~aerial_species();

        // Will print data within this class
        void print();

        // Setters
        void setFeathered(bool f);

        // Getters
        bool getFeathered(){ return isFeathered; };
    private:
        bool isFeathered;
};

#endif // AERIAL_SPECIES_H

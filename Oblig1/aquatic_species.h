#ifndef AQUATIC_SPECIES_H
#define AQUATIC_SPECIES_H

#include "animal.h"

class aquatic_species : public animal
{
    public:
        aquatic_species();
        virtual ~aquatic_species();

        // Will print data contained within this class
        void print();

        // Setters
        void setEdible(bool e);
        void setPoisonous(bool p);
        void setVenomous(bool v);

        // Getters
        bool getVenomous(){return isVenomous;};
        bool getPoisonous(){return isPoisonous;};
        bool getEdible(){ return isEdible; };
    private:
        bool isVenomous;
        bool isPoisonous;
        bool isEdible;
};

#endif // AQUATIC_SPECIES_H

#ifndef FISH_H
#define FISH_H

#include "aquatic_species.h"


class fish : public aquatic_species
{
    public:
        fish();
        fish(std::string name);
        virtual ~fish();

        // Will print data contained within this class
        void print();

        // Setters
        void setSchoolfish(bool s);
        void setSaltwater(bool s);

        // Getters
        bool getSaltwater(){return saltwater;};
        bool getSchoolfish(){return schoolfish;};

    private:
        bool saltwater; //Does this fish live in saltwater?
        bool schoolfish; //Does this fish swim in schools?
};

#endif // FISH_H

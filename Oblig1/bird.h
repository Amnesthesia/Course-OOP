#ifndef BIRD_H
#define BIRD_H

#include "aerial_species.h"


class bird : public aerial_species
{
    public:
        bird();
        virtual ~bird();

        // Will print data contained within this class
        void print();

        // Setters
        void setBirdGroup(int b);

        // Getters
        int getBirdGroup(){ return group; }
        std::string getBirdGroupLabel(int b);
        std::string getGroup(){ return getBirdGroupLabel(getBirdGroup()); }

    private:
        // Will contain the group number for this bird
        int group;

        // List of possible groups a bird can belong to
        enum birdgroup{
            ALBATROSSES_AND_PETRELS,
            BIRDS_OF_PREY,
            BUTTONQUAIL,
            CASSOWARIES_AND_EMUS,
            CRANES_COOTS_AND_RAILS,
            CUCKOOS_AND_TURACOS,
            FLAMINGOS,
            GAMEBIRDS,
            GREBES,
            HERONS_STORKS_RELATIVES,
            HUMMINGBIRDS_AND_SWIFTS,
            KINGFISHERS,
            KIWIS,
            LOONS,
            MOUSEBIRDS,
            NIGHTJARS_AND_FROGMOUTHS,
            OSTRICH,
            OWLS,
            PARROTS,
            PELICANS_RELATIVES,
            PERCHING_BIRDS,
            PIGEONS_AND_DOVES,
            RHEAS,
            SANDGROUSE,
            SHOREBIRDS,
            TINAMOUS,
            TROGONS,
            WATERFOWL,
            WOODPECKERS_AND_RELATIVES,
            UNKNOWN
        };
};

#endif // BIRD_H

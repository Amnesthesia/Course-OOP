#include "bird.h"

bird::bird()
{
    // Set the values we know ...
    this->setPhylum("Chordata");
    this->setClass("Aves");

    // Ask the user if (s)he wants to appoint a bird-group to this bird
    if(reqBoolInput("Define birdgroup"))
    {
        // List all bird-group IDs
        for(int i=ALBATROSSES_AND_PETRELS; i!=WOODPECKERS_AND_RELATIVES;i++)
        {
            // List with IDs ... but print the label
            std::cout << "\n" << i << ". " << getBirdGroupLabel(i);
        }

        this->setBirdGroup( reqIntInput("Enter birdgroup's number",ALBATROSSES_AND_PETRELS,WOODPECKERS_AND_RELATIVES) );
    }
    else // Otherwise, set bird-group to UNKNOWN
        this->setBirdGroup( UNKNOWN );

    // Request the unknown scientific data
    this->setOrder( reqStrInput("Order") );
    this->setFamily( reqStrInput("Family") );
    this->setGenus( reqStrInput("Genus") );
    this->setSpecies( reqStrInput("Species") );
}

bird::~bird()
{
}

// Sets the bird-group ID value for this bird
void bird::setBirdGroup(int b)
{
    group = b;
}

// Return the label in string format for a bird-group ID
std::string bird::getBirdGroupLabel(int b)
{
    // Contains all bird-group IDs and their labels
    // in string format
    switch(b)
    {
        case ALBATROSSES_AND_PETRELS:
            return "Albatrosses and petrels";
        case BIRDS_OF_PREY:
            return "Birds of Prey";
        case BUTTONQUAIL:
            return "Buttonquail";
        case CASSOWARIES_AND_EMUS:
            return "Cassowaries and Emus";
        case CRANES_COOTS_AND_RAILS:
            return "Cranes, Coots and Rails";
        case CUCKOOS_AND_TURACOS:
            return "Cuckoos and Turacos";
        case FLAMINGOS:
            return "Flamingos";
        case GAMEBIRDS:
            return "Gamebirds";
        case GREBES:
            return "Grebes";
        case HERONS_STORKS_RELATIVES:
            return "Herons, Storks and relatives";
        case HUMMINGBIRDS_AND_SWIFTS:
            return "Hummingbirds and swifts";
        case KINGFISHERS:
            return "Kingfishers";
        case KIWIS:
            return "Kiwis";
        case LOONS:
            return "Loons";
        case MOUSEBIRDS:
            return "Mousebirds";
        case NIGHTJARS_AND_FROGMOUTHS:
            return "Nightjards and Frogmouths";
        case OSTRICH:
            return "Ostrich";
        case OWLS:
            return "Owls";
        case PARROTS:
            return "Parrots";
        case PELICANS_RELATIVES:
            return "Pelicans and relatives";
        case PERCHING_BIRDS:
            return "Perching birds";
        case PIGEONS_AND_DOVES:
            return "Pigeons and Doves";
        case RHEAS:
            return "Rheas";
        case SANDGROUSE:
            return "Sandgrouse";
        case SHOREBIRDS:
            return "Shorebirds";
        case TINAMOUS:
            return "Tinamous";
        case TROGONS:
            return "Trogons";
        case WATERFOWL:
            return "Waterfowl";
        case WOODPECKERS_AND_RELATIVES:
            return "Woodpeckers and relatives";
        case UNKNOWN:
            return "Not specified";
    }
}

// Print data contained within this class' scope after printing parent
// class' data
void bird::print()
{
    aerial_species::print();

    if(getBirdGroup() == UNKNOWN)
        std::cout << "\n ... belongs to an unspecified group of birds";
    else
        std::cout << "\n ... belongs to the bird group \"" << getGroup() << "\"";
}

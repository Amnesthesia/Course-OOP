#include "shellfish.h"

shellfish::shellfish()
{
    // is this animal a gastropod?
    this->setGastropod( reqBoolInput("Gastropod") );
    // is this animal a parasitic animal?
    this->setParasitic( reqBoolInput("Parasitic") );

    // ... request user-input for unknown scientific fields
    this->setPhylum( reqStrInput("Phylum") );
    this->setClass( reqStrInput("Class") );
    this->setOrder( reqStrInput("Order") );
    this->setFamily( reqStrInput("Family") );
    this->setGenus( reqStrInput("Genus") );
    this->setSpecies( reqStrInput("Species") );
}

shellfish::~shellfish()
{
}


// Sets the gastropod attribute
void shellfish::setGastropod(bool g)
{
    isGastropod = g;
}

// Sets the parasite attribute
void shellfish::setParasitic(bool p)
{
    isParasitic = p;
}

// Prints data from parent class, then prints data contained
// within this class' scope
void shellfish::print()
{
    aquatic_species::print();
    std::cout << "\n... is " << (getParasitic() ? "" : "not") << " parasitic";
    std::cout << "\n... is " << (getGastropod() ? "" : "not a") << " gastropod";
}

#include "fish.h"

fish::fish()
{
    // Set known values
    this->setPhylum("Chordata");

    // Is this a saltwater fish?
    this->setSaltwater( reqBoolInput("Saltwater fish") );
    // Is this a schooling fish?
    this->setSchoolfish( reqBoolInput("Schooling/Schoaling fish") );

    // Request user-input for unknown taxonomy data
    this->setClass( reqStrInput("Class") );
    this->setOrder( reqStrInput("Order") );
    this->setFamily( reqStrInput("Family") );
    this->setGenus( reqStrInput("Genus") );
    this->setSpecies( reqStrInput("Species"));
}

// Same as fish() but also reads the layman name
fish::fish(std::string name) : animal(0)
{
    this->setLaymanName(name);

    // Set known values
    this->setPhylum("Chordata");

    // Is this a saltwater fish?
    this->setSaltwater( reqBoolInput("Saltwater fish") );
    // Is this a schooling fish?
    this->setSchoolfish( reqBoolInput("Schooling/Schoaling fish") );

    // Request user-input for unknown taxonomy data
    this->setClass( reqStrInput("Class") );
    this->setOrder( reqStrInput("Order") );
    this->setFamily( reqStrInput("Family") );
    this->setGenus( reqStrInput("Genus") );
    this->setSpecies( reqStrInput("Species"));

}

fish::~fish()
{
}

// Sets the saltwater attribute
void fish::setSaltwater(bool s)
{
    saltwater = s;
}

// Sets the "schooling" attribute
void fish::setSchoolfish(bool s)
{
    schoolfish = s;
}

// Prints all data in parentclass, then all data contained within this class
void fish::print()
{
    aquatic_species::print();
    std::cout << "\n ... is " << (getSaltwater() ? "a" : "not a") << " saltwater fish";
    std::cout << "\n ... " << (getSchoolfish() ? "swims in" : "does not swim in") << " schools";
}

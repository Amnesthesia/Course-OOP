#include "insect.h"

insect::insect()
{
    // Set the field we know ...
    this->setPhylum("Arthtropoda");

    // ... and request those we dont know from the user
    this->setClass( reqStrInput("Class") );
    this->setOrder( reqStrInput("Order") );
    this->setFamily( reqStrInput("Family") );
    this->setGenus( reqStrInput("Genus") );
    this->setSpecies( reqStrInput("Species"));

    // ... ask the user how much protein per 100g this insect contains
    this->setProtein( reqIntInput("Amount of proteins/100g ",0,99) );
}

insect::~insect()
{
}

// Sets proteinvalue of insect (per 100g)
void insect::setProtein(int p)
{
    proteins = p;
}

// Prints data contained within this class' scope (proteins)
// and calls parent-class' print method
void insect::print()
{
    aerial_species::print();

    std::cout << "\n... is made of " << proteins << "% protein";
}

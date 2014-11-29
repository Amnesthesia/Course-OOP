#include "aerial_species.h"

aerial_species::aerial_species()
{
    // Request information from user about
    // whether or not the animal has feathers
    this->setFeathered( reqBoolInput("Feathered") );
}


aerial_species::~aerial_species()
{
}

// Sets 'feather' attribute for animal
void aerial_species::setFeathered(bool f)
{
    isFeathered = f;
}

// Prints data stored within this class' scope
void aerial_species::print()
{
    animal::print();

    if(getFeathered())
        std::cout << "\n ... has feathers";
    else
        std::cout << "\n ... has no feathers";
}

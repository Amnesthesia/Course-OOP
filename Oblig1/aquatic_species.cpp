#include "aquatic_species.h"

aquatic_species::aquatic_species()
{
    // Is this species edible?
    this->setEdible( reqBoolInput("Edible") );

    // If it's not edible ... is it ... poisonous?
    if(!isEdible)
        this->setPoisonous( reqBoolInput("Poisonous") );

    // ... and is it venomous?
    this->setVenomous( reqBoolInput("Venomous") );

}

aquatic_species::~aquatic_species()
{
}

// Sets the 'edible' attribute for this species
void aquatic_species::setEdible(bool e)
{
    isEdible = e;
}

// Sets the 'venomous' attribute for this species
void aquatic_species::setVenomous(bool v)
{
    isVenomous = v;
}

// Sets the 'poisonous' attribute for this species
void aquatic_species::setPoisonous(bool p)
{
    isPoisonous = p;
}


// Prints data from parent class, then data contained within this class' scope
void aquatic_species::print()
{
    animal::print();
    std::cout << "\n ... is " << (getEdible() ? "": "not") << " edible";
    std::cout << "\n ... is " << (getVenomous() ? "" : "not") << " venomous";
    std::cout << "\n ... is " << (getPoisonous() ? "" : "not") << " poisonous";
}

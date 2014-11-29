#include "animal.h"

animal::animal()
{
    // Set the values we already know
    this->setDomain("Eukaryota");
    this->setKingdom("Animalia");

    // ... and request the one we don't know
    this->setLaymanName( reqStrInput("Name of animal?") );
}

// Same as the above constructor, but does not request layman name
animal::animal(int i)
{
    // Set the values we already know
    this->setDomain("Eukaryota");
    this->setKingdom("Animalia");
}
animal::~animal()
{
}

// Requests user input and returns as string
std::string animal::reqStrInput(std::string field)
{
    std::cout << "\n" << field << ": ";
    std::string input;
    getline(std::cin,input);
    return input;
}

// Requests user input and returns as boolean
bool animal::reqBoolInput(std::string field)
{
    char in;
    do{
        std::cout << "\n" << field << "? (y/n): ";
        std::cin >> in;
        std::cin.ignore();

    } while((in!='Y' && in!='y') && (in!='N' && in!='n'));

    // If it's not Y or y, it's N/n. Otherwise 'while' would not break
    return (in == 'Y' || in == 'y');
}

// Request user input and return integer (between 2 values)
int animal::reqIntInput(std::string field,const int min,const int max)
{
    int i;
    do{

        std::cout << "\n" << field << " (" << min << "-" << max << "): ";
        std::cin >> i;
        std::cin.ignore();
    } while(i>max || i<min);
    return i;
}

// Sets the scientific.domain of the animal
void animal::setDomain(std::string d)
{
    scientific.domain = d;
}

// Sets the scientific.kingdom of the animal
void animal::setKingdom(std::string k)
{
    scientific.kingdom = k;
}

// Sets the scientific.phylum of the animal
void animal::setPhylum(std::string p)
{
    scientific.phylum = p;
}

// Sets the scientific class of the animal
void animal::setClass(std::string c)
{
    scientific.organism_class = c;
}

// Sets the scientific.order of the animal
void animal::setOrder(std::string o)
{
    scientific.order = o;
}

// Sets the scientific.family of the animal
void animal::setFamily(std::string f)
{
    scientific.family = f;
}

// Sets the scientific.genus of the animal
void animal::setGenus(std::string g)
{
    scientific.genus = g;
}

// Sets the scientific.species of the animal
void animal::setSpecies(std::string s)
{
    scientific.species = s;
}

// Sets the layman name of the animal
void animal::setLaymanName(std::string name)
{
    laymanName = name;
}


// Prints all data belonging to this particular class
void animal::print()
{
    std::cout << "\nScientific Data:";
    std::cout << "\nDomain: " << scientific.domain;
    std::cout << "\nKingdom: " << scientific.kingdom;
    std::cout << "\nPhylum: " << scientific.phylum;
    std::cout << "\nClass: " << scientific.organism_class;
    std::cout << "\nOrder: " << scientific.order;
    std::cout << "\nFamily: " << scientific.family;
    std::cout << "\nGenus: " << scientific.genus;
    std::cout << "\nSpecies: " << scientific.species;
    std::cout << "\n\nLayman name: " << laymanName;
}

#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
#include <iostream>

// Struct containing taxonomy data
// Typedef'd to avoid defining it within
// a class, but using it inside one.
typedef struct
{
    std::string domain;
    std::string kingdom;
    std::string phylum;
    std::string organism_class;
    std::string order;
    std::string family;
    std::string genus;
    std::string species;
} taxonomy;

class animal
{
    public:
        animal();
        // Dummy constructor -- does not request layman name
        animal(int i);
        virtual ~animal();

        void print();

        /** Requests user-input in different types
         ** These are static, as they can be used from anywhere.
         ** Could have made these global, but deriving classes
         ** are dependent on them (if another main() would use the classes)
         **/
        static std::string reqStrInput(std::string field);
        static bool reqBoolInput(std::string field);
        static int reqIntInput(std::string field,const int min,const int max);

        // Setters
        void setDomain(std::string d);
        void setKingdom(std::string k);
        void setPhylum(std::string p);
        void setClass(std::string c);
        void setOrder(std::string o);
        void setFamily(std::string f);
        void setGenus(std::string g);
        void setSpecies(std::string s);
        void setLaymanName(std::string name);

        // Getters
        std::string getDomain(){ return scientific.domain; };
        std::string getKingdom(){ return scientific.kingdom; };
        std::string getPhylum(){ return scientific.phylum; };
        std::string getClass(){ return scientific.organism_class; };
        std::string getOrder(){ return scientific.order; };
        std::string getFamily(){ return scientific.family; };
        std::string getGenus(){ return scientific.genus; };
        std::string getSpecies(){ return scientific.species; };
        std::string getName(){ return laymanName; };
    private:
        taxonomy scientific;

        // Regular name for the animal
        std::string laymanName;


};

#endif // ANIMAL_H

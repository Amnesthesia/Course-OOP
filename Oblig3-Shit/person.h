#ifndef PERSON_H
#define PERSON_H
#include "globals.h"

class Person : public Num_element
{
public:
    Person();
    Person(int id);
	std::string getName() { return name; }
	void setName(std::string nme) { name = nme; }
private:
    std::string name;
};

#endif // PERSON_H

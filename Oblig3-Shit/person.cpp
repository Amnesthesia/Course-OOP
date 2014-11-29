#include "person.h"

Person::Person() : Num_element(0)
{
    this->setName(readString("Name"));
}

Person::Person(int id) : Num_element(id)
{
    this->setName(readString("Name"));
}

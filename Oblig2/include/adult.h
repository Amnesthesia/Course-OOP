#ifndef ADULT_H
#define ADULT_H

#include "individual.h"


class adult : public individual
{
    public:
        adult();
        adult(std::ifstream &in);
        ~adult();

        void toFile(std::ofstream &out);
        void display();

    protected:
        char* last_name;
};

#endif // ADULT_H

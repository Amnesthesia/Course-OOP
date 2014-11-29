#include <iostream>
#include <string>

#include "bird.h"
#include "fish.h"
#include "insect.h"
#include "shellfish.h"

using namespace std;

int main()
{
    cout << "\nWhat kind of animal would you like to create? ";
    cout << "\n1. Bird";
    cout << "\n2. Fish";
    cout << "\n3. Insect";
    cout << "\n4. Shellfish";

    switch(animal::reqIntInput("Select animal",1,4))
    {
        case 1:
        {
            bird* usrBird = new bird();
            usrBird->print();
            delete usrBird;
            break;
        }

        case 2:
        {
            string fishname = animal::reqStrInput("Name");
            fish* usrFish;
            if(fishname.empty())
                usrFish = new fish();
            else
                usrFish = new fish(fishname);
            usrFish->print();
            delete usrFish;
            break;
        }

        case 3:
        {
            insect* usrInsect = new insect();
            usrInsect->print();
            delete usrInsect;
            break;
        }
        case 4:
        {
            shellfish* usrShellfish = new shellfish();
            usrShellfish->print();
            delete usrShellfish;
            break;
        }
    }

    return 0;
}

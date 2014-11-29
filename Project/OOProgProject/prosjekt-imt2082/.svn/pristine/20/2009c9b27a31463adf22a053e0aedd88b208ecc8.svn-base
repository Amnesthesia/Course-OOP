/****************************************************************************
	class:        Hotell
	read:         <forkortet hotellnavn>.dta
	write:        <forkortet hotellnavn>.dta
	author:       ...

	description:  ...
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <iostream>
#include <string>
#include <fstream>

#include "hotellClass.h"
#include "enums.h"
#include "romSingelClass.h"
#include "romDobbelClass.h"
#include "romSuiteClass.h"

/* --------------------------------------
             USED NAMESPACE
   -------------------------------------*/
using namespace std;

/* --------------------------------------
		   FUNCTION DEFINITIONS
   -------------------------------------*/
Hotell::Hotell()
{
    rooms[singel] = new List(Sorted);
    rooms[dobbel] = new List(Sorted);
    rooms[suite] = new List(Sorted);
}

Hotell::Hotell(string fileName)
{
	ifstream inFile(fileName.c_str(), ios::in);

	rooms[singel] = new List(Sorted);
	rooms[dobbel] = new List(Sorted);
	rooms[suite] = new List(Sorted);

	int numberOfRooms[3];
	facilityDescriptions = new string[MAX_FASILITETER];

	getline(inFile, name);
	inFile >> streetAddress >> postAddress >> mailAddress;
	inFile >> phoneNumber >> faxNumber >> fileName >> breakfastCost;
	inFile >> additionalBedCost >> numberOfFacilities;
	for (int i = 1; i <= numberOfFacilities; i++)
	{
		inFile >> facilityDescriptions[i];
	}
	inFile >> numberOfRooms[singel];
	for (int i = 1; i <= numberOfRooms[singel]; i++)
	{
		int nr;
		inFile >> nr;
		Singel* nyttRom = new Singel(inFile, nr);
		rooms[singel] ->add(nyttRom);
	}
	inFile >> numberOfRooms[dobbel];
	for (int i = 1; i <= numberOfRooms[dobbel]; i++)
	{
		int nr;
		inFile >> nr;
		Dobbel* nyttRom = new Dobbel(inFile, nr);
		rooms[dobbel] ->add(nyttRom);
	}
	inFile >> numberOfRooms[suite];
	for (int i = 1; i <= numberOfRooms[suite]; i++)
	{
		int nr;
		inFile >> nr;
		Suite* nyttRom = new Suite(inFile, nr);
		rooms[suite] ->add(nyttRom);
	}
	inFile.close();
}

Hotell::~Hotell()
{

}

/******************************************************************************
	name:        getAvailableRoom(int, int, int)
	description: Returns a randomly selected available room
	parameters:  int d1, int d2, int type
	returns: 	 Rom
******************************************************************************/

Rom* Hotell::getAvailableRoom(int d1, int d2, int type)
{
    // If there's no rooms of that type, return an empty room
    if(rooms[type]->is_empty())
        return new Rom();

    // Set up a temporary list -- a copy of room[type] list
    List temporary = *rooms[type];

    // Set up a list to contain all available rooms we find...
    List* avail = new List(Sorted);

    // Check each room to see if it is available between two specified dates
    for(int i = 0; i < rooms[type]->no_of_elements(); i++)
    {
        Rom* r = (Rom*) temporary.remove();

        // And if it is ... add it to our list of available rooms :D
        if(!r->isReserved(d1, tid.forskjell_datoer(d1,d2)))
            avail->add(r);
    }

    // Randomize a number between 0 and the amount of elements in our list
    int finalRoom = rand() % avail->no_of_elements();

    // ... and return the room at that position in our list! :)
    return (Rom*) avail->remove_no(finalRoom);
}

/******************************************************************************
	name:        removeReservationBy()
	description: Loops through all rooms to find reservations made by a specific name,
                 and asks the user if (s)he wants to remove it or not.
	parameters:  std::string name
******************************************************************************/

void Hotell::removeReservationBy(std::string name)
{
    // Set up a copy (?) of each room-type's list
    List singles = *rooms[singel];
    List suites = *rooms[suite];
    List doubles = *rooms[dobbel];

    // Loop through all single rooms ...
    std::cout << "\n\n\tSingle room reservations by " << name << ": ";

    for(int i = 0; i<singles.no_of_elements(); i++)
    {
        Rom* si = (Rom*) singles.remove();

        // Now call the more specific method in the room class...
        si->removeReservationBy(name);
    }

    // ... and all double rooms ...
    std::cout << "\n\n\tDouble room reservations by " << name << ": ";

    for(int j = 0; j<doubles.no_of_elements(); j++)
    {
        Rom* d = (Rom*) doubles.remove();

        // Let Rom handle the rest ...
        d->removeReservationBy(name);
    }

    // ... aaaaand all suites :DDD
    std::cout << "\n\n\tSuit reservations by " << name << ": ";

    for(int k = 0; k<suites.no_of_elements(); k++)
    {
        Rom* su = (Rom*) suites.remove();

        // Call the more specific method found in Rom
        su->removeReservationBy(name);
    }

}

/******************************************************************************
	name:        displayHotelData()
	description: Displays data about the hotel
	parameters:
******************************************************************************/
void Hotell::displayHotelData()
{
	cout << "Hotell: " << name << endl;


	cin.get();
}

void Hotell::writeDataToFile(string fileName)
{
	ofstream outFile(fileName.c_str(), ios::out);
	outFile << name << streetAddress << postAddress << mailAddress;
	outFile << phoneNumber << faxNumber << fileName << breakfastCost;
	outFile << additionalBedCost << numberOfFacilities;
		for (int i = 1; i <= numberOfFacilities; i++)
		{
			outFile << facilityDescriptions[i];
		}
	outFile << rooms[singel]->no_of_elements();
		for (int i = 1; i <= rooms[singel]->no_of_elements(); i++)
		{
			Singel* temp = (Singel*) rooms[singel]->remove_no(i);
			rooms[singel]->add(temp);
			temp->writeDataToFile(outFile);
		}
	outFile << rooms[dobbel]->no_of_elements();
		for (int i = 1; i <= rooms[dobbel]->no_of_elements(); i++)
		{
			Dobbel* temp = (Dobbel*) rooms[dobbel]->remove_no(i);
			rooms[dobbel]->add(temp);
			temp->writeDataToFile(outFile);
		}
	outFile << rooms[suite]->no_of_elements();
		for (int i = 1; i <= rooms[suite]->no_of_elements(); i++)
		{
			Suite* temp = (Suite*) rooms[suite]->remove_no(i);
			rooms[suite]->add(temp);
			temp->writeDataToFile(outFile);
		}
	
}
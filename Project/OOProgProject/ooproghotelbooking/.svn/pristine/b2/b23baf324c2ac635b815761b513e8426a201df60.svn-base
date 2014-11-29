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
#include <iostream>										    // For input/output
#include <string>												  // For string
#include <fstream>											  // For filestream
#include <cstdlib>												// itoa
#include <sstream>												// to_string

#include "hotellClass.h"
#include "enums.h"
#include "romSingelClass.h"
#include "romDobbelClass.h"
#include "romSuiteClass.h"


/* --------------------------------------
          NAMESPACE, STD SYMBOLS
   -------------------------------------*/
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

/* --------------------------------------
		   FUNCTION DEFINITIONS
   -------------------------------------*/
Hotell::Hotell()
{
    rooms[singel] = new List(Sorted);
    rooms[dobbel] = new List(Sorted);
    rooms[suite] = new List(Sorted);
}

/******************************************************************************
	name:        Hotell(string)
	description: Reads data from filename.dta
	parameters:  string filename
	returns: 	 n/a
******************************************************************************/
Hotell::Hotell(string openfileName)
{
	ifstream inFile(openfileName.c_str(), ios::in);

	rooms[singel] = new List(Sorted);
	rooms[dobbel] = new List(Sorted);
	rooms[suite] = new List(Sorted);

	int numberOfRooms[3];
	facilityDescriptions = new string[MAX_FASILITETER];

	getline(inFile, name);
	getline(inFile, streetAddress);
	getline (inFile, postAddress);
	inFile >> mailAddress;
	inFile >> phoneNumber >> faxNumber >> fileName >> numberOfSuites;

	suiteDesctiptions = new string[numberOfSuites];
	inFile.ignore();
		for (int i = 0; i < numberOfSuites; i++)
		{
			getline(inFile, suiteDesctiptions[i]);
		}

	inFile >> breakfastCost >> additionalBedCost >> numberOfFacilities;
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
		bool extraBed1;
		inFile >> extraBed1 >> nr;
		Dobbel* nyttRom = new Dobbel(inFile, extraBed1, nr);
		rooms[dobbel] ->add(nyttRom);
	}
	inFile >> numberOfRooms[suite]; inFile.ignore();
	for (int i = 1; i <= numberOfRooms[suite]; i++)
	{
		int nr;
		int nBeds;
		int bedMod;
		int sqremeters;
		string desc;
		inFile >> nBeds >> bedMod >> sqremeters >> nr;
		int rNr = nr - 301;								//forutsetter at alle suiter er >300

		desc = suiteDesctiptions[rNr];

		Suite* nyttRom = new Suite(inFile, nBeds, bedMod, sqremeters, desc, nr);
		rooms[suite] ->add(nyttRom);
	}
	inFile.close();
}

Hotell::~Hotell()
{
	delete rooms[singel];
	delete rooms[dobbel];
	delete rooms[suite];

	//delete facilityDescriptions; // Causes an debug assertion fail.
}

/******************************************************************************
	name:        Rom* getAvailableRoom(int, int, int)
	description: Returns a randomly selected available room
	parameters:  int d1, int d2, int type
	returns: 	 Rom
******************************************************************************/

Rom* Hotell::getAvailableRoom(int d1, int d2, int type)
{
    // If there's no rooms of that type, return an empty room
    if(rooms[type]->is_empty())
        return new Rom(noRoomOfSpecifiedTypeExists);

    // Set up a list to contain all available rooms we find...
    List* avail = new List(Sorted);

    // Check each room to see if it is available between two specified dates
    for(int i = 0; i < rooms[type]->no_of_elements(); i++)
    {
        Rom* r = (Rom*) rooms[type]->remove_no(i);

        // And if it is ... add it to our list of available rooms :D
        if(!r->isReserved(d1, tid.forskjell_datoer(d1,d2)))
            avail->add(r);

		// ... and put it back in the list
		rooms[type]->add(r);
    }

	if(avail->is_empty())
		return new Singel(noRoomOfSpecifiedTypeAvailable);

    // Randomize a number between 0 and the amount of elements in our list
    int finalRoom = rand() % avail->no_of_elements();

    // ... and return the room at that position in our list! :)
    return (Rom*) avail->remove_no(finalRoom);
}


/******************************************************************************
	name:        void removeReservationBy()
	description: Loops through all rooms to find reservations made by a specific name,
                 and asks the user if (s)he wants to remove it or not.
	parameters:  std::string name
******************************************************************************/

void Hotell::removeReservationBy(std::string name)
{
	cout << "Reservations on the name " << name << "\n";

	for (int i = rooms[singel]->no_of_elements(); i > 0; i--)
	{
		Singel* temp = (Singel*) rooms[singel]->remove_no(i);
		temp->singleReservationByName(name);
		rooms[singel]->add(temp);
	}

	for (int i = rooms[dobbel]->no_of_elements(); i > 0; i--)
	{
		Dobbel* temp = (Dobbel*) rooms[dobbel]->remove_no(i);
		temp->dobbleReservationByName(name);
		rooms[dobbel]->add(temp);
	}

	for (int i = rooms[suite]->no_of_elements(); i > 0; i--)
	{
		Suite* temp = (Suite*) rooms[suite]->remove_no(i);
		temp->suiteReservationByName(name);
		rooms[suite]->add(temp);
	}
}

/******************************************************************************
	name:        void displayHotelData()
	description: Displays data about the hotel
	parameters:  n/a
	returns:     n/a
******************************************************************************/
void Hotell::displayHotelData()
{
	cout << "\n" << name << endl;
	cout << "--------------------------\n";
	cout << "Adresse....: " << streetAddress << "\n";
	cout << "Postadresse: " << postAddress << "\n";
	cout << "E-post.....: " << mailAddress << "\n";
	cout << "Tlf........: " << phoneNumber << "\n";
	cout << "Fax........: " << faxNumber << "\n";
	cout << "\nPRISER\n";
	cout << "Frokostpris: " << breakfastCost << " " << VALUTA << "\n";
	cout << "Ekstra seng: " << additionalBedCost << " " << VALUTA << "\n";
	cout << "\n" << "FASILITETER\n";

	for (int i = 1; i <= numberOfFacilities; i++)
		cout << " - " << facilityDescriptions[i] << "\n";

	cout << "\nTrykk en tast for \x86 g\x86 tilbake til hovedmeny."; cin.get();
}

/******************************************************************************
	name:        void displaySuiteData()
	description: Displays data about the suites in the hotel
	parameters:  n/a
	returns:     n/a
******************************************************************************/
void Hotell::displaySuiteData()
{
	cout << "\n" << name << "\n";
	cout << "---------------------------------\n";
	cout << "Oversikt over Suiter:\n";

	for (int i=0; i < numberOfSuites; i++)
		cout << "\tRom " << (i + 301) << ": " << suiteDesctiptions[i] << "\n"; 

	cout << "\nTrykk en tast for \x86 g\x86 tilbake til hovedmeny."; cin.get();
}

/******************************************************************************
	name:        void writeDataToFile()
	description: writes hotel data to file <forkortet hotellnavn.dta>
	parameters:  n/a
	returns:     n/a
******************************************************************************/
void Hotell::writeDataToFile()
{
	ofstream outFile(fileName.c_str(), ios::out);
	outFile << name << "\n" << streetAddress << "\n" << postAddress << "\n" << mailAddress << "\n";
	outFile << phoneNumber << "\n" << faxNumber << "\n" << fileName << "\n" << numberOfSuites << "\n";
		for (int i = 0; i < numberOfSuites; i++)
		{
			outFile << suiteDesctiptions[i] << "\n";
		}
	outFile << breakfastCost << "\n";
	outFile << additionalBedCost << "\n" << numberOfFacilities << "\n";
		for (int i = 1; i <= numberOfFacilities; i++)
		{
			outFile << facilityDescriptions[i] << "\n";
		}
	outFile << rooms[singel]->no_of_elements() << "\n";
		for (int i = 1; i <= rooms[singel]->no_of_elements(); i++)
		{
			Singel* temp = (Singel*) rooms[singel]->remove_no(i);
			rooms[singel]->add(temp);
			temp->writeDataToFile(outFile);
		}
	outFile << rooms[dobbel]->no_of_elements() << "\n";
		for (int i = 1; i <= rooms[dobbel]->no_of_elements(); i++)
		{
			Dobbel* temp = (Dobbel*) rooms[dobbel]->remove_no(i);
			rooms[dobbel]->add(temp);
			temp->writeDataToFile(outFile);
		}
	outFile << rooms[suite]->no_of_elements() << "\n";
		for (int i = 1; i <= rooms[suite]->no_of_elements(); i++)
		{
			Suite* temp = (Suite*) rooms[suite]->remove_no(i);
			rooms[suite]->add(temp);
			temp->writeDataToFile(outFile);
		}
	
}
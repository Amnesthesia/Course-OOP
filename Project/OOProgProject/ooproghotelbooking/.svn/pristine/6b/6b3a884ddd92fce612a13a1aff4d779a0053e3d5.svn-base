/****************************************************************************
	class:        Reservasjon
	read:         n/a
	write:        n/a
	author:       ...

	description:  ...
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include "reservasjonClass.h"
#include "reservasjonClass.h"
#include <iostream>
#include <fstream>

/******************************************************************************
	name:        operator ==
	description: ...
	parameters:  ...
******************************************************************************/
//bool Reservasjon::operator ==(std::string name) 
//{
//	if(occupants->in_list(name.c_str())) 
//		return true; 
//	
//	return false;
//}
/******************************************************************************
	name:        Reservasjon()
	description: Constructor for Reservasjon. Creates a reservation for a single occupant
	parameters:  std::string names, int arr, int dep, int room_id
******************************************************************************/

Reservasjon::Reservasjon(int rID, int arr, int dep) : Num_element(arr)
{
    Timer timecalc;
    arrival = arr;
    departure = dep;
    numberOfDays = tid.forskjell_datoer(arrival,departure);

    costPrDay = new float[numberOfDays];
	
	
	// Ask user how many names (s)he wants on the reservation ...
	numberOfOccupants = readNumber("How many names would you like to put on your reservation?",0,MAX_PAA_ROM);

    // Set up our occupant string array
    occupant = new std::string[numberOfOccupants+1];

	// Request names from user
	for(int i = 1; i <= numberOfOccupants; i++)
	{
		occupant[i] = readString("Enter name");
	}

    roomID = rID;

}


Reservasjon::Reservasjon(std::ifstream &inFile, int dato) : Num_element(dato)
{
	occupant = new std::string[MAX_PAA_ROM];
	arrival = dato;
	inFile >> departure >> numberOfDays;
	inFile >> extraBed >> bedInUse >> numberOfOccupants;
	for (int i = 1; i <= numberOfOccupants; i++)
	{
		inFile >> occupant[i];
	}
}

bool Reservasjon::sameNameAsReservation(std::string name)
{
	bool nameIsOnReservation = false;

	for(int i = 1; i <= numberOfOccupants; i++)
	{
		if(name.compare(occupant[i]) == 0)
			nameIsOnReservation = true;
	}
	
	return nameIsOnReservation;
}

/******************************************************************************
	name:        setExtrabedAvailable
	description: Sets the boolean for whether or not an extra bed is available
	parameters:  bool e
******************************************************************************/
void Reservasjon::setExtrabedAvailable(bool e)
{
    extraBed = e;
}

/******************************************************************************
	name:        setExtrabedInUse
	description: Sets the value for whether or not the extra bed is available / in use
	parameters:  bool e
******************************************************************************/
void Reservasjon::setExtrabedInUse(bool e)
{
    // If an extrabed isn't available to begin with, set to 0 and exit
    if(!extraBed)
    {
        bedInUse = 0;
        return;
    }

    // Otherwise, if it's available, we want to set it to:
    // 1 - if bed exists but is not in use
    // 2 - bed exists and is in use
    // Therefore, we treat our boolean as an int and just increment it.
    bedInUse = (int)e+1;
}

/******************************************************************************
	name:        setBreakfast()
	description: Sets the boolean for whether or not the guest wants breakfast
	parameters:  bool b
******************************************************************************/
void Reservasjon::setBreakfast(bool b)
{
    breakfast = b;
}

// Displays without displaying room number -- to be able to run display_list() on a list of reservations
void Reservasjon::display()
{
	std::cout << "\nCHECK-IN: " << arrival;
    std::cout << "\nCHECK-OUT: " << departure;
    std::cout << "\nBREAKFAST: " << (breakfast ? "Yes" : "No");
    std::cout << "\nEXTRA BED: " << (extraBed ? "Yes" : "No");
    std::cout << "\n\nTOTAL NIGHTS: " << numberOfDays;
    std::cout << "\n\nNames on reservation: ";
}


void Reservasjon::display(int roomNr)
{
    std::cout << "\nReservation for room " << roomNr;
    std::cout << "\nCHECK-IN: " << arrival;
    std::cout << "\nCHECK-OUT: " << departure;
    std::cout << "\nBREAKFAST: " << (breakfast ? "Yes" : "No");
    std::cout << "\nEXTRA BED: " << (extraBed ? "Yes" : "No");
    std::cout << "\n\nTOTAL NIGHTS: " << numberOfDays;
    std::cout << "\n\nNames on reservation: ";
    //occupants->display_list();
}

void Reservasjon::writeDataToFile(std::ofstream &outFile)
{
	//occupant = new std::string[MAX_PAA_ROM];
	outFile << arrival << "\n" << departure << "\n" << numberOfDays << "\n";
	outFile << extraBed << "\n" << bedInUse << "\n" << numberOfOccupants << "\n";
		for (int i = 1; i <= numberOfOccupants; i++)
		{
			outFile << occupant[i] << "\n";
		}
}
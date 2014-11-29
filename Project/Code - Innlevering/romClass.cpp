/****************************************************************************
	class:        Rom (abstract)
	read:         n/a
	write:        n/a
	author:       ...

	description:  Base (parent) class for Singel, Dobbel and Suite classes
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <string>
#include "romClass.h"
#include "listtool2.h"
#include "reservasjonClass.h"
#include "globalFunctions.h"
#include <iostream>
#include <fstream>
/* --------------------------------------
             USED NAMESPACE
   -------------------------------------*/
using namespace std;

Rom::Rom() : Num_element(0)
{
	Reservations = new List(Sorted);
	roomNumber = 0;
	numberOfBeds = 1;
	breakfastIncluded = true;
}

Rom::Rom(int rID) : Num_element(rID)
{
    Reservations = new List(Sorted);
	roomNumber = rID;
	numberOfBeds = 1;
	breakfastIncluded = true;
}

Rom::Rom(ifstream &inFile, int nr) : Num_element(nr)
{
	int dato;
	int reservations;
	roomNumber = nr;
	inFile >> numberOfBeds >> breakfastIncluded;
	inFile >> reservations;
	Reservations = new List(Sorted);
		for (int i = 1; i <= reservations; i++)
		{
			inFile >> dato;
 			Reservasjon* nyReservation = new Reservasjon(inFile, dato);
			Reservations->add(nyReservation);
		}
}

/******************************************************************************
	name:        setReservation()
	description: Creates a new reservation for the current room object
	parameters:  int arrival, int departure, bool breakfast, bool extrabed
******************************************************************************/

Reservasjon* Rom::setReservation(int arrival, int departure, bool breakfast, bool extrabed)
{
	
    // Now set up the reservation with provided arguments and names ...
    Reservasjon* r = new Reservasjon(roomNumber, arrival, departure);
    r->setExtrabedInUse(extrabed);
    r->setBreakfast(breakfast);

    // Add our reservation to our list of reservations for this room, and return it
    Reservations->add(r);
	//Reservations->display_list();

    return r;
}

/******************************************************************************
	name:        getRoomNumber()
	description: Gets the number of the room instance ...
	return:  int
******************************************************************************/
int Rom::getRoomNumber()
{
    return roomNumber;
}

/******************************************************************************
	name:        isReserved()
	description: Checks if the room is booked on (or between) certain dates
	parameters:  int date, int nights
	return:      bool
******************************************************************************/
bool Rom::isReserved(int date, int nights)
{
	// If we have no reservations at all, there's no need to check ...
	if(Reservations->is_empty())
		return false;


    // We use a tm timestruct to make SURE our dates are correct when iterating later on...
    struct tm time;
    int correctedTime;

    // Lets set up that time struct...
    time.tm_year = date / 10000;
    time.tm_mon = (date % (time.tm_year * 10000)) / 100;
    time.tm_mday = (date % (time.tm_year * 10000)) % 100;
    time.tm_hour = 12;
    time.tm_min = 0;
    time.tm_sec = 0;
    mktime(&time);

    // Loop through the list from end to beginning
    for(int i = Reservations->no_of_elements(); i > 0; i--)
    {
        // ... and remove each element, one at the time ...
        Reservasjon* r = (Reservasjon*) Reservations->remove_no(i);

        // Now, if nights-parameter is set, we must check the status of the room
        // for several days ...
        if(nights > 0)
        {
            // Increment date by 1 ...
            for(int k=1; k<=nights; k++)
            {
                // Increment tm_mday, then run mktime to correct potentially invalid values
                time.tm_mday++;
                mktime(&time);

                // ... and now, format that to YYYYMMDD :)
                int correctedTime = (time.tm_year * 10000) + (time.tm_mon * 100) + time.tm_mday;

                // If this new time value is a value between the arrival and departure value of the reservation,
                // that would imply the room is already booked on that day ...
                if(correctedTime >= r->getArrival() && correctedTime <= r->getDeparture())
                {
					// ... and put our reservation back in the list...
					Reservations->add(r);
                    // If it's booked, just return -- no point in continuing
                    return true;
                }
            }
        }
        else
            if(date >= r->getArrival() && date <= r->getDeparture())
            {
				// ... and put our reservation back in the list...
				Reservations->add(r);
				// If it's booked, just return -- no point in continuing
                return true;
			}
    }

    return false;
}

/******************************************************************************
	name:        void removeReservationBy
	description: Iterates through all reservations looking for a specific name,
                 and asks the user if he wants to remove each reservation it finds
	parameters:  std::string name
	returns:     n/A
******************************************************************************/

//void Rom::removeReservationBy(std::string name)
//{
//    // Set up a copy of our reservations list ... because for
//    // some damn reason there's no way to iterate through it without
//    // removing the elements..
//    List cplist = *Reservations;
//
//
//    // Loop through the list beginning to end
//    for(int i = 0; i < cplist.no_of_elements(); i++)
//    {
//        // ... and remove each element, one at the time ...
//        Reservasjon* r = (Reservasjon*) cplist.remove();
//
//        if(*r == name.c_str())
//            r->display();
//
//        if(readChar("Would you like to remove it?", 'y','n') == 'y')
//        {
//            // Only if the user explicitly provided 'y' (or 'Y') will we remove it ...
//            delete r;
//        }
//    }
//
//}

void Rom::reservationByName(std::string name)
{
	for (int i = 1; i <= Reservations->no_of_elements(); i++)
	{
		Reservasjon* temp = (Reservasjon*) Reservations->remove_no(i);
		if (temp->sameNameAsReservation(name))
		{
			//cout << "Do you want to delete reservation: ";
			temp->display(roomNumber); //cout << "\n (y/n)";
			
			if(readChar("Delete reservation?", 'y','n') == 'y')
			{
				delete temp;
			}
			else
				Reservations->add(temp);
			//char command;
			//command = readCommand();
			//switch (command)
			//{
			//case 'y': delete temp; break;
			//case 'n': Reservations->add(temp); break;
			//}

		}
	}
	
}

void Rom::writeRomDataToFile(ofstream & outFile)
{
	outFile << roomNumber << "\n" << numberOfBeds << "\n" << breakfastIncluded << "\n";
	outFile << Reservations->no_of_elements() << "\n";
		for (int i = 1; i <= Reservations->no_of_elements(); i++)
		{
			Reservasjon* temp = (Reservasjon*) Reservations->remove_no(i);
			Reservations->add(temp);
			temp->writeDataToFile(outFile);
		}
}

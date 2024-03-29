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

Rom::Rom()
{
    Reservations = new List(Sorted);
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
    // Set up a sorted list ... we'll store the names in this one
    List* names = new List(FIFO);

    // Set up string to use for temporary name storage ...
    string tmp;

    cout << "\nWhat name would you like on the reservation?";
    cout << "\nNote: You can put several names on the reservation, but at least one.";

    // Ask user for name until user provides empty string ... Reservations can have multiple names...
    do
    {
        tmp = readString("Name (or blank when done)");

        // Add it to our list of names as a standard c-string
        names->add(new Text_element(tmp.c_str()));

    } while(!tmp.empty());

    // Now set up the reservation with provided arguments and names ...
    Reservasjon* r = new Reservasjon(roomNumber, names, arrival, departure);
    r->setExtrabedInUse(extrabed);
    r->setBreakfast(breakfast);

    // Add our reservation to our list of reservations for this room, and return it
    Reservations->add(r);
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
    // Set up a copy of our reservations list ... because for
    // some damn reason there's no way to iterate through it without
    // removing the elements..
    List cplist = *Reservations;

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
    for(int i = cplist.no_of_elements(); i > 0; i--)
    {
        // ... and remove each element, one at the time ...
        Reservasjon* r = (Reservasjon*) cplist.remove();

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
                    // If it's booked, just return -- no point in continuing
                    return true;
                }
            }
        }
        else
            if(date >= r->getArrival() && date <= r->getDeparture())
                // If it's booked, just return -- no point in continuing
                return true;
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

void Rom::removeReservationBy(std::string name)
{
    // Set up a copy of our reservations list ... because for
    // some damn reason there's no way to iterate through it without
    // removing the elements..
    List cplist = *Reservations;


    // Loop through the list beginning to end
    for(int i = 0; i < cplist.no_of_elements(); i++)
    {
        // ... and remove each element, one at the time ...
        Reservasjon* r = (Reservasjon*) cplist.remove();

        if(*r == name.c_str())
            r->display();

        if(readChar("Would you like to remove it?", 'y','n') == 'y')
        {
            // Only if the user explicitly provided 'y' (or 'Y') will we remove it ...
            delete r;
        }
    }

}

void Rom::writeRomDataToFile(ofstream & outFile)
{
	outFile << roomNumber << numberOfBeds << breakfastIncluded;
	outFile << Reservations->no_of_elements();
		for (int i = 1; i <= Reservations->no_of_elements(); i++)
		{
			Reservasjon* temp = (Reservasjon*) Reservations->remove_no(i);
			Reservations->add(temp);
			temp->writeDataToFile(outFile);
		}
}

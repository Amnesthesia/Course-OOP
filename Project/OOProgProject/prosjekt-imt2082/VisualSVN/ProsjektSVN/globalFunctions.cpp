/******************************************************************************
	file:         globalFunctions
	author:       Tommy B. Ingdal

	description:  this file contains all the global functions used
	by the program.
******************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "hotellClass.h"
#include "consts.h"
#include "globalFunctions.h"

/* --------------------------------------
              USED NAMESPACE
   -------------------------------------*/
using namespace std;
extern Timer tid;
extern int dagsdato;
extern Hotell * hotellet;

/* --------------------------------------
          Æ Ø Å (fjernes tilslutt)
   -------------------------------------*/
/*
æ: \x91
ø: \x9B
å: \x86
Æ: \x92
Ø: \x9D
Å: \x8F
*/

/******************************************************************************
	name:        int readNumber(string, int, int)
	description: displays text, reads and returns an int between min and max
	parameters:  string text, int minValue, int maxValue
	returns:     integer between minValue and maxValue
******************************************************************************/
int readNumber(string text, int min, int max)
{
	int number;

	do
	{
		cout << text << " (" << min << '-' << max << "): ";
		cin >> number;
	} while (number < min || number > max);

	return number;
}

/******************************************************************************
	name:        char readCommand()
	description: reads a char from user and returns the char in upper case
	parameters:  n/a
	returns:     character in upper case
******************************************************************************/
char readCommand()
{
    // Edited this function because readChar was more dynamic
    // and usable other places. Having both readChar and readCommand
    // and NOT making readCommand use readChar looked kind of weird.
    // Sorry for any inconvenience.
	return toupper(readChar("\n\nCommand: "));
}


/******************************************************************************
	name:        char readChar()
	description: Reads a single character and returns it as is
	parameters:  n/a
	returns:     char
******************************************************************************/
char readChar(string text)
{
    char c;
    cout << "\n\t" << text << ": ";
    cin >> c;
    cin.ignore();

    return c;
}

/******************************************************************************
	name:        char readChar()
	description: Reads a single character, and returns only if it matches alternative1 or alternative2
	parameters:  n/a
	returns:     char
******************************************************************************/
char readChar(string text, char alternative1, char alternative2)
{
    text = text + " (" + alternative1 + "/" + alternative2 + ")";

    char c = tolower(readChar(text));
    while(c != tolower(alternative1) && c != tolower(alternative2))
        c = tolower(readChar(text));

    return c;
}

/******************************************************************************
	name:        string readString()
	description: Reads a string from the user (wrapper function for getline used for semantics)
	parameters:  n/a
	returns:     string
******************************************************************************/

string readString(string text)
{
    cout << "\n\t" << text << ":";
    string tmp;

    getline(cin,tmp);
    return tmp;
}

/******************************************************************************
	name:        int readTime()
	description: Requests a date from the user (YYYYMMDD). Returns todays date by default.
	parameters:  n/a
	returns:     int
******************************************************************************/
int readTime(string text)
{
    int t;

    cout << "\n\t" << text << ": ";
    cin >> t;

    if(t < dagsdato || !t)
        return dagsdato;
    else
        return t;
}

/******************************************************************************
	name:        char readCommand()
	description: reads a char from user and returns the char in upper case
	parameters:  n/a
	returns:     character in upper case
******************************************************************************/

string makeString(char* c)
{
    string res;
    stringstream s;
    s << c;
    s >> res;

    return res;
}

/******************************************************************************
	name:        void showMenu()
	description: displays a menu and let's the user issue commands
	parameters:  n/a
	returns:     n/a
******************************************************************************/
void showMenu()
{
	char userCommand;

	cout << "\nHOTELLSYSTEM v0.1\n";
	cout << "-----------------\n";
	cout << "B - Bestill/reserver et rom\n";
	cout << "A - Avbestill et rom\n";
	cout << "I - Innsjekking\n";
	cout << "U - Utsjekking\n";
	cout << "R - Registrer regning p\x86 rom\n";
	cout << "E - Endre en reservasjon:\n";
	cout << "\tE1 - Endre ankomst og/eller avreisedato f\x9Br innsjekking\n";
	cout << "\tE2 - Endre avreisedato etter innsjekking\n";
	cout << "\tE3 - Bytte til et annet rom enn det tildelte\n";
	cout << "O - Vis oversikt over:\n";
	cout << "\tO1 - Hoveddata om ett hotell\n";
	cout << "\tO2 - Beskrivelse av alle suiter\n";
	cout << "\tO3 - Alle reservasjoner som st\x86r i en persons navn\n";
	cout << "\tO4 - N\x86r et rom er ledig\n";
	cout << "\tO5 - Alle reservasjoner p\x86 et rom\n";
	cout << "\tO6 - Alle data for ett roms n\x86v\x91rende beboer, inkl. regninger\n";
	cout << "\tO7 - Alle ledige rom i en kategori en gitt tidsperiode\n";
	cout << "T - Skriv hotelldata til fil\n";
	cout << "H - Bytte over til et annet hotell\n";

	userCommand = readCommand();
	switch (userCommand)
	{
	case 'O': overviewMenu(); break;
	case 'E': reservationsMenu(); break;
	case 'H': changeHotel(); break;
	case 'B': createReservation(); break;
	case 'A': removeReservation(); break;
	}

	// Recursive function call. Always show the menu, never exit the program:
	showMenu();
}

/******************************************************************************
	name:        void overviewMenu
	description: displays the overview sub menu to the user
	parameters:  n/a
	returns:     n/a
******************************************************************************/
void overviewMenu()
{
	char userCommand;
	extern Hotell * hotellet;

	cout << "O - Vis oversikt over:\n";
	cout << "\tO1 - Hoveddata om ett hotell\n";
	cout << "\tO2 - Beskrivelse av alle suiter\n";
	cout << "\tO3 - Alle reservasjoner som st\x86r i en persons navn\n";
	cout << "\tO4 - N\x86r et rom er ledig\n";
	cout << "\tO5 - Alle reservasjoner p\x86 et rom\n";
	cout << "\tO6 - Alle data for ett roms n\x86v\x91rende beboer, inkl. regninger\n";
	cout << "\tO7 - Alle ledige rom i en kategori en gitt tidsperiode\n";
	cout << "\tOQ - G\x86 tilbake til hovedmeny\n";

	userCommand = readCommand();

	while (userCommand != 'Q')
	{
		switch(userCommand)
		{
		case '1': hotellet->displayHotelData(); break;
		case '2': cout << "Beskrivelse av alle suiter\n"; break;
		case '3': cout << "Alle reservasjoner som st\x86r i en persons navn\n"; break;
		case '4': cout << "N\x86r et rom er ledig\n"; break;
		case '5': cout << "Alle reservasjoner p\x86 et rom\n"; break;
		case '6': cout << "Alle data for ett roms n\x86v\x91rende beboer, inkl. regninger\n"; break;
		case '7': cout << "Alle ledige rom i en kategori en gitt tidsperiode\n"; break;
		default: overviewMenu(); break;
		}
		showMenu();
	}
	showMenu();
}

/******************************************************************************
	name:        void reservationsMenu
	description: displays the reservation sub menu to the user
	parameters:  n/a
	returns:     n/a
******************************************************************************/
void reservationsMenu()
{
	char userCommand;

	cout << "E - Endre en reservasjon:\n";
	cout << "\tE1 - Endre ankomst og/eller avreisedato f\x9Br innsjekking\n";
	cout << "\tE2 - Endre avreisedato etter innsjekking\n";
	cout << "\tE3 - Bytte til et annet rom enn det tildelte\n";
	cout << "\tEQ - G\x86 tilbake til hovedmeny\n";

	userCommand = readCommand();

	while (userCommand != 'Q')
	{
		switch (userCommand)
		{
		case '1': cout << "Endre ankomst og/eller avreisedato f\x9Br innsjekking\n"; break;
		case '2': cout << "Endre avreisedato etter innsjekking\n"; break;
		case '3': cout << "Bytte til et annet rom enn det tildelte\n"; break;
		default: reservationsMenu(); break;
		}
		showMenu();
	}
	showMenu();
}

/******************************************************************************
	name:        void selectHotel
	description: Asks the user for the name of a hotel, then reads all the
				 available data from <forkortet hotellnavn>.dta
	parameters:  n/a
	returns:     hotel filename
******************************************************************************/
string selectHotel()
{
	string hotelName = "";							 // Contains the hotel name
	string filename = "";							 // Contains hotel filename

	do											 // Loop until we find a hotel:
	{
		cout << "Vennligst oppgi navn p\x86 hotell: ";
		getline(cin, hotelName);

		filename = searchHotel(hotelName);			// Holds the hotel filename
	} while (filename.length() == 0);		 // If filename is empty, try again

	return filename;						   // Return hotel filename to user
}

/******************************************************************************
	name:        string searchHotel
	description: Asks the user for a hotel, then searches for that specific
				 hotel in <Hoteller>.dta
	parameters:  string hotelName
	returns:     filename if the hotel exist
		         empty string if the hotel doesn't exist
******************************************************************************/
string searchHotel(string hotelName)
{
	string hotelFilename,		   // Contains the filename from <Hoteller.dta>
		   hotelLongName;        // Contains the hotel name from <Hoteller.dta>

			   // c_str() converts a regular string into the old c-string type:
	ifstream inFile(NAVN_PAA_HOTELLFIL.c_str(), ios::in);

	if (inFile)										   // File opened correcty:
	{
		while (!inFile.eof())					 // Loops until the end of file
		{
			inFile >> hotelFilename;				   // Read short hotel name
			inFile.ignore();				   // Ignore and discard whitespace
			getline(inFile, hotelLongName);				// Read long hotel name

			if (hotelLongName.compare(hotelName) == 0)			// Hotel exist:
			{
				return (hotelFilename + FILENDELSE).c_str(); // Return filename
			}
		}
		return "";			        // Hotel doesn't exist. Return empty string
	}
	else
	{	  // File doesn't exist. Return empty string and display error message:
		cout << "Error: Could not open file '" << NAVN_PAA_HOTELLFIL << "'\n";
		return "";
	}
	inFile.close();											  // Close the file
}

/******************************************************************************
	name:        void changeHotel()
	description: removes the current hotel from memory and asks the user
				 for a new hotel. It then creates a new hotel object
				 and reads data from <forkortet hotellnavn>.dta
	parameters:  n/a
	returns:     n/A
******************************************************************************/
void changeHotel()
{
	string hotelFilename;        // Variable which will hold the hotel filename
	extern Hotell * hotellet;  // Declare pointer as extern so we can access it

	// hotellet->writeToFile();                // Write hotel data back to file
	// delete hotellet;                // Delete the pointer and free up memory
	// hotelFilename = selectHotel();          // Asks the user for a new hotel
	// hotellet = new Hotell(hotelFilename);     // Create a new object on heap
}

/******************************************************************************
	name:        void writeHotelData
	description: Writes hotel data to file <forkortet hotellnavn.dta>
	parameters:  n/a
	returns:     n/A
******************************************************************************/
void writeHotelData()
{
	extern Hotell * hotellet;  // Declare pointer as extern so we can access it

	// hotellet->writeToFile();				   // Write hotel data back to file
}


/******************************************************************************
	name:        void createReservation
	description: Requests information from user to create a reservation
	parameters:  n/a
	returns:     n/A
******************************************************************************/

void createReservation()
{
    int roomtype, arrival, departure;
    bool breakfast = false, extrabed = false;

    cout << "\n\n\tAvailable room types: ";
    cout << "\n\t\t" << singel << ". Single";
    cout << "\n\t\t" << dobbel << ". Double";
    cout << "\n\t\t" << suite << ". Suite";

    // Select the room type by entering the ID of singel / dobbel / suite
    roomtype = readNumber("What type of room would you like to book?", singel, suite);

    // Select check-in and check-out dates ...
    arrival = readTime("Check-in date [YYYYMMDD] (default: today): ");
    departure = readTime("Check-out date [YYYYMMDD] (default: tomorrow): ");

    // If check-in and check-out are set to the same date (as is the case if the user
    // hit enter twice for default values), set departure to 1 day later than arrival,
    // i.e tomorrow if user selected default value for arrival (today)
    if(departure == arrival)
        departure = tid.nestedato(arrival);

    // If user wants breakfast included, set breakfast to true. Else keep as is.
    if(readChar("Include breakfast?", 'y', 'n') == 'y')
        breakfast = true;

    // If selected room type is double, ask if user requires extrabed
    if(roomtype == dobbel)
        if(readChar("Add extra bed?", 'y', 'n') == 'y')
            extrabed = true;

    // Create the reservation by first getting a randomly chosen available room at the hotel,
    // and then making the reservation for that room.
    hotellet->getAvailableRoom(arrival, tid.forskjell_datoer(arrival,departure), roomtype)
            ->setReservation(arrival, departure, breakfast, extrabed);

}

/******************************************************************************
	name:        void removeReservation
	description: Requests information (and confirmation) from user to remove a reservation
	parameters:  n/a
	returns:     n/A
******************************************************************************/
void removeReservation()
{
    string name = readString("Name on reservation");

    // Tell the hotel that the user wants to remove a reservation made by name
    hotellet->removeReservationBy(name);
}





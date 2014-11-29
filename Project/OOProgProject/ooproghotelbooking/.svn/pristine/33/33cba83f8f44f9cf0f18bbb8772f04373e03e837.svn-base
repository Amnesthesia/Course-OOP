/******************************************************************************
	file:         globalFunctions
	author:       Tommy & Victor

	description:  this file contains all the global functions used
	by the program.
******************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <iostream>											// For input/output
#include <string>												  // For string
#include <fstream>												 // For fstream
#include <sstream>												 // For sstream

#include "hotellClass.h"
#include "consts.h"
#include "globalFunctions.h"

/* --------------------------------------
          NAMESPACE, STD SYMBOLS
   -------------------------------------*/
using std::cout;													// For cout
using std::cin;														 // For cin
using std::string;												  // For string
using std::ifstream;											// For ifstream
using std::ios;													 // For ios::in
using std::stringstream;									// For stringstream

/* --------------------------------------
            EXTERN VARIABLES
   -------------------------------------*/
extern Hotell * hotellet;	   // Declare pointer as extern so we can access it
extern Timer tid;							    // Declare object as extern ...
extern int dagsdato;					      // Declare variable as extern ...

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
		cout << "\n" << text << " (" << min << '-' << max << "): ";
		cin >> number;
		cin.ignore();
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
	return toupper(readChar("\n\nCommand"));
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
    cout << "\n" << text << ": ";
    cin >> c;
    cin.ignore();

    return c;
}

/******************************************************************************
	name:        char readChar(string, char, char)
	description: Reads a single character, and returns only if it matches alternative1 or alternative2
	parameters:  string text, char alt1, char alt2
	returns:     char
******************************************************************************/
char readChar(string text, char alternative1, char alternative2)
{
    text = text + " (" + alternative1 + "/" + alternative2 + ")";

    char c = tolower(readChar(text));
    while(c != tolower(alternative1) && c != tolower(alternative2))
    {    
		c = tolower(readChar(text));
		cin.ignore();
	}

    return c;
}

/******************************************************************************
	name:        string readString(string)
	description: Reads a string from the user (wrapper function for getline used for semantics)
	parameters:  string text
	returns:     string
******************************************************************************/

string readString(string text)
{
    cout << "\n\t" << text << ": ";
    string tmp;

    getline(cin,tmp);
    return tmp;
}

/******************************************************************************
	name:        int readTime(string)
	description: Requests a date from the user (YYYYMMDD). Returns todays date by default.
	parameters:  string text
	returns:     int
******************************************************************************/
int readTime(string text)
{
    int t;
    
	do{
		cout << "\n" << text;
		cin >> t;
		cin.ignore();
	} while( t < 19000000); // Make sure it's at least 8 digits format

    if(t < dagsdato || !t)
	{
		cout << "\nNotice: You have entered a date that has already passed.";
		cout << "\nNotice: Date has automagically been changed.\n";
		return dagsdato;
	}
    else
        return t;
}

/******************************************************************************
	name:        char readCommand(char *)
	description: reads a char from user and returns the char in upper case
	parameters:  char * c
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
	// case 'T': hotellet->writeDataToFile(); break;
	}

	// Recursive function call. Always show the menu, never exit the program:
	showMenu();
}

/******************************************************************************
	name:        void overviewMenu()
	description: displays the overview sub menu to the user
	parameters:  n/a
	returns:     n/a
******************************************************************************/
void overviewMenu()
{
	char userCommand;

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
		case '2': hotellet->displaySuiteData(); break;
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
	name:        void reservationsMenu()
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
	name:        void selectHotel()
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
	name:        string searchHotel(string)
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
			    inFile.close();								  // Close the file
				return (hotelFilename + FILENDELSE).c_str(); // Return filename
			}
		}
		inFile.close();										  // Close the file
		return "";			        // Hotel doesn't exist. Return empty string
	}
	else
	{	  // File doesn't exist. Return empty string and display error message:
		cout << "Error: Could not open file '" << NAVN_PAA_HOTELLFIL << "'\n";
        inFile.close();										  // Close the file
		return "";
	}
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

	//hotellet->writeDataToFile();               // Write hotel data back to file
	delete hotellet;                     // Delete the pointer and free up memory
	hotelFilename = selectHotel();             // Asks the user for a new hotel
	hotellet = new Hotell(hotelFilename);        // Create a new object on heap
}

/******************************************************************************
	name:        void createReservation()
	description: Requests information from user to create a reservation
	parameters:  n/a
	returns:     n/A
******************************************************************************/

void createReservation()
{
    int roomtype, arrival, departure, rID;
    bool breakfast = false, extrabed = false;

	// To make sure the user enters a valid date, we'll make sure it's at least YYYYxxxx
	// Therefore we compare it against current years first day ... for that we need a 
	// time struct
	struct tm timeh;

    cout << "\n\nAvailable room types: ";
    cout << "\n\t" << singel << ". Single";
    cout << "\n\t" << dobbel << ". Double";
    cout << "\n\t" << suite << ". Suite";

    // Select the room type by entering the ID of singel / dobbel / suite
    roomtype = readNumber("What type of room would you like to book?", singel, suite);

	// Print user hint
	cout << "\nTip: Today is " << dagsdato << "\n";

    // Select check-in and check-out dates ... 
	// readTime automagically makes sure it's at least today
	
	// Verify that the correct dates have been specified, by looping if the user
	// says they were not.
	do
	{
		// Request check-in date
		arrival = readTime("Check-in date [YYYYMMDD] (must be today or later): ");
		
		// Request check-out date
		departure = readTime("Check-out date [YYYYMMDD]: ");

		// If check-in and check-out are set to the same date (as is the case if the user
		// hit enter twice for default values), set departure to 1 day later than arrival,
		// i.e tomorrow if user selected default value for arrival (today)
		if(departure == arrival)
			departure = tid.nestedato(arrival);

		// Inform the user of his choice (in case of automatic adjustment such as above, or from readTime)
		cout << "\nCheck-in date: " << arrival;
		cout << "\nCheck-out date: " << departure;

	} while(readChar("Is this correct?",'y','n') != 'y');
    


    // If user wants breakfast included, set breakfast to true. Else keep as is.
    if(readChar("Include breakfast?", 'y', 'n') == 'y')
        breakfast = true;

    // If selected room type is double, ask if user requires extrabed
    if(roomtype == dobbel)
        if(readChar("Add extra bed?", 'y', 'n') == 'y')
            extrabed = true;


	// Start the reservation process:
	Rom* r = hotellet->getAvailableRoom(arrival, departure, roomtype);

	// If room number is negative -- we have an error!
	rID = r->getRoomNumber();

	if(rID < 0)
	{
		switch(rID)
		{
		case noRoomOfSpecifiedTypeExists:
			cout << "\nThere are no rooms of the selected type at this hotel.";
			break;
		case noRoomOfSpecifiedTypeAvailable:
			cout << "\nNo rooms of the selected type are available between " << arrival << " and " << departure;
			break;
		}

		// We can pretty much stop trying here :(
		return;
	}

	// ... and if room ID was positive, we'll make a reservation :)
	r->setReservation(arrival, departure, breakfast, extrabed);


}

/******************************************************************************
	name:        void removeReservation()
	description: Requests information (and confirmation) from user to remove a reservation
	parameters:  n/a
	returns:     n/A
******************************************************************************/
void removeReservation()
{
    // Tell the hotel that the user wants to remove a reservation made by name
    hotellet->removeReservationBy(readString("Name on reservation"));
}
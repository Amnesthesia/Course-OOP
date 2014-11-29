/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include <iostream>
#include <string>

/* --------------------------------------
              USED NAMESPACE        
   -------------------------------------*/
using namespace std;

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

/****************************************************************************
	name:        int readNumber(string, int, int)
	description: displays text, reads and returns an int between min and max
	parameters:  string text, int minValue, int maxValue
	returns:     integer between min and max
*****************************************************************************/
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

/****************************************************************************
	name:        char readCommand()
	description: reads a command from user and returns a char in upper case
	parameters:  n/a
	returns:     character in upper case
*****************************************************************************/
char readCommand()
{
	char command;

	cout << "\n\nCommand (B, A, I, U, R, E, O, T, H, Q): ";
	cin >> command; cin.ignore();

	return toupper(command);
}

/****************************************************************************
	name:        void showMenu()
	description: displays a menu and let's the user issue commands
	parameters:  n/a
	returns:     n/a
*****************************************************************************/
void showMenu()
{
	char userCommand;

	cout << "HOTELLSYSTEM v0.1\n";
	cout << "-----------------\n";
	cout << "B - Bestill/reserver et rom\n";
	cout << "A - Avbestill et rom\n";
	cout << "I - Innsjekking\n";
	cout << "U - Utsjekking\n";
	cout << "R - Registrer regning p\x86 rom\n";
	cout << "E - Endre en reservasjon\n";
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
	cout << "Q - Avslutt program\n";

	userCommand = readCommand();
	while (userCommand != 'Q')
	{
		switch(userCommand)
		{
		default: showMenu(); break;
		}
		userCommand = readCommand();
	}
}
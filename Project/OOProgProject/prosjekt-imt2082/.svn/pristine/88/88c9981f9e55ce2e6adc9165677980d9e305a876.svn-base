#include <iostream>
#include <fstream>
using namespace std;

class Hotel
{
private:
	char * filnavn;

public:
	Hotel()
	{
		char hotelName[50];
		filnavn = NULL; // DEFAULT INIT. YOU SHOULD ALWAYS INITIALIZE YOUR POINTERS

		cout << "Please enter the name of the hotel: "; 
		cin.getline(hotelName, 50);

		if (!findHotel(hotelName))
		{
			cout << "Error: Could not find the hotel specified." << endl;
		}
	}

	char findHotel(char * hotelNameIn)
	{
		ifstream inFile("Hotels.dta", ios::in);
		char hotelShortFile[25],	// Forkortelse
			 hotelLongFile[25];		// Hele navnet

		if(inFile)
		{
			while (!inFile.eof())
			{
				inFile >> hotelShortFile; 
				inFile.ignore(); 
				inFile.getline(hotelLongFile, 25);

				if (!strcmp(hotelNameIn, hotelLongFile))	// If match
				{
					filnavn = new char[strlen(hotelShortFile)];
					strcpy(filnavn, hotelShortFile);	// Copy content into filnavn array.

					return 1;	// When you find a match, break out of the loop. This way you don't waste time and memory(?) itterating through the whole file.
				}
			}
		}
	}

	void showFilename() // DEBUG!!!
	{ 
		if (!filnavn == NULL)
		{
			cout << "Filname: " << filnavn << endl;
		}
	}
};



int main()
{
	Hotel hotelObject;
	hotelObject.showFilename();



	return 0;
}
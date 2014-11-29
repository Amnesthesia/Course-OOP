/******************************************************************************
	class:        Reg_Post
	read:         n/a
	write:        n/a

	description:  Contains all the data members and functions used by the
	              Reg_Post object
******************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include "reg_postClass.h"

#include <iostream>										    // For input/output
#include <string>												  // For string
#include <fstream>											 // For file stream
#include <ctype.h>												   // For ctype

using namespace std;

/******************************************************************************
	name:        Reg_Post()
	description: Constructor for Reg_Post -- initiates file reading process
				 as soon as a new Reg_Post object is initiated.
	parameters:  n/a
******************************************************************************/

Reg_Post::Reg_Post()
{
	readFromFile();					//runs readFromFile function in constructor
}
/******************************************************************************
	name:        ~Reg_Post()
	description: Destructor for Reg_Post -- deletes objects stored within Reg_Post
				 before dying.
	parameters:  n/a
******************************************************************************/
Reg_Post::~Reg_Post()
{
	delete [] descriptions;
}

/******************************************************************************
	name:        readFromFile()
	description: Reads data from disk into the Reg_Post object.
	parameters:  n/a
******************************************************************************/
void Reg_Post::readFromFile()
{
	ifstream inFile("reg_post.dta", ios::in);					   //opens file
		
	inFile >> numberOfServices;
	descriptions = new string[numberOfServices+1];		 //creates string array
	for (int i = 1; i <= numberOfServices; i++)
	{
		inFile >> descriptions[i];						   //fills string array
	}
	inFile.close();											      //closes file
}

/******************************************************************************
	name:        display()
	description: Displays data stored within the Reg_Post object
	parameters:  n/a
******************************************************************************/
void Reg_Post::display()
{
	for (int i = 1; i <= numberOfServices; i++)
	{
		cout << i << ": " << descriptions[i] << "\n";
	}
}

/******************************************************************************
	name:        std::string choice
	description: Allows the user to choose an available service 
	             (printed by display()) either by entering the number 
				 representing that service, or by entering the title of the
				 service.
				 User is allowed to enter text that is not listed, which allows
				 creation of services apart from those predefined.
				 Returns the title of the service as entered (or selected by ID).
	parameters:  n/a
	return:		 string
******************************************************************************/
string Reg_Post::choice()
{
	string valg;
	string text;
	int nr;
	cout << "Select number or write text: ";
	cin.sync(); getline(cin, valg);								 //reads choice

	if (isdigit(valg[0]))			 //checks if the first character is a digit
	{					 //if choice is a digit then convert to int and set nr:
		nr = atoi(valg.c_str());
		if (nr <= numberOfServices && nr >= 0)		//checks if choice is valid
		{
			text = descriptions[nr];   //sets string to the right data in array
			return text;				  //returns the string with description
		}
		else
		{													   //error message:
			cout << "Error: Invalid choice.";
			cout << "Press any key to continue";
			cin.ignore(); cin.get();									//pause
		}
		
	}
	else  //if not number, then free text, and returns that text as description
	{
		return valg;
	}
}
/*---------------------------------END-------------------------------------*/
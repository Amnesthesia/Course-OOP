/****************************************************************************
	class:        Suite (child)
	read:         n/a
	write:        n/a

	description:  inherits all properties from Rom class.
	              Suite also contains the following data members:
					(int) Number of beds +- the standard 4
					(int) Size of the suite (square meters)
					(char *) description of the suite
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include <string>
#include <iostream>
#include <fstream>

#include "romSuiteClass.h"

Suite::Suite()
{ 

}

Suite::Suite(int rID) : Rom(rID)
{

}
			  //receives pre-read data to constructor and runs Rom constructor:
Suite::Suite(std::ifstream &inFile, int nBeds, int bedMod, int sqremeters, std::string desc, int nr) : Rom(inFile, nr)
{							//sets data:
	numberOfBeds = nBeds;
	bedModifier = bedMod;
	squareMeters = sqremeters;
	description = new std::string();	//creates new string
}

void Suite::writeDataToFile(std::ofstream &outFile) //writes suite data to file
{
	outFile << numberOfBeds << "\n" << bedModifier << "\n" << squareMeters << "\n";
	writeRomDataToFile(outFile);							//rom's write data
}

void Suite::suiteReservationByName(std::string name)
{
	reservationByName(name);
}
/*---------------------------------END-------------------------------------*/
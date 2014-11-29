/****************************************************************************
	class:        Suite (child)
	read:         n/a
	write:        n/a
	author:       ...

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

Suite::Suite(std::ifstream &inFile, int nBeds, int bedMod, int sqremeters, std::string desc, int nr) : Rom(inFile, nr)
{
	numberOfBeds = nBeds;
	bedModifier = bedMod;
	squareMeters = sqremeters;
	description = new std::string();
}

void Suite::writeDataToFile(std::ofstream &outFile)
{
	outFile << numberOfBeds << "\n" << bedModifier << "\n" << squareMeters << "\n";
	writeRomDataToFile(outFile);
}

void Suite::suiteReservationByName(std::string name)
{
	reservationByName(name);
}
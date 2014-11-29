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
#include "romSuiteClass.h"
#include <string>
#include <iostream>
#include <fstream>

Suite::Suite()
{
}
Suite::Suite(std::ifstream &inFile, int nr) : Rom(inFile, nr)
{
	inFile >> numberOfBeds >> bedModifier >> squareMeters;

}

void Suite::writeDataToFile(std::ofstream &outFile)
{
	outFile << numberOfBeds << bedModifier << squareMeters;
	outFile << description;
	writeRomDataToFile(outFile);
}
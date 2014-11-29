/****************************************************************************
	class:        Dobbel (child)
	read:         n/a
	write:        n/a
	author:       ...

	description:  inherits all properties from Rom class
	Suite also contains the following data members:
	(bool) Extra beds
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include "romDobbelClass.h"
#include <string>
#include <iostream>
#include <fstream>

/* --------------------------------------
             USED NAMESPACE
   -------------------------------------*/
using namespace std;

Dobbel::Dobbel()
{
	cout << "Constructor..." << endl;
	extraBed = true;
}

Dobbel::Dobbel(int rID) : Rom(rID)
{

}

Dobbel::Dobbel(ifstream &inFile, bool extraBed1, int nr) : Rom(inFile, nr)
{
	extraBed = extraBed1;
}

void Dobbel::writeDataToFile(ofstream &outFile)
{
	outFile << extraBed << "\n";
	writeRomDataToFile(outFile);
}

void Dobbel::dobbleReservationByName(string name)
{
	reservationByName(name);
}

/****************************************************************************
	class:        Dobbel (child)
	read:         n/a
	write:        n/a

	description:  inherits all properties from Rom class
	              Suite also contains the following data members:
					(bool) Extra beds
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <string>                                                // For string
#include <iostream> // For iostream
#include <fstream> // For file stream
#include "romDobbelClass.h" // For romDobbel class

/* --------------------------------------
             USED NAMESPACE
   -------------------------------------*/
using namespace std;


Dobbel::Dobbel(int rID) : Rom(rID)	//constructor gets roomnr and sends to Rom
{
	extraBed = true;			   //sets extrabed to true, because double room
}
					//constructor with ifstream parameter, extra bed and roomnr
Dobbel::Dobbel(ifstream &inFile, bool extraBed1, int nr) : Rom(inFile, nr)
{
	extraBed = extraBed1;											//sets bool
}

void Dobbel::writeDataToFile(ofstream &outFile)//function to write data to file
{
	outFile << extraBed << "\n";	
	writeRomDataToFile(outFile);			   //runs Rom's write data function
}

void Dobbel::dobbleReservationByName(string name)
{
	reservationByName(name);
}
/*---------------------------------END-------------------------------------*/
/****************************************************************************
	class:        Singel (child)
	read:         n/a
	write:        n/a

	description:  inherits all properties from Rom class
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include "romSingelClass.h"
#include "romClass.h"
#include <iostream>
#include <fstream>
#include <string>

/* --------------------------------------
             USED NAMESPACE        
   -------------------------------------*/
using namespace std;

Singel::Singel()	
{
	cout << "Constructor..." << endl;
}

Singel::Singel(int rID) : Rom(rID)//runs rom constructor and sends romnr
{
	//no need for extra data
}

Singel::Singel(ifstream &inFile, int nr) : Rom(inFile, nr)
{
	//runs Rom constructor with ifstream and roomnr parameter
}

void Singel::writeDataToFile(ofstream &outFile)//write data to file function
{
	writeRomDataToFile(outFile);	//runs Rom's write function sends ofstream
}

void Singel::singleReservationByName(string name)
{
	reservationByName(name);
}
/*---------------------------------END-------------------------------------*/
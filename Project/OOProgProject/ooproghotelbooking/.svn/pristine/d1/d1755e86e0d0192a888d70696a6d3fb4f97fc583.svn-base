/****************************************************************************
	class:        Singel (child)
	read:         n/a
	write:        n/a
	author:       ...

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

Singel::Singel(ifstream &inFile, int nr) : Rom(inFile, nr)
{
}

void Singel::writeDataToFile(ofstream &outFile)
{
	writeRomDataToFile(outFile);
}
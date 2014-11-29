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
               INCLUDE GUARD        
   -------------------------------------*/
#if !defined(__ROMSUITECLASS_H)
#define __ROMSUITECLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include "romClass.h"
#include "listtool2.h"
#include <string>

class Suite : public Rom
{
private:
	int numberOfBeds;
	int bedModifier;
	int squareMeters;
	std::string * description;
public:
	Suite();
	Suite(std::ifstream &inFile, int nr);

	void writeDataToFile(std::ofstream &outFile);
};

#endif
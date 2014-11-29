/****************************************************************************
	class:        Singel (child)
	read:         n/a
	write:        n/a

	description:  inherits all properties from Rom class
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD        
   -------------------------------------*/
#if !defined(__ROMSINGELCLASS_H)
#define __ROMSINGELCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include <string>

#include "romClass.h"
#include "listtool2.h"

class Singel : public Rom
{
private:

public:
	Singel();
	Singel(int rID);
	Singel(std::ifstream &inFile, int nr);

	void writeDataToFile(std::ofstream & outFile);
	void singleReservationByName(std::string name);
};

#endif
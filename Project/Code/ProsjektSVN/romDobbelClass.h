/****************************************************************************
	class:        Dobbel (child)
	read:         n/a
	write:        n/a

	description:  inherits all properties from Rom class
	              Dobbel also contains the following data members:
					(bool) Extra beds
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD
   -------------------------------------*/
#if !defined(__ROMDOBBELCLASS_H)
#define __ROMDOBBELCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include "romClass.h"
#include "listtool2.h"

class Dobbel : public Rom
{
private:
	bool extraBed;
public:
	Dobbel();
	Dobbel(int rID);
	Dobbel(std::ifstream &inFile, bool extraBed1, int nr);
	void setExtrabedExists(bool e);
	void writeDataToFile(std::ofstream &outFile);
	void dobbleReservationByName(std::string name);
};

#endif

/****************************************************************************
	class:        Pris
	read:         <forkortet hotellnavn>.prs
	write:        n/a

	description:  Contains all the data members and methods for use in the
	              Pris class
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD        
   --------------------------------------*/
#if !defined(__PRISCLASS_H)
#define __PRISCLASS_H

/* -------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include "enums.h"
#include "timer2.h"
#include <string>

extern Timer tid;

class Pris
{
private:
	// Room cost
	std::string fileName;
	float singleRoom, doubleRoom, suiteRoom;
	float singleRoomWe, doubleRoomWe, suiteRoomWe;

	/* Trenger også en eller annen "datastruktur" for å representere resten av
	   fildataene for spesielle priser/tilbud i egne tidsperioder og for ulike
	   romtyper. Innspill? */
public:
	Pris(std::string);
	float* getPrice(int roomtype, int arrival, int departure, float * costPerDay);
	void setPrice(float value, int for_what, bool weekend = false);
	void setFile(std::string filename);
	void readDataFromFile();
};

#endif
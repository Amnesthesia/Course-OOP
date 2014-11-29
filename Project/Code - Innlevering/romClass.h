/****************************************************************************
	class:        Rom (abstract)
	read:         n/a
	write:        n/a
	author:       ...

	description:  Base (parent) class for Singel, Dobbel and Suite classes
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD
   -------------------------------------*/
#if !defined(__ROMCLASS_H)
#define __ROMCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include "listtool2.h"
#include <string>
#include "reservasjonClass.h"

class Rom : public Num_element
{
private:
	int roomNumber;			 // Romnummer
	int numberOfBeds;		 // Antall senger i dette rommet
	bool breakfastIncluded;  // Er frokost inkludert? (0/1)
	List * Reservations;	 // Liste over alle reservasjonene for dette rommet

public:
	Rom();
	Rom(int rID);
	Rom(std::ifstream &inFile, int nr);

	bool isReserved(int date, int nights = 0);
	int getRoomNumber();
	Reservasjon* setReservation(int arrival, int departure, bool breakfast, bool extrabed);
	//void removeReservationBy(std::string name);
	void writeRomDataToFile(std::ofstream & outFile);
	void reservationByName(std::string name);
};

#endif

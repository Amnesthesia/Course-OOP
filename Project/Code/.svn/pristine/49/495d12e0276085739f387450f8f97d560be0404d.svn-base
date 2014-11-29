/****************************************************************************
	class:        Rom (abstract)
	read:         n/a
	write:        n/a

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
#include <string>												  // For string
#include "listtool2.h"                                          // For listtool
#include "reservasjonClass.h"						   // For reservasjon class
#include "enums.h"												   // For enums


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
	~Rom();

	Reservasjon* reservationByDate(int date = tid.hent_dato(), int action = CHECKIN);
	Reservasjon* setReservation(int arrival, int departure, bool breakfast, bool extrabed);
	bool checkReservationData(std::string name, int checkinDate);
	bool isReserved(int date, int nights = 0);
	bool hasFutureReservations(){ if(Reservations->is_empty()) return false; else return true;}
	int getRoomNumber();
	void writeRomDataToFile(std::ofstream & outFile);
	void reservationByName(std::string name, int action = NOOP);
	void listReservations();
	void listReservationsGaps();
	void editReservation(std::string name, int date);
	void addBill();
};

#endif

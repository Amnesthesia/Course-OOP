/****************************************************************************
	class:        Hotell
	read:         <forkortet hotellnavn>.dta
	write:        <forkortet hotellnavn>.dta
	author:       ...

	description:  ...
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD
   --------------------------------------*/
#if !defined(__HOTELLCLASS_H)
#define __HOTELLCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include "enums.h"
#include "consts.h"
#include <string>
#include <time.h>
#include <stdlib.h>
#include "listtool2.h"
#include "romClass.h"

extern Timer tid;

class Hotell
{
private:
	std::string name;										 // Navn på hotellet
	std::string streetAddress;									  // Gateadresse
	std::string postAddress;								      // Postadresse
	std::string mailAddress;									 // Mail-adresse
	std::string fileName;							     // Filnavn (.dta-filen)

	int phoneNumber;										    // Telefonnummer
	int faxNumber;												   // Fax-nummer
	int breakfastCost;										 // Kostnad, frokost
	int additionalBedCost;								 // Kostnad, ekstra seng
	int numberOfFacilities;								   // Antall fasiliteter
	int numberOfSuites;											// Antall suites

	std::string * facilityDescriptions;  // Beskrivelse for fasiliteter
	std::string * suiteDesctiptions;	// Suite descriptions
	List * rooms[3];	   // Peker-array til romkategoriene; Singel, Dobbel, Suite

public:
	Hotell();
	Hotell(std::string);
	~Hotell();
	void displayHotelData();
	void displaySuiteData();
    Rom* getAvailableRoom(int checkin, int nights, int type = singel);    // Fetches an available room
    void removeReservationBy(std::string name);
	void writeDataToFile();
};

#endif
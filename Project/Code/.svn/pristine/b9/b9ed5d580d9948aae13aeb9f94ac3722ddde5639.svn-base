/****************************************************************************
	class:        Hotell
	read:         <forkortet hotellnavn>.dta
	write:        <forkortet hotellnavn>.dta

	description:  Contains all the data members and methods for use in the
	              Hotell class.
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD
   --------------------------------------*/
#if !defined(__HOTELLCLASS_H)
#define __HOTELLCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <string>                                                 // For string
#include <time.h>													// For time
#include <stdlib.h>												  // For cstlib
#include "timer2.h"                                               // For timer2
#include "enums.h"                                                 // For enums
#include "consts.h"                                               // For consts
#include "listtool2.h"                                          // For listtool
#include "prisClass.h"										  // For pris class

#include "romClass.h"                                         // For room class
#include "romSingelClass.h"                            // For single room class
#include "romDobbelClass.h"                            // For double room class
#include "romSuiteClass.h"                              // For suite room class
#include "regningClass.h"                                     // For bill class

class Hotell
{
private:
	std::string name;											  // Hotel name
	std::string streetAddress;								  // Street address
	std::string postAddress;								    // Post address
	std::string mailAddress;									// Mail address
	std::string fileName;							                // Filename

	int phoneNumber;										    // Phone number
	int faxNumber;												  // Fax number
	int breakfastCost;										  // Breakfast cost
	int additionalBedCost;								      // Extra bed cost
	int numberOfFacilities;							    // Number of facilities
	int numberOfSuites;									    // Number of suites


	std::string * facilityDescriptions;               // Facilities description
	std::string * suiteDescriptions;	                  // Suite descriptions
	       // Pointer array the all the different rooms; single, double, suite:
	List * rooms[3];
	
public:
	Hotell();
	Hotell(std::string);
	~Hotell();
	void displayHotelData();
	void displaySuiteData();
	void displayAvailableRooms();
	void displayReservationsOnRoom(int roomNr);
	void displayRoomAvailability(int roomNr);
	void checkOut();
	void changeRoomReservation();
	void changeRoom();
	void reservationsBy(std::string name, int action = NOOP);
	void writeDataToFile();
	void newBill();

	int getAdditionalBedCost(){ return additionalBedCost; }
	int getBreakfastCost() { return breakfastCost; }
	Rom* getRoom(int roomNr);
    Rom* getAvailableRoom(int checkin, int nights, int type = singel);
	List* getAvailableRooms(int checkin, int nights, int type = singel);
	std::string getFilename() { return fileName; }
};

#endif
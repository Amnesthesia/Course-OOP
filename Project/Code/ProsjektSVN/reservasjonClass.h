/****************************************************************************
	class:        Reservasjon
	read:         <forkortet hotellnavn.dta>
	write:        <forkortet hotellnavn.dta>

	description:  Contains all the data members and methods for use in the
	              Reservasjon object.
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD
   --------------------------------------*/
#if !defined(__RESERVASJONCLASS_H)
#define __RESERVASJONCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <string>												  // For string

#include "listtool2.h"											// For listtool
#include "consts.h"												  // For consts
#include "timer2.h"												  // For timer2
#include "globalFunctions.h"						    // For global functions
#include "enums.h"												   // For enums
#include "prisClass.h"										  // For pris class

extern Timer tid;

class Reservasjon : public Num_element
{
private:
    int roomID;             // ID of the room
	int arrival;			// Ankomstdato
	int departure;			// Avreisedato
	int checkIn[2];			// Timestamp for when the guest ACTUALLY checked in
	int checkOut[2];		// Timestamp for when the guest ACTUALLY checked out
	int numberOfDays;		// Antall d�gn (forskjellen p� ankomst og avreise)
	int numberOfOccupants;  // Antall beboere p� et rom
	int bedInUse;			// Om s� er tilfellet, er de i bruk (2) eller ei (1)
	float * costPrDay;		// Dette er tydeligvis et dynamisk array,
	bool breakfast;			// siden det skal inneholde priser for alle d�gn.
	bool extraBed;			// Da antar jeg vi bruker float * <variabel> og
							// og oppretter riktig st�rrelse for array runtime. Tanker?
	bool inUse;
	int numberOfBills;
	List * bills;			// FIFO-liste med regninger.
	Pris * costs;
	std::string * occupant; // Array med pekere til navnet p� beboerene.
	

public:
    Reservasjon();
	~Reservasjon();
	Reservasjon(int rID) : Num_element(rID) { roomID = rID; } // Used for error catching
    Reservasjon(int rID, int arr, int dep);
	Reservasjon(std::ifstream &inFile, int dato, int roomNr);

	bool sameNameAsReservation(std::string name);

	void addNewBill(std::string, float);

	// Getters
	int getArrival() { return arrival; } // Returns arrival date
    int getDeparture() { return departure; } // Returns departure date
	int getCheckinTime(){ return this->checkIn[1]; }
	int getCheckoutTime(){ return this->checkOut[1]; }
	int getCheckinDate(){ return this->checkIn[0]; }
	int getCheckoutDate(){ return this->checkOut[0]; }
	bool getInUse(){return this->inUse;}
	int getRoomID(){ return this->roomID; }

	std::string * getNameOfOccupant();

	// Setters
	void setCheckin(int date = 0, int time = 0);
	void setCheckout(int date = 0, int time = 0);
    void setExtrabedAvailable(bool e);
    void setExtrabedInUse(bool e);
    void setBreakfast(bool b);
	void setArrival(int arrivalDate);
	void setDeparture(int departureDate);

	// Output

	void display();
	void writeDataToFile(std::ofstream &outFile);
};

#endif
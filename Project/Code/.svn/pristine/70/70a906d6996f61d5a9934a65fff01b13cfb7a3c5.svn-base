/****************************************************************************
	class:        Reservasjon
	read:         <forkortet hotellnavn.dta>
	write:        <forkortet hotellnavn.dta>

	description:  Contains all the data members and methods used by the
	              Reservasjon object
*****************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include "hotellClass.h"
#include "reservasjonClass.h"
#include "regningClass.h"
#include <iostream>
#include <fstream>

/* --------------------------------------
          NAMESPACE STD SYMBOLS
   -------------------------------------*/
using std::cout;
using std::cin;

/* --------------------------------------
            EXTERN VARIABLES
   -------------------------------------*/
extern Hotell* hotellet;                    // Declare Hotell pointer as extern

/******************************************************************************
	name:        Reservasjon()
	description: Constructor for Reservasjon; requests information from the user
				 to create the reservation.
				 Parameters sent from Rom are room ID, and arrival + departure
				 date
	parameters:  int rID, int arr, int dep
******************************************************************************/
Reservasjon::Reservasjon(int rID, int arr, int dep) : Num_element(arr)
{
    Timer timecalc;                                             // Timer object
    arrival = arr;                                     // Assign arr to arrival
    departure = dep;                                 // Assign dep to departure
    numberOfDays = tid.forskjell_datoer(arrival,departure);   // Number of days
	bills = new List(FIFO);                           // Create a new FIFO list
	
    costPrDay = new float[numberOfDays];            // Create a new float array
	costs = new Pris(hotellet->getFilename());        // Create new Pris object

	if(rID > 300)                                     // If greater than 300...
		costPrDay = costs->getPrice(suite, arrival, departure, costPrDay);
	else if(rID > 200)                                // If greater then 200...
		costPrDay = costs->getPrice(dobbel, arrival, departure, costPrDay);
	else if (rID > 100)                               // If greater than 100...
		costPrDay = costs->getPrice(singel, arrival, departure, costPrDay);
	this->inUse = false;
	
	              // Ask user how many names (s)he wants on the reservation ...
	numberOfOccupants = readNumber("How many names would you like to put "
		                            "on your reservation?",0,MAX_PAA_ROM);

                                            // Set up our occupant string array
    occupant = new std::string[numberOfOccupants+1];

	                                                 // Request names from user
	for(int i = 1; i <= numberOfOccupants; i++)
	{
		occupant[i] = readString("Enter name");
	}
    roomID = rID;
}


/******************************************************************************
	name:        Reservasjon()
	description: Constructor for Reservasjon; creates a reservation from 
	             information read from file.
				 Parameters sent from Rom is a reference tothe file reading object, 
				 date (arrival date), and the room number
	parameters:  std::ifstream &infile, int dato, int roomNr
******************************************************************************/
Reservasjon::Reservasjon(std::ifstream &inFile, int dato, int roomNr) : Num_element(dato)
{
	occupant = new std::string[MAX_PAA_ROM];           // Create a string array
	bills = new List(FIFO);                               // Create a FIFO list
	roomID = roomNr;                                 // Assign roomNr to roomID
	arrival = dato;                                   // Assign dato to arrival
	inFile >> departure >> numberOfDays >> inUse;        // Read data from file
	costPrDay = new float[numberOfDays];                // Create a float array
	inFile.ignore();                            // Ignore and discard character

	                         // Loop through number of days and read from file:
	for (int i = 0; i < numberOfDays; i++)
	{
		inFile >> costPrDay[i]; inFile.ignore();
	}
	inFile >> extraBed >> bedInUse >> numberOfOccupants; // Read data from file
	inFile.ignore();                            // Ignore and discard character

	                                       // Loop through number of occupants:
	for (int i = 1; i <= numberOfOccupants; i++)
	{
		getline(inFile, occupant[i]);
	}
	inFile >> numberOfBills;                  // Read number of bills from file
	inFile.ignore();                            // Ignore and discard character

	                                           // Loop through number of bills:
	for (int i = 1; i <= numberOfBills; i++)
	{
		Regning* reg = new Regning(inFile);      // Create a new regning object
		bills->add(reg);                                        // Add new bill
	}
}


/******************************************************************************
	name:        ~Reservasjon()
	description: Destructor for Reservasjon. Deletes objects the reservation 
	             object should have in memory before the object dies.
	parameters:  n/a
******************************************************************************/
Reservasjon::~Reservasjon()
{
	// Removes bills unless, for some reason, bills has not been initialized

	if(bills != nullptr)
		delete bills;

	delete [] costPrDay;                     // Delete and free costPrDay array
  // If occupant isnt a null pointer (already deletes), delete and free memory:

	
	                           // costPrDay should always have been initialized
	delete [] costPrDay;

	    // Removes occupant, unless it for some reason has not been initialized
	     // This can happen if a Reservasjon object is created with the purpose
	                                      // of returning it with an error code
	if(occupant != nullptr)
		delete [] occupant;
}

/******************************************************************************
	name:        bool sameNameAsReservation
	description: Checks if a given name is contained within the occupants string
				 array; to see if a name is on a reservation or not. If it is,
				 the method returns true. Otherwise, returns false.
	parameters:  std::string name
	return:		 bool
******************************************************************************/
bool Reservasjon::sameNameAsReservation(std::string name)
{
	bool nameIsOnReservation = false;                      // Controll variable

	name = wordsToUpper(name);      // Converts name from lowercase(?) to upper

	                                            // Loops through each occupant:
	for(int i = 1; i <= numberOfOccupants; i++)
	{
		if(name.compare(occupant[i]) == 0)
			nameIsOnReservation = true;
	}
	           // Return true or false wether or not the name is on reservation
	return nameIsOnReservation;
}

/******************************************************************************
	name:        setExtrabedAvailable
	description: Sets the boolean for whether or not an extra bed is available
	parameters:  bool e
******************************************************************************/
void Reservasjon::setExtrabedAvailable(bool e)
{
    extraBed = e;                            // Set if a extra bed is available
}

/******************************************************************************
	name:        setExtrabedInUse
	description: Sets the value for whether or not the extra bed is available 
	             / in use
	parameters:  bool e
******************************************************************************/
void Reservasjon::setExtrabedInUse(bool e)
{
            // If an extrabed isn't available to begin with, set to 0 and exit:
    if(!extraBed)
    {
        bedInUse = 0;
        return;
    }
                         // Otherwise, if it's available, we want to set it to:
                                         // 1 - if bed exists but is not in use
                                                // 2 - bed exists and is in use
            // Therefore, we treat our boolean as an int and just increment it.
    bedInUse = (int)e+1;
}

/******************************************************************************
	name:        setBreakfast()
	description: Sets the boolean for whether or not the guest wants breakfast
	parameters:  bool b
******************************************************************************/
void Reservasjon::setBreakfast(bool b)
{
    breakfast = b;                        // Set if guest want breakfast or not
}

/******************************************************************************
	name:        setCheckin
	description: Sets a timestamp for when the user checked in (defaults to now),
				 and sets the inUse boolean to true.
	parameters:  int date, int time
******************************************************************************/
void Reservasjon::setCheckin(int date, int time)
{
	            // If we got a negative (or 0) date parameter, use current date
	if(!date)
		date = tid.hent_dato(); 
	            // If we got a negative (or 0) time parameter, use current time
	if(!time)
	{
		                                                // Get the current time
		int h, m, s;
		tid.hent_tid(h,m,s);
		   // We dont care about seconds, it's irrelevant for check-in time ...
		h *= 100;
		time = h + m;
	}

	                 // Set checkin[0] to our date, and checkin[1] to our time:
	this->checkIn[0] = date;
	this->checkIn[1] = time;
	
	this->inUse = true;
}

/******************************************************************************
	name:        setCheckout
	description: Sets a timestamp for when the user checked out. Defaults to 
	             today if no date is provided, and current time if no time is 
				 provided.
	parameters:  int date, int time
******************************************************************************/
void Reservasjon::setCheckout(int date, int time)
{
	            // If we got a negative (or 0) date parameter, use current date
	if(!date)
		date = tid.hent_dato(); 
	            // If we got a negative (or 0) time parameter, use current time
	if(!time)
	{
		                                                // Get the current time
		int h, m, s;
		tid.hent_tid(h,m,s);
		   // We dont care about seconds, it's irrelevant for check-in time ...
		h *= 100;
		time = h + m;
	}
	                // Set checkOut[0] to our date, and checkOut[1] to our time
	this->checkOut[0] = date;
	this->checkOut[1] = time;
}

/******************************************************************************
	name:        display()
	description: Displays all information about a reservation.
				 If checkout date for that reservation is today, and the guest is
				 currently checked in, it will also display the total cost for that
				 reservation.
	parameters:  n/a
******************************************************************************/
void Reservasjon::display()
{
	float expenses = 0;
	std::cout << "\nROOM NUMBER: " << roomID;
	std::cout << "\nCHECK-IN: " << arrival;
    std::cout << "\nCHECK-OUT: " << departure;
    std::cout << "\nBREAKFAST: " << (breakfast ? "Yes" : "No");
    std::cout << "\nEXTRA BED: " << (extraBed ? "Yes" : "No");
    std::cout << "\n\nTOTAL NIGHTS: " << numberOfDays;
    std::cout << "\n\nNames on reservation: ";

	for(int i = 0; i < this->numberOfOccupants; i++)
		std::cout << "\n\t" << (i+1) << ". " << occupant[i+1];
	
	// Displays bills if there are any linked to this reservation
	if(!bills->is_empty())
	{
		
		for(int b = 0; b < bills->no_of_elements(); b++)
		{
			Regning* r = (Regning*) bills->remove();
			std::cout << "\n\nEXPENSE #" << b << ": \n";
			std::cout << "\t" << r->getDescription();
			std::cout << "\n\t" << r->getTotalCost() << " " << VALUTA;
			expenses += r->getTotalCost();

			bills->add(r);
		}
	}

	// If the guest is checked in, displaying the reservation also
	// displays current expenses:
	if(inUse)
	{
		double weekdayCost = 0;
		double weekendCost = 0;
		double totalRoomCost = 0;

		std::cout << "\n\n###################################################";
		std::cout << "\n# TOTAL EXPENSES: " << expenses << " " << VALUTA;
		if(bedInUse ==2)
			std::cout << "\n#\t+ Extra bed: " << hotellet->getAdditionalBedCost() << " " << VALUTA;
		if(breakfast)
			std::cout << "\n#\t+ Breakfast: " << hotellet->getBreakfastCost() << " " << VALUTA;

		for(int i = 1; i < (departure-arrival); i++)
		{
			totalRoomCost += costPrDay[i];
		}
		
		std::cout << "\n# SUBTOTAL: " << expenses << " " << VALUTA;
		std::cout << "\n#\tRoom cost: " << totalRoomCost << " " << VALUTA << " (" << (departure-arrival) << " nights)";
		std::cout << "\n# -------------------------------------------------";
		std::cout << "\n# TOTAL: " << (expenses + totalRoomCost + 
			                        (bedInUse== 2 ? hotellet->getAdditionalBedCost() : 0) + 
									(breakfast ? hotellet->getBreakfastCost() : 0)) << " " << VALUTA;
		std::cout << "\n###################################################";

	}
}


/******************************************************************************
	name:        writeDataToFile
	description: Outputs data currently in a Reservasjon object to disk.
				 Takes a reference to the file output object.
	parameters:  std::ofstream &outfile
******************************************************************************/

void Reservasjon::writeDataToFile(std::ofstream &outFile)
{

	outFile << arrival << "\n" << departure << "\n" << numberOfDays << "\n";
	outFile << (inUse ? 1 : 0) << "\n";
	for (int i = 0; i < numberOfDays; i++)
	{
		outFile << costPrDay[i] << "\t";
	}
	outFile << "\n" << (extraBed ? 1 : 0)<< "\n" << (bedInUse ? 1 : 0) << "\n" << numberOfOccupants << "\n";
	for (int i = 1; i <= numberOfOccupants; i++)
	{
		outFile << occupant[i] << "\n";
	}
	numberOfBills = bills->no_of_elements();
	outFile << numberOfBills << "\n";
	for (int i = 1; i <= numberOfBills; i++)
	{
		Regning * temp = (Regning*) bills->remove();
		temp->writeBillToFile(outFile);
		bills->add(temp);
	}
}

/******************************************************************************
	name:        setArrival
	description: Sets the arrival date of the reservation to the integer passed
				 as parameter, as well as updates numberOfDays accordingly.
	parameters:  int arrivalDate
******************************************************************************/
void Reservasjon::setArrival(int arrivalDate)
{
	extern Timer tid;

	arrival = arrivalDate;
	numberOfDays = tid.forskjell_datoer(arrival, departure);
}

/******************************************************************************
	name:        setDeparture
	description: Sets the departureDate to the integer passed as parameter,
				 as well as updates numberOfDays accordingly.
	parameters:  int departureDate
******************************************************************************/
void Reservasjon::setDeparture( int departureDate )
{
	extern Timer tid;

	numberOfDays = tid.forskjell_datoer(arrival, departureDate);
	departure = departureDate;
}

/******************************************************************************
	name:        addNewBill
	description: Creates a new Regning object and appends on this reservations
				 list of bills, and increments amount of bills contained within
				 this object.
	parameters:  int departureDate
******************************************************************************/
void Reservasjon::addNewBill(std::string text, float cost)
{
	Regning* nyRegning = new Regning(text, cost);
	bills->add(nyRegning);
	numberOfBills++;
}
/*---------------------------------END-------------------------------------*/
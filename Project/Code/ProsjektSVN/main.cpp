/******************************************************************************
	created:		04/04/2013
	faculty:		IMT
	title:			Hotell Booking ftw!
	authors:		Halvor M. Thoresen, Tommy B. Ingdal, Victor Rudolfsson

	description:	A program to keep track of the guests at different hotels.
	                Guests can book, checkin, check out, order different kind
					of services (like Pay-TV, Internet) and so forth.
******************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <iostream>											// For input/output
#include <fstream>											  // For filestream
#include <string>										    // For string class
#include <cstdlib>												   // For srand
#include <cstdlib>                                               // For cstdlib

#include "listtool2.h"										   // For list tool
#include "timer2.h"								 // For time and date functions
#include "hotellClass.h"									// For hotell class
#include "reg_postClass.h"								  // For reg_post class
#include "globalFunctions.h"						    // For global functions

/* --------------------------------------
            GLOBAL VARIABLES
  -------------------------------------*/
Hotell * hotellet;									// Pointer to Hotell object
Reg_Post reg_post;									         // Reg_Post object
Timer tid;														  // Tid object
int dagsdato;													 // Todays date

/* --------------------------------------
               MAIN PROGRAM
   -------------------------------------*/
int main()
{
	srand(time(NULL));  // Generate the random seed - srand(0) will not work!!!
	dagsdato = tid.hent_dato();							     // Get todays date
	reg_post.readFromFile();                        // Get values from reg_post
	            // Displays a list over the available hotels in <Hoteller.dta>:
	displayAvailableHotels();
	                     // Create and allocate memory for a new hotell object:
	hotellet = new Hotell(selectHotel());

	showMenu();								    // Display the menu to the user

	return 0;                                     // Exit and terminate program
}
/*---------------------------------END-------------------------------------*/
/******************************************************************************
	created:		04/04/2013
	faculty:		IMT
	title:			...
	authors:		Halvor M. Thoresen, Tommy B. Ingdal, Victor Rudolfsson

	description:	...
******************************************************************************/

/* --------------------------------------
           INCLUDED DEPENDENCIES
   -------------------------------------*/
#include <iostream>											// For input/output
#include <fstream>											  // For filestream
#include <string>										    // For string class
#include <cstdlib>												   // For srand
#include "listtool2.h"										   // For list tool
#include "timer2.h"								 // For time and date functions
#include <cstdlib>

#include "hotellClass.h"									// For hotell class
#include "reg_postClass.h"								  // For reg_post class
#include "globalFunctions.h"						    // For global functions

/* --------------------------------------
          NAMESPACE STD SYMBOLS
   -------------------------------------*/
using std::string;

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
	string hotelFilename;
	srand(0);
	dagsdato = tid.hent_dato();
	hotelFilename = selectHotel();


	hotellet = new Hotell(hotelFilename);

	showMenu();

	return 0;
}

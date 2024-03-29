/****************************************************************************
	file:         const.h
	author:       ...

	description:  Contains all the constants used by the program
*****************************************************************************/
/* FOREL�PIGE CONSTS. LEGG TIL FLERE OM DET ER BEHOV FOR DET.
   ALDRI REFERER DIREKTE TIL EN TALLVERDI I PROGRAMMET.
   BRUK CONSTER                                            */

/* --------------------------------------
               INCLUDE GUARD        
   --------------------------------------*/
#if !defined(__CONSTS_H)
#define __CONSTS_H

const int NVNLEN = 50;
const int STRLEN = 70;
const int MAX_FASILITETER = 10;
const int MAX_PAA_ROM = 5;
const int MAX_RESERVASJONS_DOGN = 14;
const int STORSTE_ROMNR = 399;
const std::string NAVN_PAA_HOTELLFIL = "Hoteller.dta";
const std::string FILENDELSE = ".dta";
const std::string VALUTA = "NOK";

#endif
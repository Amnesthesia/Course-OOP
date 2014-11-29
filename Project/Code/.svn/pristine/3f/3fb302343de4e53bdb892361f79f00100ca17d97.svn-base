/****************************************************************************
	class:        Regning
	read:         <forkortet hotellnavn.dta>
	write:        <forkortet hotellnavn.dta>

	description:  Contains all the data members and methods for use in the
	              Regning class
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD        
   --------------------------------------*/
#if !defined(__REGNINGCLASS_H)
#define __REGNINGCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include <string>
#include "listtool2.h"

class Regning : public Element
{
private:
	std::string description;			// Beskrivelse, regningspost
	float totalCost;				    // Totalutgift for denne regningsposten
public:
	Regning(std::string, float);
	Regning(std::ifstream &inFile);

	void writeBillToFile(std::ofstream & outFile);
	float getTotalCost() { return totalCost; };
	std::string getDescription(){ return description; };
};

#endif
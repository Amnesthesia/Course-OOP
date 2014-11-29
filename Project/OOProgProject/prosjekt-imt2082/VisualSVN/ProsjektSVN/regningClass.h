/****************************************************************************
	class:        Regning
	read:         n/a
	write:        n/a
	author:       ...

	description:  ...
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

class Regning
{
private:
	std::string * description;			// Beskrivelse, regningspost
	float totalCost;				    // Totalutgift for denne regningsposten
public:

};

#endif
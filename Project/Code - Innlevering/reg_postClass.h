/****************************************************************************
	class:        Reg_Post
	read:         n/a
	write:        n/a
	author:       ...

	description:  ...
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD        
   --------------------------------------*/
#if !defined(__regpostCLASS_H)
#define __regpostCLASS_H

/* --------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/
#include <string>

class Reg_Post
{
private:
	int numberOfServices;		 // Antall standard/mest vanlige regningsposter
	std::string description;	 // Array med beskrivelse av de vanlige postene
public:

};

#endif
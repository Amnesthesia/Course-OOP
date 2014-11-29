/****************************************************************************
	class:        Reg_Post
	read:         <reg_post.dta>
	write:        n/a

	description:  Contains all the data members and methods for use in the
	              Reg_Post object.
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
	std::string * descriptions;	 // Array med beskrivelse av de vanlige postene
public:
	Reg_Post::Reg_Post();
	Reg_Post::~Reg_Post();

	void readFromFile();
	void display();
	std::string choice();

};

#endif
/* --------------------------------------
               INCLUDE GUARD        
   -------------------------------------*/
#if !defined(__GLOBALFUNCTIONS_H)
#define __GLOBALFUNCTIONS_H

/****************************************************************************
	name:        int readNumber(string, int, int)
	description: displays text, reads and returns an int between min and max
	parameters:  string text, int minValue, int maxValue
	returns:     integer between min and max
*****************************************************************************/
int readNumber(std::string text, int min, int max);


/****************************************************************************
	name:        char readCommand()
	description: reads a command from user and returns a char in upper case
	parameters:  n/a
	returns:     character in upper case
*****************************************************************************/
char readCommand();


/****************************************************************************
	name:        void showMenu()
	description: displays a menu to the user
	parameters:  n/a
	returns:     n/a
*****************************************************************************/
void showMenu();

#endif
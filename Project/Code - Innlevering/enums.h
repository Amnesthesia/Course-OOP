/****************************************************************************
	file:         enum.h
	author:       ...

	description:  Contains all the enums (enumerated lists) used by the 
	              program
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD        
   --------------------------------------*/
#if !defined(__ENUMS_H)
#define __ENUMS_H

enum romType {singel, dobbel, suite};
enum suiteRoomNumber {r301, r302, r303, r304, r305, r306, r307, r308, r309, r310};
enum errorCodes { noRoomOfSpecifiedTypeExists = -1, noRoomOfSpecifiedTypeAvailable = -2 };

#endif
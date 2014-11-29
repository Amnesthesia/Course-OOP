/****************************************************************************
	file:         enum.h

	description:  Contains all the enums (enumerated lists) used by the 
	              program
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD        
   --------------------------------------*/
#if !defined(__ENUMS_H)
#define __ENUMS_H

// Available room types (short hand for array keys in rooms[type] list)
enum romType {singel, dobbel, suite};

// Shorthand for suites array keys
enum suiteRoomNumber {r301, r302, r303, r304, r305, r306, r307, r308, r309, r310};

// Error codes returned as room number on reservations or rooms, when an 
// error occurs in a method returning a room or reservation objects.
enum errorCodes { noRoomOfSpecifiedTypeExists = -1, noRoomOfSpecifiedTypeAvailable = -2, roomNumberIsNotReserved = -3, reservationDoesNotExist = -4, reservationHasBeenPruned = -5 };

// Actions are used for modifying a reservation, as follows:
// NOOP - NO OPeration; does not modify the information in the reservation
// REMOVE - Asks the user whether or not to remove the reservation, and allows for removing it
// CHECKIN - Lets the user check in a reservation
// CHECKOUT - Lets the user check out a reservation
enum action { NOOP, REMOVE, CHECKIN, CHECKOUT};

#endif
/****************************************************************************
	class:        Pris
	read:         from <forkortet hotellnavn>.prs
	write:        n/a
	author:       ...

	description:  ...
*****************************************************************************/

/* --------------------------------------
               INCLUDE GUARD        
   --------------------------------------*/
#if !defined(__PRISCLASS_H)
#define __PRISCLASS_H

/* -------------------------------------
           INCLUDED DEPENDENCIES        
   -------------------------------------*/


class Pris
{
private:
	int costWeekday;// Vanlig pris, overnatting i uka (søn. kveld - fre. morgen)
	int costWeekend;// Vanlig pris, overnatting i helg (fre. kveld - søn. morgen)

	/* Trenger også en eller annen "datastruktur" for å representere resten av
	   fildataene for spesielle priser/tilbud i egne tidsperioder og for ulike
	   romtyper. Innspill? */
public:
};

#endif
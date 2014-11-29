//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_V02_2.TPL

//  Hovedrisset til eksamen i C++, 24.mai 2002, oppgave 2.
//  Laget av Frode Haug, HiG, mai 2002.
//  Litt endret/modifisert av FrodeH, HiG, v†ren 2003.


//  Programmet holder oversikt over en persons tegneseriesamling.
//  Nye serier og blader kan legges inn i datastrukturen.


                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  ifstream, ofstream
#include <cstring>           //  strlen, strcpy, strcmp
#include <cctype>            //  toupper
#include "listtool.h"        //  Ulike "verkt›y" fra "Listtool".

using namespace std;
                        //  CONST:
const int STRLEN     = 200;  //  Max. lengde for en tekst/streng.
const int MAX_SERIER = 100;  //  Max. antall serier i samlingen.

                        //  KLASSER:

//  Oppgave 2A:  Lag klassen "Blad"


class Serie  {               //  Klassen "Serie":
  private:
    char* tittel;            //  Full tittel/navn.
    char* utgiver;           //  Utgiver forlag.
    char* beskrivelse;       //  Generell info om serien.
    char* merknad;           //  Spesielle merknader.
    float hoyde, bredde;     //  seriens m†l (bredde og h›yde).
    int   ant_sider;         //  Antall sider i seriens blader.
    List* blader;            //  Liste med (alle) bladene i serien.

  public:
    Serie(char* t);          //  2x constructorer:
    Serie(char* t, istream* inn);      
    ~Serie()  { delete [] tittel;   delete [] utgiver;  delete [] beskrivelse;
                delete [] merknad;  delete blader;  }   // Overloading av "==":
    bool operator == (char* t)  { return ((strcmp(tittel, t) == 0) ?  true : false); }
    void endre_blad();       //  Endrer data om et blad.
    void skriv_serie();      //  Skriver ALLE data om en serie.
    void til_fil(ostream* ut);  //  Skriver serien til fil.
};

                        //  DEKLARASJON AV FUNKSJONER:
void skriv_meny();
char les();
int  finn_serie(char* t);
void ny_serie();             //  Oppgave 2B
void blad_endring();         //  Oppgave 2C
void display_en_serie();     //  Oppgave 2D
void les_fra_fil();          //  Oppgave 2E
void skriv_til_fil();        //  Oppgave 2F

                        //  GLOBALE VARIBLE:
Serie* samling[MAX_SERIER+1];   //  Peker-array til seriene (datastrukturen).
int    ant_brukt;               //  N†v‘rende antall serier.


int main()   {          //  HOVEDPROGRAM:
  char kommando;             //  Brukerens valg/›nske.

  les_fra_fil();                             //  Oppgave 2E

  skriv_meny();              //  Skriver aktuelle valg/muligheter.

  kommando = les();          //  Leser brukerens valg.
  while (kommando != 'Q')  {
    switch(kommando)  {
      case 'N': ny_serie();          break;  //  Oppgave 2B
      case 'B': blad_endring();      break;  //  Oppgave 2C
      case 'D': display_en_serie();  break;  //  Oppgave 2D
      case 'S': skriv_til_fil();     break;  //  Oppgave 2F
      default:  skriv_meny();      break;
    }
    kommando = les();        //  Leser brukerens valg.
  }
 return 0;
}


                        //  DEFINISJON AV KLASSE-FUNKSJONER:
Serie :: Serie(char* t)  {     //  Leser alle generelle data om en serie
                               //    vha. dialog med brukeren.
//  Oppgave 2b:  Lag innmaten
}
                               //  Leser ALLE data om en serie
                               //    (inkl. bladene) fra fil.
Serie :: Serie(char* t, istream* inn)  {

//  Oppgave 2e:  Lag innmaten
}
 

void Serie :: endre_blad()  {  //  Endrer data om et blad.

//  Oppgave 2c:  Lag innmaten
}

                             //  Skriver alle generelle data om en serie,
void Serie :: skriv_serie()  {    //  inkl. data om alle bladene til skjerm:

//  Oppgave 2d:  Lag innmaten
}

                             //  Skriver alle generelle data om en serie,
void Serie :: til_fil(ostream* ut)  {   //  inkl. data om alle bladene til fil:

//  Oppgave 2f:  Lag innmaten
}



                        //  DEFINISJON AV FUNKSJONER:
void skriv_meny()  {         //  Skriver meny/lovlige kommandoer til bruker:
  cout << "\n\n\nF›lgende kommandoer er lovlig:\n";
  cout << "\tN - Ny serie\n";
  cout << "\tB - Blad-endring\n";
  cout << "\tD - Display/skriv en serie\n";
  cout << "\tS - Skriv til fil\n";
  cout << "\tQ - Quit / avslutt\n";
}


char les()  {                //  Leser og returnerer ETT upcaset tegn.
  char ch;
  cout << "\n\nKommando:  ";   cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                            //  Leter etter og returnerer (om mulig) indeksen
                            //    for en serie med "tittel" lik "t".
int  finn_serie(char* t)  {        
  for (int i = 1;  i <= ant_brukt;  i++)
      if (*samling[i] == t)  return i;     //  Funn/match.
  return 0;                                //  Intet funn.
}


void ny_serie()  {           //  Oppgave 2B - Legger inn en totalt ny serie:

//  Oppgave 2B:  Lag innmaten
}


void blad_endring()  {       //  Oppgave 2C - Endrer data om ETT blad:

//  Oppgave 2C:  Lag innmaten
}


void display_en_serie()  {   //  Oppgave 2D - Skriver en serie til skjerm:

//  Oppgave 2D:  Lag innmaten
}


void les_fra_fil()  {        //  Oppgave 2E - Leser alle bladene fra fil:

//  Oppgave 2E:  Lag innmaten
}


void skriv_til_fil()  {      //  Oppgave 2F - Skriver alle bladene til fil:

//  Oppgave 2F:  Lag innmaten
}

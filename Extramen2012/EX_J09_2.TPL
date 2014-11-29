//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J09_2.TPL

//  Hovedrisset til kontinuasjonseksamen i OOP, 5.januar 2009, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2008.


//  Programmet holder orden p† EN banks ulike kunder og deres
//      l†n i banken (til hvilken rente).
//
//  Det er mulig †:
//      - skrive alle data om en kunde (til skjerm)        (oppgave 2A)
//      - foreta en innbetaling for en kunde               (oppgave 2B)
//      - endre en kundes "program" (l†neprosent)          (EXTRA)
//      - endre et "programs" l†neprosent                  (oppgave 2C)
//      - legge inn en ny l†nekunde                        (oppgave 2D)
//      - sende ut varsling til ALLE om termininnbetaling  (oppgave 2E)
//      - alle kj›ret›y skrives til fil                    (oppgave 2F) 
//      - alle kj›ret›y leses fra fil                      (oppgave 2G)

                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  i(f)stream, o(f)stream
#include <cstring>           //  strlen, strcpy
#include <cctype>            //  toupper
#include <cstdlib>           //  atoi, atof
#include "listtool.h"        //  "Verkt›ykasse" for listeh†ndtering.

using namespace std;

                        //  CONST:
const int   STRLEN      =       80;  //  Standard streng-lengde (i array).
const int   ANTPROGRAM  =        5;  //  Antall ulike l†neprogram banken har.
const int   MAXLAANEAAR =       25;  //  Max. antall l†ne†r.
const int   MINKONTO    =  1000000;  //  Nummer p† f›rste kontonummer.
const int   MAXKONTO    =  9999999;  //  Nummer p† siste kontonummer.
const int   MINLAAN     =    10000;  //  Min. bel›p p† l†n (10-tusen).
const int   MAXLAAN     = 10000000;  //  Max. bel›p p† l†n (10 mill.).
const float MAXPROSENT  =    30.0F;  //  Max. prosent for/p† et l†n.



                        //  KLASSER:
class Kunde : public Num_element  {
  private:                        //  number = kundens ID/kontonummer.
    char  * navn,                 //  Navn.
          * adr,                  //  Adresse (gate og sted).
          * mail;                 //  Mail-adresse.
    int   tlf,                    //  Telefon (fast eller mobil).
          program,                //  L†neprogramnummer (= 1-5).
          ant_aar;                //  Antall †r l†net g†r over.
    float belop,                  //  N†v‘rende l†nebel›p.
          avdrag;                 //  M†nedlig fast avdragsbel›p.

  public:
    Kunde(int nr);                    //  Lag innmaten ifm. oppgave 2D.
    Kunde(int nr, istream* inn);      //  Lag innmaten ifm. oppgave 2G.
    ~Kunde()  {  delete [] navn;  delete [] adr;  delete [] mail;  }
    void display();                   //  Lag innmaten ifm. oppgave 2A.
    void innbetaling();               //  Lag innmaten ifm. oppgave 2B.
    void varsel(ostream* ut);         //  Lag innmaten ifm. oppgave 2E.
    void skriv_til_fil(ostream* ut);  //  Lag innmaten ifm. oppgave 2F.
};

class Program  {
  private:
    char* beskrivelse;            //  Beskrivelse av l†neprogrammet.
    float prosent;                //  N†v‘rende l†neprosent p† programmet.

  public:
    Program(char* t, float p);        //  Lag innmaten ifm. oppgave 2G.
    ~Program() {  delete [] beskrivelse;  }
    void endre_prosent();             //  Lag innmaten ifm. oppgave 2C.
    float hent_prosent()   {  return prosent;  }
    void skriv_til_fil(ostream* ut);  //  Lag innmaten ifm. oppgave 2F.
};


                        //  DEKLARASJON AV FUNKSJONER:
void  skriv_meny();
char  les();
int   les(char* t, const int MIN, const int MAX);
float les(char* t, const float MAX);
void  les(const char t[], char s[], const int LEN);
void  skriv();                          //  Lag innmaten ifm. oppgave 2A.
void  innbetaling();                    //  Lag innmaten ifm. oppgave 2B.
void  endre_program();                  //  Lag innmaten ifm. oppgave 2C.
void  ny_kunde();                       //  Lag innmaten ifm. oppgave 2D.
void  varsling();                       //  Lag innmaten ifm. oppgave 2E.
void  skriv_til_fil();                  //  Lag innmaten ifm. oppgave 2F.
void  les_fra_fil();                    //  Lag innmaten ifm. oppgave 2G.


                        //  GLOBALE VARIABLE:
List* kunder;                         //  Listen med alle l†nekundene.
Program* programmer[ANTPROGRAM+1];    //  Array med de ulike programmene.

                        //  HOVEDPROGRAM:
int main()  {
  char valg;

  kunder = new List(Sorted);
  les_fra_fil();                         //  Oppgave 2G
  
  skriv_meny();
  valg = les();
  while (valg != 'Q')  {
    switch(valg)  {
      case 'S': skriv();         break;  //  Oppgave 2A
      case 'I': innbetaling();   break;  //  Oppgave 2B
      case 'P': endre_program(); break;  //  Oppgave 2C
      case 'N': ny_kunde();      break;  //  Oppgave 2D
      case 'V': varsling();      break;  //  Oppgave 2E
      default:  skriv_meny();    break;
	}
    if (valg == 'I'  ||  valg == 'K'  ||  valg == 'P'  ||  valg == 'N') 
       skriv_til_fil();                  //  Oppgave 2F
    valg = les();
  }
  cout << "\n\n";
  return 0;
}



// *************************************************************************
// ******************  DEFINISJON AV MEDLEMS-FUNKSJONER:  ******************
// *************************************************************************


// ********************************  KUNDE:  ******************************

Kunde::Kunde(int nr) :  Num_element(nr)  {  //  Oppgave 2D - Leser ALLE data:
//  Lag innmaten
}

                                            //  Oppgave 2G - Leser ALT fra fil:
Kunde::Kunde(int nr, istream* inn) :  Num_element(nr)  {
//  Lag innmaten
}


void Kunde::display()  {               //  Oppgave 2A - Skriver ALT til skjerm:
//  Lag innmaten
}


void Kunde::innbetaling()  {           //  Oppgave 2B - Trekker fra innbetaling:
//  Lag innmaten
}


void Kunde::varsel(ostream* ut)  {     //  Oppgave 2E - Innbet.varsel til fil:
//  Lag innmaten
}


void Kunde::skriv_til_fil(ostream* ut)  {   //  Oppgave 2F - Skriver til fil:
//  Lag innmaten
}



// ********************************  PROGRAM:  ******************************

Program::Program(char* t, float p)  {     //  Oppgave 2G - Setter ALLE verdier:
//  Lag innmaten
}


void Program::endre_prosent()  {        //  Oppgave 2C - Endrer l†neprograms %:
//  Lag innmaten
}


void Program::skriv_til_fil(ostream* ut)  { //  Oppgave 2F - Skriver til fil:
//  Lag innmaten
}


// ****************************************************************************
// ******************   DEFINISJON AV (GLOBALE) FUNKSJONER:  ******************
// ****************************************************************************

void skriv_meny()  {         //  Skriver alle mulige menyvalg:
  cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   S  - Skriv ALLE data om EN kunde"
       << "\n   I  - Innbetaling fra en kunde"
       << "\n   P  - endre et Programs l†neprosent"
       << "\n   N  - Ny kunde/l†n"
       << "\n   V  - Varsle ALLE om termininnbetaling"
       << "\n   Q  - Quit / avslutt";
}


char les()  {                //  Leser og upcaser brukerens valg/›nske:
  char ch;
  cout << "\n\nKommando: ";
  cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                             //  Leser en INT mellom MIN og MAX:
int les(char* t, const int MIN, const int MAX)  {
  char text[STRLEN];
  int n;
  do  {
    cout << '\t' << t << " (" << MIN << '-' << MAX << "): ";
    cin.getline(text, STRLEN);   n = atoi(text);  // Leser som tekst - omgj›r:
  } while (n < MIN  ||  n > MAX);
  return n;
}

                             //  Leser en FLOAT mellom 0.1 og MAX:
float les(char* t, const float MAX)  {
  char text[STRLEN];
  float n;
  do  {
    cout << '\t' << t << " (0.1-" << MAX << "): ";
    cin.getline(text, STRLEN); 	n = atof(text);  // Leser som tekst - omgj›r:
  } while (n < 0.1  ||  n > MAX);
  return n;
}

                             //  Leser inn en ikke-blank tekst:
void les(const char t[], char s[], const int LEN) {  
  do  {
    cout << '\t' << t << ": ";    //  Skriver ledetekst.
    cin.getline(s, LEN);          //  Leser inn tekst.
  } while (strlen(s) == 0);       //  Sjekker at tekstlengden er ulik 0.
}


void skriv()  {              //  Oppgave 2A - Skriv ALLE data om EN kunde:
//  Lag innmaten
}


void innbetaling()  {        //  Oppgave 2B - EN kunde foretar innbetaling:
//  Lag innmaten
}


void endre_program()  {      //  Oppgave 2C - Endre et programs l†neprosent:
//  Lag innmaten
}


void ny_kunde()  {           //  Oppgave 2D - Legge inn en ny kunde/l†n:
//  Lag innmaten
}


void varsling()  {           //  Oppgave 2E - Terminvarsel til ALLE:
//  Lag innmaten
}


void skriv_til_fil()  {    //  Oppgave 2F - Skriv HELE datastrukturen til fil:
//  Lag innmaten
}


void les_fra_fil()  {      //  Oppgave 2G - Leser HELE datastrukturen fra fil:
//  Lag innmaten
}

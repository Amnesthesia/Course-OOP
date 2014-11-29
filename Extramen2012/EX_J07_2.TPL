//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J07_2.TPL

//  Hovedrisset til kontinuasjonseksamen i C++, 5.januar 2007, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2006.


//  Programmet holder orden på hvilke personer som deltar i trekningen,
//  og har vunnet, på de ulike dagene i advent (1.-24.desember).
//
//  Det er mulig å:
//      - skrive ut alle data (primært deltagerne og vinnerne) for en gitt dag.
//      - bytte til en ny aktuell/relevant dag å arbeide med (nye/trekke).
//      - legge inn en ny deltager på en aktuell/gitt dag.
//      - foreta trekning av vinnere for/på en aktuell/gitt dag.
//      - hele datastrukturen leses fra/skrives til fil.


                        //  INCLUDE:
#include <iostream>           //  cin, cout
#include <fstream>            //  i(f)stream, o(f)stream
#include <cstring>            //  strlen, strcpy
#include <cctype>             //  toupper
#include <cstdlib>            //  (s)rand
#include <ctime>              //  time (ifm. srand)
#include "listtool.h"         //  "Verktøykasse" for listehåndtering.

using namespace std;

                        //  CONST:
const int STRLEN   =  80;     //  Max. streng-lengde.
const int ANTDAGER =  24;     //  Antall dager i desember (til julekvelden).


                        //  KLASSER:
class Deltager : public Num_element  {
  private:                    //  Deltagerens telefon ligger i "number".
    char* navn, *adr;         //  Deltagerens navn og adresse.
  
  public:                     //  Funksjons-deklarasjoner:
    Deltager(int n);
    Deltager(int n, istream* inn);
    void display();
    void skriv_til_fil(ostream* ut); 
};


class Dag  {                  //  En ukedag i desember (1.-24.).
  private:
    bool trukket;             //  Er dagens trekning foretatt eller ei.
    List* deltagere,          //  Liste av trekningsdeltagere.
        * vinnere;            //  Liste av trekningsvinnere.
  public:
    Dag();                      //  Funksjons-deklarasjoner:
    bool er_trukket()  {  return trukket;  }
    void display();
    void ny();
    void trekk();
    void skriv_til_fil(ostream* ut); 
    void les_fra_fil(istream* inn);
};


                        //  DEKLARASJON AV FUNKSJONER:
void skriv_meny();
char les_kommando();
int  les(char* t, const int MIN, const int MAX);
void initier();
void bytt_dag();
void skriv_til_fil();
void les_fra_fil();
void trekk();


                        //  GLOBALE VARIABLE:
Dag* dagene[ANTDAGER+1];    //  Alle desemberdagene, bruker fra indeks nr.1-24.
int idag = 0;               //  Aktuell/relevant som det egges inn deltagere på.


                        //  HOVEDPROGRAM:
int main()  {
  char valg;

  srand((unsigned)time( NULL ));             //  Tall trekkes HELT tilfeldig.
  initier();                                 //  Oppgave 2A
  les_fra_fil();                             //  Oppgave 2F
  bytt_dag();                                //  Oppgave 2C

  skriv_meny();
  valg = les_kommando();
  while (valg != 'Q')  {
    switch(valg)  {
      case 'S': /*  Oppgave 2B: Lag manglende kode(linje)  */  break;
      case 'B': bytt_dag();          break;  //  Oppgave 2C
      case 'N': /*  Oppgave 2D: Lag manglende kodelinje    */  break;
      case 'T': trekk();             break;  //  Oppgave 2G
      default:  skriv_meny();        break;
    }
    valg = les_kommando();
  }

  skriv_til_fil();                           //  Oppgave 2E
  cout << "\n\n";
  return 0;
}


                        //  DEFINISJON AV MEDLEMS-FUNKSJONER:

//***************************  DELTAGER:  ***************************
Deltager::Deltager(int n) : Num_element(n)  { // Setter/leser ALLE dets data:
//  Oppgave 2D: Lag innmaten
}
                                              //  Leser ALLE dets data fra fil:
Deltager::Deltager(int n, istream* inn) : Num_element(n)  {
//  Oppgave 2F: Lag innmaten
}

void Deltager::display()  {                   // Skriver ALLE dets data:
//  Oppgave 2B: Lag innmaten
}

void Deltager::skriv_til_fil(ostream* ut)  { // Skriver ALLE dets data til fil:
//  Oppgave 2E: Lag innmaten
}


//******************************  DAG:  *****************************

Dag::Dag() {                                  //  Initierer ALLE dets data:
//  Oppgave 2A: Lag innmaten
}

void Dag::display()  {                        //  Skriver ALLE dets data:
//  Oppgave 2B: Lag innmaten
}

void Dag::ny()  {                             //  Legger inn ny deltager:
//  Oppgave 2D: Lag innmaten
}

void Dag::skriv_til_fil(ostream* ut)  {  //  Skriver ALT om EN dag til fil:
//  Oppgave 2E: Lag innmaten
}

void Dag::les_fra_fil(istream* inn)  {  //  Leser ALT om EN dag fra fil:
//  Oppgave 2F: Lag innmaten
}

void Dag::trekk()  {                    //  Foretar evt. trekning av vinnere:
//  Oppgave 2G: Lag innmaten
}


                        //  DEFINISJON AV (GLOBALE) FUNKSJONER:
void skriv_meny()  {                 //  Skriver alle mulige menyvalg:
  cout << "\n\nFØLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   S  - Skriv en dag"
       << "\n   B  - Bytt til/sett ny aktuell dag"
       << "\n   N  - Ny deltager"
       << "\n   T  - foreta Trekning på aktuell dag"
       << "\n   Q  - Quit / avslutt"
	   << "\n\n   Aktuelt/nåværende dagnummer: " << idag;
}


char les_kommando()  {               //  Leser og upcaser brukerens valg/ønske:
  char ch;
  cout << "\n\nKommando: ";
  cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                                     //  Leser et tall mellom MIN og MAX:
int les(char* t, const int MIN, const int MAX)  {
  int n;
  do  {
     cout << '\t' << t << " (" << MIN << '-' << MAX << "): ";
     cin >> n;  cin.ignore();
  } while (n < MIN  ||  n > MAX);
  return n;
}


void initier()  {                    //  Initierer alle de 24 dagene:
//  Oppgave 2A: Lag innmaten
}

void bytt_dag()  {                   //  Bytter til annen/ny aktuell dag:
//  Oppgave 2C: Lag innmaten
}

void skriv_til_fil()  {                //  Skriver HELE datastrukturen til fil:
//  Oppgave 2E: Lag innmaten
}

void les_fra_fil()  {                  //  Leser HELE datastrukturen fra fil:
//  Oppgave 2F: Lag innmaten
}

void trekk()  {                      //  Foretar evt. trekning på aktuell dag:
//  Oppgave 2G: Lag innmaten
}

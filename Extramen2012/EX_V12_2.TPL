//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_V12_2.TPL

//  Hovedrisset til eksamen i OOP, 1.juni 2012, oppgave 2.
//  Laget av Frode Haug, HiG, mai 2012.


//  Programmet holder orden p† to ulike klubbers fotballfans og hvordan 
//    disse fordeler seg p† ulike hoteller i en og samme by.

//  Det er mulig †:
//      - f† antall ulike fan p† de ulike hoteller          (Oppgave 2A)
//      - f† oversikt over de ulike fan p† ETT hotell       (Oppgave 2B)
//      - la en gjest dra fra et hotell                     (Oppgave 2C)
//      - la en gjest ankomme et hotell                     (Oppgave 2D)
//      - finne en navngitt person                          (Oppgave 2E)
//      - Lese hele datastrukturen fra fil                  (Oppgave 2F) 


                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  i(f)stream, o(f)stream
#include <cstring>           //  strlen, strcpy, strcmp
#include <cctype>            //  toupper
#include "listtool.h"

using namespace std;

                        //  CONST og ENUM:
const int STRLEN    =       120;   //  Max. streng-lengde.
const int MAXHOTELL =        30;   //  Max. antall hoteller i Manhester.
const int MAXROMNR  =      9999;   //  Max. romnummer p† ett hotell.
const int MINPID    =         1;   //  Min. personnummer/-ID.
const int MAXPID    = 999999999;   //  Max. personnummer/-ID.
enum  kategori { City, United, Noytral };  //  En gjests/fans kategori/type.


                        //  KLASSER:
class Hotell  {
  private:
    char* navn;              //  Hotellets navn.
    char* data;              //  Alle andre data (adresse, tlf, ...)
    int   ant_C,             //  Antall City-fans p† hotellet.
          ant_U,             //  Antall United-fans p† hotellet.
          diff;              //  Max. differanse (antall) p† C- og U-fans.
    List* gjester;           //  Gjestene som for ›yeblikket er p† hotellet.

  public:
    Hotell(istream* inn);              //  Lag innmaten ifm. oppgave 2F.
    ~Hotell();                                //  (Ferdigkodet)
    bool inneholder(int nr);                  //  (Ferdigkodet)
    void skriv();                             //  (Ferdigkodet)
    void hent_antall(int & an_C, int & an_U); //  (Ferdigkodet)
    void skriv2();                     //  Lag innmaten ifm. oppgave 2B. 
    void slett(int nr);                //  Lag innmaten ifm. oppgave 2C.
    bool innlosjer(kategori kat2, int nr); // Lag innmaten ifm. oppgave 2D.
    bool finn_og_skriv(char* nvn);     //  Lag innmaten ifm. oppgave 2E. 
};


class Gjest : public Num_element  {
  private:                   //  Number = personID (helt unikt (person)nummer).
    char*    navn;           //  Gjestens navn.
    int      romnr;          //  Romnummer p† hotellet.
    kategori kat;            //  Type "fan" (City, United, Noytral).

  public:
    Gjest(kategori kat2, int pID);    //  (Ferdigkodet)
    Gjest(istream* inn, int pID);     //  Lag innmaten ifm. oppgave 2F.
    ~Gjest();                         //  (Ferdigkodet)
    void display();                   //  (Ferdigkodet)
    bool operator == (kategori kat2); //  (Ferdigkodet)
    bool operator == (char* t);       //  (Ferdigkodet)
};


                        //  DEKLARASJON AV FUNKSJONER:
void skriv_meny();                                        //
char les();                                               //
int  les(const char t[], const int MIN, const int MAX);   //  (Ferdigkodet)
void les(const char t[], char s[], const int LEN);        //
int  finn_gjest(int nr);                                  //
void antall_paa_hotellene();  //  Lag innmaten ifm. oppgave 2A.
void drar();                  //  Lag innmaten ifm. oppgave 2C.
void kommer();                //  Lag innmaten ifm. oppgave 2D.
void finn_person();           //  Lag innmaten ifm. oppgave 2E.
void les_fra_fil();           //  Lag innmaten ifm. oppgave 2F.


                        //  GLOBALE VARIABLE:
int     ant_hoteller = 0;         //  Aktuelt antall hoteller i byen.
Hotell* hoteller[MAXHOTELL+1];    //  Alle hotellene, bruker fra indeks nr.1.


int main()  {           //  HOVEDPROGRAM:
  char valg;

  les_fra_fil();                                 //  Oppgave 2F

  skriv_meny();
  valg = les();
  while (valg != 'Q')  {
    switch(valg)  {
      case 'A': antall_paa_hotellene();  break;  //  Oppgave 2A
      case 'H':
            hoteller[les("Skriv alt om hotell nr", 1, ant_hoteller)]->skriv();
                                         break;
      case 'S':
            hoteller[les("Skriv fans p† hotell nr", 1, ant_hoteller)]->skriv2();
                                         break;  //  Oppgave 2B
      case 'D': drar();                  break;  //  Oppgave 2C
      case 'K': kommer();                break;  //  Oppgave 2D
      case 'F': finn_person();           break;  //  Oppgave 2E
      default:  skriv_meny();            break;
    }
    valg = les();
  }
//  skriv_til_fil();
  cout << "\n\n";
  return 0;
}

// *************************************************************************
// ******************  DEFINISJON AV MEDLEMS-FUNKSJONER:  ******************
// *************************************************************************

//***************************  HOTELL:  *******************************

                                //  Oppgave 2F - Constructor som leser fra fil:
Hotell::Hotell(istream* inn)  {

//  Lag innmaten
}


Hotell::~Hotell()  {                  //  Sletter alt allokert vha. "new":
  delete [] navn;   delete [] data;   delete gjester;
}


bool Hotell::inneholder(int nr)  {
  return (gjester->in_list(nr));
}


void Hotell::skriv()  {
  gjester->display_list();
  cout << "\n\n\tNavn: " << navn << "\n\tData: " << data
       << "\n\tAnt.City: " << ant_C << "\tAnt.United: " << ant_U
       << "\tAnt.n›ytrale: " << (gjester->no_of_elements() - ant_C - ant_U)
       << "\tMax.diff: " << diff;
}

                                //  Referanseoverf›rer tilbake 2x verdier:
void Hotell::hent_antall(int & an_C, int & an_U)  {
  an_C = ant_C;      an_U = ant_U;
}

                                //  Oppgave 2B - Skriver hotellets gjester - 
void Hotell::skriv2()  {        //    gruppert/sortert etter fan-grupper:

//  Lag innmaten
}


void Hotell::slett(int nr)  {   //  Oppgave 2C - Sletter/fjerner en gjest:

//  Lag innmaten
}

                                //  Oppgave 2D- Pr›ver † legge inn en gjest:
bool Hotell::innlosjer(kategori kat2, int nr)  {

//  Lag innmaten
}

                                //  Oppgave 2E - Leter etter navngitt gjest
bool Hotell::finn_og_skriv(char* nvn)  {   //  og skriver om n›dvendig:

//  Lag innmaten
}


//***************************  GJEST:  ********************************

                                //  Leser/setter alle data om ny gjest:
Gjest::Gjest(kategori kat2, int pID) : Num_element(pID)  {   
  char nvn[STRLEN];
  les("Gjestens navn", nvn, STRLEN);           // Leser ny gjest navn,
  navn = new char[strlen(nvn)+1];   strcpy(navn, nvn);
  romnr = les("Romnr", 1, MAXROMNR);           //   romnummer og
  kat = kat2;                                  //   setter fan-kategori.
}

                                //  Oppgave 2F - Leser gjest fra fil:
Gjest::Gjest(istream* inn, int pID) : Num_element(pID)  {

//  Lag innmaten
}


Gjest::~Gjest()  {                    //  Sletter alt allokert vha. "new":
   delete [] navn;
}


void Gjest::display()  {              //  Skriver ALLE objektets data:
   cout << "\n\t" << number << ": " << navn << "\t(rom: " << romnr << ") - ";
   switch (kat)  {                               //  Skriver enum-verdier
     case City:     cout << "City";     break;   //    som tekst:
     case United:   cout << "United";   break;
     case Noytral:  cout << "N›ytral";  break;
   }
}

                                      //  Returnerer om er av en viss fan-kat:
bool Gjest::operator == (kategori kat2)  {  
   return (kat == kat2);
}

                                      //  Returnerer om har et gitt navn ('t'):
bool Gjest::operator == (char* t)  {
  return(!strcmp(navn, t));
}


// ****************************************************************************
// ******************   DEFINISJON AV (GLOBALE) FUNKSJONER:  ******************
// ****************************************************************************

void skriv_meny()  {                 //  Skriver alle mulige menyvalg:
  cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   A  - Antall ulike fans p† alle byens ulike hoteller"
       << "\n   H  - skriv ett Hotell (usortert)"
       << "\n   S  - Skriv ett hotell (sortert)"
       << "\n   D  - gjest Drar"
       << "\n   K  - gjest Kommer"
       << "\n   F  - Finn en navngitt person"
       << "\n   Q  - Quit / avslutt";
}


char les()  {                //  Leser og upcaser ett tegn:
  char ch;
  cout << "\n\n\nKommando: ";
  cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                             //  Leser et tall mellom MIN og MAX:
int les(const char t[], const int MIN, const int MAX)  {
  int n;
  do  {
     cout << '\t' << t << " (" << MIN << '-' << MAX << "): ";
     cin >> n;  cin.ignore();
  } while (n < MIN  ||  n > MAX);
  return n;
}

                             //  Leser inn en ikke-blank tekst:
void les(const char t[], char s[], const int LEN) {  
  do  {
    cout << '\t' << t << ": ";	//  Skriver ledetekst.
    cin.getline(s, LEN);        //  Leser inn tekst.
  } while (strlen(s) == 0);     //  Sjekker at tekstlengden er ulik 0.
}

                    //  Leter etter en gjest med et gitt nummer/ID. Returnerer
int finn_gjest(int nr)  {       //     hotellets nummer der er † finne, evt. 0:
  for (int i = 1;  i <= ant_hoteller;  i++)   //  For hvert hotell:
      if (hoteller[i]->inneholder(nr))        //  Er † finne p† hotell nr.'i':
         return i;
  return 0;                                   //  Ingen funn - returnerer '0'.
}

                 //  Oppgave 2A - Antall C- og U-fan p† hvert hotell og totalt:
void antall_paa_hotellene()  {  

//  Lag innmaten
}


void drar()  {             //  Oppgave 2C - Hotellgjest drar (fra et hotell):

//  Lag innmaten
}


void kommer()  {           //  Oppgave 2D - Hotellgjest ankommer (et hotell):

//  Lag innmaten
}


void finn_person()  {  // Oppgave 2E - Leter etter navngitt person p† hotellene:

//  Lag innmaten
}


void les_fra_fil()  {       //  Oppgave 2F - Leser HELE datastrukturen fra fil:

//  Lag innmaten
}


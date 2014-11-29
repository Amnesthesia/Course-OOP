//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J12_2.TPL

//  Hovedrisset til kontinuasjonseksamen i OOP, 5.januar 2012, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2009.


//  Programmet holder orden p ulike typer gjenstander (malerier, mbler og
//     ting). Alle diss (arvede objektene) ligger i en og samme liste.
//
//  Det er mulig :
//      - Skrive alt om EN gitt/spesiell gjenstand          (oppgave 2B)
//      - Skrive alle gjenstander av en viss type/kategori  (oppgave 2C)
//      - Legge inn en ny (subklasse av en) gjenstand       (oppgave 2D)
//      - Slette/fjerne en gitt gjenstand                   (oppgave 2E)
//      - Skrive hele datastrukturen TIL fil                (oppgave 2F)
//      - Lese hele datastrukturen FRA fil                  (oppgave 2G)

                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  i(f)stream, o(f)stream
#include <cstring>           //  strlen, strcpy
#include <cctype>            //  toupper
#include <cstdlib>           //  atof
#include "listtool.h"        //  "Verktykasse" for listehndtering.

using namespace std;

                        //  CONST og ENUM:
const int  STRLEN   =     80;    //  Standard streng-/tekstlengde.
const int  MINAAR   =   1500;    //  Gjenstand ikke eldre enn dette.
const int  MAXAAR   =   2030;    //  Gjenstand ikke yngre enn dette.
const int  MINANT   =      1;    //  Min. antall av en gjenstand (jfr. Ting).
const int  MAXANT   =    100;    //  Max. antall av en gjenstand (jfr. Ting).
const int  MINSUM   =      1;    //  Min. verdi/betalt for en gjenstand.
const int  MAXSUM   = 200000;    //  Max. verdi/betalt for en gjenstand.
enum  Type { maleri, mobel, ting  };  //  Aktuelle subklasse-typer.

                        //  KLASSER:
class Gjenstand : public Text_element  {
  private:                         //  Text = navn
    int   aar;                     //  Gjenstanden er fra dette ret (ca.)
    float verdi, betalt;           //  Dens (antatte ca.) verdi og kjpesum.
  protected:
    Type  type;                    //  Brukes/settes av subklassene.

  public:
    Gjenstand(char* t);                      //  Lag innmaten ifm. oppgave 2D.
    Gjenstand(char* t, istream* inn);        //  Lag innmaten ifm. oppgave 2G.
    virtual void display();                  //  Lag innmaten ifm. oppgave 2B.
    bool operator == (Type typ)  {  return (type == typ);  }
    virtual void skriv_til_fil(ostream* ut); //  Lag innmaten ifm. oppgave 2F.
};


class Maleri : public Gjenstand  {
  private:
    char* kunstner;                      //  Kunstnerens navn.
  public:
    Maleri(char* t);                     //  Lag innmaten ifm. oppgave 2D.
    Maleri(char* t, istream* inn);       //  Lag innmaten ifm. oppgave 2G.
    ~Maleri()  { delete [] kunstner;  }
    void display();                      //  Lag innmaten ifm. oppgave 2B.
    void skriv_til_fil(ostream* ut);     //  Lag innmaten ifm. oppgave 2F.
};


class Mobel: public Gjenstand  {
  private:
    char* beskrivelse;                   //  Beskrivelse av mbelet.
  public:
    Mobel(char* t);                      //  Lag innmaten ifm. oppgave 2D.
    Mobel(char* t, istream* inn);        //  Lag innmaten ifm. oppgave 2G.
    ~Mobel()  { delete [] beskrivelse;  }
    void display();                      //  Lag innmaten ifm. oppgave 2B.
    void skriv_til_fil(ostream* ut);     //  Lag innmaten ifm. oppgave 2F.
};


class Ting : public Gjenstand  {
  private:                   //  Materialet tingen er laget av:
    char* stoff;             //     porselen, krystall, stl, jern,...
    int   antall;            //  Antall duplikater man har av gjenstanden.

  public:
    Ting(char* t);                       //  Lag innmaten ifm. oppgave 2D.
    Ting(char* t, istream* inn);         //  Lag innmaten ifm. oppgave 2G.
    ~Ting()  { delete [] stoff;  }
    void display();                      //  Lag innmaten ifm. oppgave 2B.
    void skriv_til_fil(ostream* ut);     //  Lag innmaten ifm. oppgave 2F.
};

                        //  DEKLARASJON AV FUNKSJONER:
void skriv_meny();
char  les(const char* t);
float les(const char* t, const int MIN, const int MAX);
void  les(const char t[], char s[], const int LEN);
Type  les();                             //  Lag innmaten ifm. oppgave 2A.
void skriv_en_gjenstand();               //  Lag innmaten ifm. oppgave 2B.
void skriv_all_av_type();                //  Lag innmaten ifm. oppgave 2C.
void ny_gjenstand();                     //  Lag innmaten ifm. oppgave 2D.
void slett_gjenstand();                  //  Lag innmaten ifm. oppgave 2E.
void skriv_til_fil();                    //  Lag innmaten ifm. oppgave 2F.
void les_fra_fil();                      //  Lag innmaten ifm. oppgave 2G.

                        //  GLOBALE VARIABLE:
List* gjenstandene;              //  Liste med ALLE de ulike gjenstandene.


int main()  {           //  HOVEDPROGRAM:
  char valg;

  gjenstandene = new List(Sorted);     //  Initierer listen.

  les_fra_fil();                                        //  Oppgave 2G

  skriv_meny();
  valg = les("\n\nKommando");
  while (valg != 'Q')  {
    switch(valg)  {
      case 'A': gjenstandene->display_list();  break;
      case 'E': skriv_en_gjenstand();          break;   //  Oppgave 2B
      case 'T': skriv_all_av_type();           break;   //  Oppgave 2C
      case 'N': ny_gjenstand();                break;   //  Oppgave 2D
      case 'S': slett_gjenstand();             break;   //  Oppgave 2E
      default:  skriv_meny();                  break;
    }
    valg = les("\n\nKommando");
  }
  skriv_til_fil();                                      //  Oppgave 2F
  cout << "\n\n";
  return 0;
}


// *************************************************************************
// ******************  DEFINISJON AV MEDLEMS-FUNKSJONER:  ******************
// *************************************************************************


// ***************************  Gjenstand:  **************************
Gjenstand::Gjenstand(char* t) : Text_element(t)  {  // Oppgave 2D:

//  Lag innmaten
}

                                                    //  Oppgave 2G:
Gjenstand::Gjenstand(char* t, istream* inn) : Text_element(t)  {

//  Lag innmaten
}


void Gjenstand::display()  {                        //  Oppgave 2B:

//  Lag innmaten
}

                                                    //  Oppgave 2F:
void Gjenstand::skriv_til_fil(ostream* ut)  {

//  Lag innmaten
}


// *******************************  Maleri:  *********************************
Maleri::Maleri(char* t) : Gjenstand(t)  {           //  Oppgave 2D:

//  Lag innmaten
}

                                                    //  Oppgave 2G:
Maleri::Maleri(char* t, istream* inn) : Gjenstand(t, inn)  {

//  Lag innmaten
}


void Maleri::display()  {                           //  Oppgave 2B:

//  Lag innmaten
}


void Maleri::skriv_til_fil(ostream* ut)  {          //  Oppgave 2F:

//  Lag innmaten
}


// *******************************  Mbel:  **********************************
Mobel::Mobel(char* t) : Gjenstand(t)  {             //  Oppgave 2D:

//  Lag innmaten
}

                                                    //  Oppgave 2G:
Mobel::Mobel(char* t, istream* inn) : Gjenstand(t, inn)  {

//  Lag innmaten
}


void Mobel::display()  {                            //  Oppgave 2B:

//  Lag innmaten
}


void Mobel::skriv_til_fil(ostream* ut)  {           //  Oppgave 2F:

//  Lag innmaten
}


// *******************************  Ting:  **********************************
Ting::Ting(char* t) : Gjenstand(t)  {               //  Oppgave 2D:

//  Lag innmaten
}

                                                    //  Oppgave 2G:
Ting::Ting(char* t, istream* inn) : Gjenstand(t, inn)  {

//  Lag innmaten
}


void Ting::display()  {                             //  Oppgave 2B:

//  Lag innmaten
}


void Ting::skriv_til_fil(ostream* ut)  {            //  Oppgave 2F:

//  Lag innmaten
}


// ****************************************************************************
// ******************   DEFINISJON AV (GLOBALE) FUNKSJONER:  ******************
// ****************************************************************************

void skriv_meny()  {         //  Skriver alle mulige menyvalg:
  cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   A  - skriv Alle gjenstandene"
       << "\n   E  - skriv alt om En spesiell gjenstand"
       << "\n   T  - skriv gjenstander av en viss Type (maleri, mbel, ting)"
       << "\n   N  - Ny gjenstand"
       << "\n   S  - Slett/fjern en gjenstand"
       << "\n   Q  - Quit / avslutt";
}


char les(const char* t)  {   //  Leser og upcaser brukerens valg/nske:
  char ch;
  cout << t << ": ";
  cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                             //  Leser en FLOAT mellom MIN og MAX:
float les(const char* t, const int MIN, const int MAX)  {
  char text[STRLEN];
  float n;
  do  {
    cout << '\t' << t << " (" << MIN << '-' << MAX << "): ";
    cin.getline(text, STRLEN);   n = atof(text);  // Leser som tekst - omgjr:
  } while (n < MIN  ||  n > MAX);
  return n;
}

                             //  Leser inn en ikke-blank tekst:
void les(const char t[], char s[], const int LEN) {
  do  {
    cout << '\t' << t << ": ";    //  Skriver ledetekst.
    cin.getline(s, LEN);          //  Leser inn tekst.
  } while (strlen(s) == 0);       //  Sjekker at tekstlengden er ulik 0.
}

                               //  Oppgave 2A - Leser og returnerer lovlig
Type les()  {                  //               type gjenstand:

//  Lag innmaten
}


void skriv_en_gjenstand()  {   //  Oppgave 2B - Skriv EN spesiell gjenstand:

//  Lag innmaten
}


void skriv_all_av_type()  {   //  Oppgave 2C - Skriv EN spesiell gjenstand:

//  Lag innmaten
}


void ny_gjenstand()  {        //  Oppgave 2D - Legg inn en ny gjenstand:

//  Lag innmaten
}


void slett_gjenstand()  {     //  Oppgave 2E - Slett/fjern en gjenstand:

//  Lag innmaten
}


void skriv_til_fil()  {    //  Oppgave 2F - Skriv HELE datastrukturen til fil:

//  Lag innmaten
}


void les_fra_fil()  {      //  Oppgave 2G - Leser HELE datastrukturen fra fil:

//  Lag innmaten
}

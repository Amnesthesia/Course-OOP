//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J12_2.CPP

//  L›sningsforslag til kontinuasjonseksamen i OOP, 5.januar 2012, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2009.


//  Programmet holder orden p† ulike typer gjenstander (malerier, m›bler og
//     ting). Alle diss (arvede objektene) ligger i en og samme liste.
//
//  Det er mulig †:
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
#include "listtool.h"        //  "Verkt›ykasse" for listeh†ndtering.

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
    int   aar;                     //  Gjenstanden er fra dette †ret (ca.)
    float verdi, betalt;           //  Dens (antatte ca.) verdi og kj›pesum.
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
    char* beskrivelse;                   //  Beskrivelse av m›belet.
  public:
    Mobel(char* t);                      //  Lag innmaten ifm. oppgave 2D.
    Mobel(char* t, istream* inn);        //  Lag innmaten ifm. oppgave 2G.
    ~Mobel()  { delete [] beskrivelse;  }
    void display();                      //  Lag innmaten ifm. oppgave 2B.
    void skriv_til_fil(ostream* ut);     //  Lag innmaten ifm. oppgave 2F.
};


class Ting : public Gjenstand  {
  private:                   //  Materialet tingen er laget av:
    char* stoff;             //     porselen, krystall, st†l, jern,...
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
  aar    = int(les("r", MINAAR, MAXAAR));          //   Leser inn de ulike
  verdi  = les("Verdi", MINSUM, MAXSUM);            //   datamedlemmene vha.
  betalt = les("Betalt", MINSUM, MAXSUM);           //   en hjelpefunksjon.
}

                                              //  Oppgave 2G:
Gjenstand::Gjenstand(char* t, istream* inn) : Text_element(t)  {
  *inn >> aar >> verdi >> betalt;             //  Leser datamedlemmer fra fil.
  inn->ignore();
}


void Gjenstand::display()  {                  //  Oppgave 2B:
  cout << '\t' << text << "\n\t\t"            //  Skriver/displayer objektet:
       << "r: " << aar << "\tVerdi kr." << verdi
       << "\tBetalt kr." << betalt << '\n';
}

                                          //  Oppgave 2F - Skriver alt til fil:
void Gjenstand::skriv_til_fil(ostream* ut)  {  
  *ut << text << '\n' << aar << ' ' << verdi << ' ' << betalt << '\n';
}


// *******************************  Maleri:  *********************************
Maleri::Maleri(char* t) : Gjenstand(t)  {     //  Oppgave 2D:
  char buffer[STRLEN];               
  type = maleri;                              //  Setter aktuell subklassetype.
  les("Kunstner", buffer, STRLEN);            //  Leser kunstnernavnet:
  kunstner = new char[strlen(buffer)+1];  strcpy(kunstner, buffer);
}

                                              //  Oppgave 2G:
Maleri::Maleri(char* t, istream* inn) : Gjenstand(t, inn)  {  
  char buffer[STRLEN];
  type = maleri;                              //  Setter aktuell subklassetype.
  inn->getline(buffer, STRLEN);               //  Leser datamedlemmer fra fil:
  kunstner = new char[strlen(buffer)+1];  strcpy(kunstner, buffer);
}


void Maleri::display()  {                    //  Oppgave 2B:
  cout << "\n\tMALERI:";
  Gjenstand::display();                      //  Skriver/displayer "mors" data:
  cout << "\t\tKunstner: " << kunstner << '\n';  //  Skriver egne data.
}


void Maleri::skriv_til_fil(ostream* ut)  {   //  Oppgave 2F:
  *ut << "A ";                               //  Skriver alt til fil:
  Gjenstand::skriv_til_fil(ut);
  *ut << kunstner << '\n';
}


// *******************************  M›bel:  **********************************
Mobel::Mobel(char* t) : Gjenstand(t)  {      //  Oppgave 2D:
  char buffer[STRLEN];
  type = mobel;                              //  Setter aktuell subklassetype.
  les("Beskrivelse", buffer, STRLEN);        //  Leser beskrivelsen:
  beskrivelse = new char[strlen(buffer)+1];  strcpy(beskrivelse, buffer);
}

                                             //  Oppgave 2G:
Mobel::Mobel(char* t, istream* inn) : Gjenstand(t, inn)  {   
  char buffer[STRLEN];
  type = mobel;                              //  Setter aktuell subklassetype.
  inn->getline(buffer, STRLEN);              //  Leser datamedlemmer fra fil:
  beskrivelse = new char[strlen(buffer)+1];  strcpy(beskrivelse, buffer);
}


void Mobel::display()  {                     //  Oppgave 2B:
  cout << "\n\tMBEL:";
  Gjenstand::display();                      //  Skriver/displayer "mors" data:
  cout << "\t\tBeskrivelse: " << beskrivelse << '\n';  // Skriver egne data.
}


void Mobel::skriv_til_fil(ostream* ut)  {    //  Oppgave 2F:
  *ut << "O ";                               //  Skriver alt til fil:
  Gjenstand::skriv_til_fil(ut);
  *ut << beskrivelse << '\n';
}


// *******************************  Ting:  **********************************
Ting::Ting(char* t) : Gjenstand(t)  {        //  Oppgave 2D:
  char buffer[STRLEN];
  type = ting;                               //  Setter aktuell subklassetype.
  les("Stoff", buffer, STRLEN);              //  Leser stoff og antall:
  stoff = new char[strlen(buffer)+1];  strcpy(stoff, buffer);
  antall = les("Antall", MINANT, MAXANT);
}

                                             //  Oppgave 2G:
Ting::Ting(char* t, istream* inn) : Gjenstand(t, inn)  { 
  char buffer[STRLEN];
  type = ting;                               //  Setter aktuell subklassetype.
  *inn >> antall;  inn->ignore();            //  Leser datamedlemmer fra fil:
  inn->getline(buffer, STRLEN);
  stoff = new char[strlen(buffer)+1];  strcpy(stoff, buffer);
}


void Ting::display()  {                      //  Oppgave 2B:
  cout << "\n\tTING:";                       //  Skriver/displayer "mors" og
  Gjenstand::display();                      //    egne data:
  cout <<  "\t\tAntall: " << antall << "\tStoff: " << stoff << '\n';
}


void Ting::skriv_til_fil(ostream* ut)  {     //  Oppgave 2F:
  *ut << "T ";                               //  Skriver alt til fil:
  Gjenstand::skriv_til_fil(ut);
  *ut << antall << ' ' << stoff << '\n';
}


// ****************************************************************************
// ******************   DEFINISJON AV (GLOBALE) FUNKSJONER:  ******************
// ****************************************************************************

void skriv_meny()  {         //  Skriver alle mulige menyvalg:
  cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   A  - skriv Alle gjenstandene"
       << "\n   E  - skriv alt om En spesiell gjenstand"
       << "\n   T  - skriv gjenstander av en viss Type (maleri, m›bel, ting)"
       << "\n   N  - Ny gjenstand"
       << "\n   S  - Slett/fjern en gjenstand"
       << "\n   Q  - Quit / avslutt";
}


char les(const char* t)  {   //  Leser og upcaser brukerens valg/›nske:
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
    cin.getline(text, STRLEN);   n = atof(text);  // Leser som tekst - omgj›r:
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
  char tegn;
  do                           //  Leser ALLTID  'A', 'O' eller 'T':
    tegn = les("\tGjenstand-type (m)A(leri), (m)O(bel), T(ing)");
  while (tegn != 'A'  &&  tegn != 'O'  &&  tegn != 'T');

  switch (tegn)  {             //  Gj›r om til og returnerer aktuell type:
    case 'A':  return maleri;
    case 'O':  return mobel;
    case 'T':  return ting;
  }
}


void skriv_en_gjenstand()  {   //  Oppgave 2B - Skriv EN spesiell gjenstand:
  char navn[STRLEN];

  les("Se gjenstand (navn)", navn, STRLEN);      //  Leser navn.
  if (!gjenstandene->display_element(navn))      //  Finnes? Displayer, ellers:
     cout << "\n\tIngen gjenstand med dette navnet!\n\n";  //  melding.
}


void skriv_all_av_type()  {   //  Oppgave 2C - Skriv EN spesiell gjenstand:
  Gjenstand* gjenst;                           //  Hjelpepeker.
  int i, ant = gjenstandene->no_of_elements(); //  L›kkevar, antall i listen.
  Type type = les();

  for (i = 1;  i <= ant;  i++)  {              //  G†r gjennom hele listen:
      gjenst = (Gjenstand*) gjenstandene->remove_no(i);  //  Tar ut.
      if (*gjenst == type) gjenst->display();  //  Av aktuell type?  Display!
      gjenstandene->add(gjenst);               //  Legger tilbake/inn igjen.
  }
}


void ny_gjenstand()  {        //  Oppgave 2D - Legg inn en ny gjenstand:
  char navn[STRLEN];
  Type type;

  les("Ny gjenstand (navn)", navn, STRLEN);      //  Leser nytt(?) navn. 
  if (!gjenstandene->in_list(navn))  {           //  Finnes IKKE allerede:
     type = les();                               //  Leser typen.
     switch (type)  {                            //  Lager og legger inn nytt 
       case maleri: gjenstandene->add(new Maleri(navn)); break; //  aktuelt
       case mobel:  gjenstandene->add(new Mobel(navn));  break; //  subklasse-
       case ting:   gjenstandene->add(new Ting(navn));   break; //  objekt:
     }
  } else                                         //  Finnes allerede:
    cout << "\n\tGjenstand med dette navnet finnes allerede!\n";
}


void slett_gjenstand()  {     //  Oppgave 2E - Slett/fjern en gjenstand:
  char navn[STRLEN];

  les("Slett/fjern gjenstand (navn)", navn, STRLEN);   //  Leser navn.
  if (gjenstandene->in_list(navn))  {                  //  Finnes:
     if (les("\tSikker (j/N)") == 'J')  {              //  VIL slette?
        gjenstandene->destroy(navn);                   //  Sletter/fjerner.
        cout << "\n\tGjenstanden er slettet/fjernet.\n\n";
     } else                                            //  Ville ikke slette:
        cout << "\n\tGjenstanden ble IKKE slettet/fjernet.\n\n";
  } else                                               //  Finnes IKKE:
     cout << "\n\tIngen gjenstand med dette navnet!\n\n";
}


void skriv_til_fil()  {    //  Oppgave 2F - Skriv HELE datastrukturen til fil:
  Gjenstand* gjenst;                           //  Hjelpepeker.
  ofstream utfil("GJENSTANDER.DTA");           //  pner aktuell fil.
  int i, ant = gjenstandene->no_of_elements(); //  L›kkevar, antallet i listen.

  for (i = 1;  i <= ant;  i++)  {              //  G†r gjennom hele listen:
      gjenst = (Gjenstand*) gjenstandene->remove_no(i);  //  Tar ut.
      gjenst->skriv_til_fil(&utfil);           //  Skriver objektet til fil.
      gjenstandene->add(gjenst);               //  Legger tilbake/inn igjen.
  }
}


void les_fra_fil()  {      //  Oppgave 2G - Leser HELE datastrukturen fra fil:
  ifstream innfil("GJENSTANDER.DTA");         //  pner aktuell fil:
  char nvn[STRLEN];                           //  Gjenstands-navn.
  char type;                                  //  'A', 'O' eller 'T'.

  if (innfil)  {                              //  Filen finnes:
     innfil >> type;                          //  Leser om mulig 'A', 'O', 'T'.
     while (!innfil.eof())  {                 //  Mer p† filen:
       innfil.ignore();                       //  Skipper ' ' (EN blank).
       innfil.getline(nvn, STRLEN);           //  Leser gjenstandens navn.
       switch (type)  {                       //  Aktuell ny lages/legges inn:
         case 'A': gjenstandene->add(new Maleri(nvn, &innfil));  break;
         case 'O': gjenstandene->add(new Mobel(nvn, &innfil));   break;
         case 'T': gjenstandene->add(new Ting(nvn, &innfil));    break;
       }
       innfil >> type;                        //  Leser om mulig 'A', 'O', 'T'.
     }
  } else                                      //  Filen finnes IKKE:
    cout << "\n\nFant ikke filen 'GJENSTANDER.DTA'!\n\n";
}

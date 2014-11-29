//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J05_2.TPL

//  Skjellett/omriss for kontinuasjonseksamen i C++, 5.januar 2005, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2004.


//  Programmet holder orden på ulike øvelser og deltagere i en større 
//  idrettskonkurranse (f.eks. Paralympics), derav også hvilke øvelser 
//  den enkelte deltager deltar/er oppmeldt i.


                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  ifstream
#include <cstring>           //  strcpy, strlen
#include <cctype>            //  toupper
#include "listtool.h"        //  Ulike "verktøy" fra "Listtool".

using namespace std;

                        //  CONST:
const int STRLEN  =  80;     //  Max. lengde for en tekststreng.
const int LANDLEN =   4;     //  Max. lengde for landsforkortelse (inkl.'\0').
const int MAXOVELS = 20;     //  Max. antall øvelser man kan delta i.


                        //  KLASSER:
class Ovelse : public Num_element  {
  private:
       //  Den arvede "number" brukes som ID for øvelsen/idrettsgrenen.
    char* navn;
    int dato,                //  På formen:  ååååmmdd
        klokkeslett,         //  På formen:  ttmm
        arena;               //  Tall fra 1-20.
	  
  public:
    Ovelse(int nr);          //  Deklarasjon av medlemsfunksjoner:
    Ovelse(int nr, istream* inn);
    ~Ovelse()   {  delete [] navn;  }
    void display();
};


class Deltager : public Text_element  {
  private:
    //  Den arvede "text" brukes som ID/navn for deltageren.
    char land[LANDLEN];
    int  ant_ovelser;         //  Antall ganger individet har brukt kortet.
    int  ovelser[MAXOVELS+1]; //  Nummeret på øvelsene vedkommende deltar i.

  public:
    Deltager(char* t);        //  Deklarasjon av medlemsfunksjoner:
    Deltager(char* t, istream* inn);
    void display();
    void display2();
    void paamelde_ovelse();
    bool deltar(int n);
    void kutt_ovelse(int n);
};


                        //  DEKLARASJON AV FUNKSJONER:
void skriv_meny();
char les();
void les(char t[], char s[], const int LEN);
int  les(char t[], const int MIN, const int MAX);
void ny_ovelse();
void ny_deltager();
void skriv_deltager();
void delta_i_ovelse();
void skriv_ovelse();
void slett_ovelse();
void les_fra_fil();


                        //  GLOBAL VARIBEL:
List* ovelsene;             //  Liste med alle ovelsene (numerisk sortert).
List* deltagere;            //  Liste med alle deltagerne (tekstlig sortert).
int ovelse_teller = 0;      //  Fortløpende nummerering av øvelsene.


int main()   {          //  HOVEDPROGRAM:
  char kommando;             //  Brukerens valg/ønske.

  ovelsene  = new List(Sorted);    //  Initierer tomme lister:
  deltagere = new List(Sorted);

  les_fra_fil();                   //  Oppgave 2G

  skriv_meny();                    //  Skriver aktuelle valg/muligheter.

  kommando = les();                //  Leser brukerens valg.
  while (kommando != 'Q')  {
    switch(kommando)  {
      case 'N': ny_ovelse();       break;   //  Oppgave 2A
      case 'D': ny_deltager();     break;   //  Oppgave 2B
      case 'V': skriv_deltager();  break;   //  Oppgave 2C
      case 'P': delta_i_ovelse();  break;   //  Oppgave 2D
      case 'A': skriv_ovelse();    break;   //  Oppgave 2E
      case 'S': slett_ovelse();    break;   //  Oppgave 2F
      default:  skriv_meny();      break;
    }
    kommando = les();              //  Leser brukerens valg.
  }
  cout << "\n\n";
  return 0;
}

                        //  DEFINISJON AV MEDLEMS-FUNKSJONER:
Ovelse::Ovelse(int nr) : Num_element(nr)  {  //  Constructor som leser inn ALLE medlemsdata:

//     Oppgave 2A:  Skriv innmaten
}

                             // Constructor som leser inn medlemsdata fra fil:
Ovelse::Ovelse(int nr, istream* inn) : Num_element(nr)  {

//     Oppgave 2G:  Skriv innmaten
}


void Ovelse::display()  {           //  Skriver ut ALLE medlemsdata:

//     Oppgave 2A:  Skriv innmaten
}

                                    
Deltager::Deltager(char* t) : Text_element(t)  {   // Initierer hoveddataene:

//     Oppgave 2B:  Skriv innmaten
}

                             // Constructor som leser inn medlemsdata fra fil:
Deltager::Deltager(char* t, istream* inn) : Text_element(t)  {

//     Oppgave 2G:  Skriv innmaten
}


void Deltager::display()  {  //  Skriver ut ALLE medlemsdataene:

//     Oppgave 2C:  Skriv innmaten
}

void Deltager::display2()  { //  Skriver kun navn og nasjon/land:

//     Oppgave 2E:  Skriv innmaten
}
	
void Deltager::paamelde_ovelse()  {   //  Påmeldes evt. i en øvelse:

//     Oppgave 2D:  Skriv innmaten
}


bool Deltager::deltar(int n)  {       //  Skal delta i øvelse nr.'n' eller ei:

//     Oppgave 2E:  Skriv innmaten
}


void Deltager::kutt_ovelse(int n)  {  //  Avmeldes av øvelse nr.'n':

//     Oppgave 2F:  Skriv innmaten
}

                        //  DEFINISJON AV FUNKSJONER:
void skriv_meny()  {         //  Skriver meny/lovlige kommandoer til bruker:
  cout << "\n\n\nFølgende kommandoer er lovlig:\n";
  cout << "\tN - Ny øvelse\n";
  cout << "\tD - ny Deltager\n";
  cout << "\tV - Vis/skriv alt om en deltager\n";
  cout << "\tP - Påmeld en deltager i en ny øvelse\n";
  cout << "\tA - skriv Alle deltagere i en øvelse\n";
  cout << "\tS - Slett øvelse\n";
  cout << "\tQ - Quit / avslutt\n";
}


char les()  {                //  Leser og returnerer ETT upcaset tegn.
  char ch;
  cout << "\n\nKommando:  ";   cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                             // Leser tall i et visst intervall:
int les(char t[], const int MIN, const int MAX)  {  
  int n;
  do  {                                 // Skriver ledetekst:
    cout << '\t' << t << '(' << MIN << '-' << MAX << "): ";
    cin >> n;   cin.ignore();           // Leser inn ett tall, forkaster '\n'.
  } while(n < MIN  ||  n > MAX);        // Sjekker at i lovlig intervall.
  return n;                             // Returnerer innlest tall.
}

                             //  Leser inn en tekst med lengde ulik 0:
void les(char t[], char s[], const int LEN) {    
  do  {
    cout << '\t' << t << ": ";    //  Skriver ledetekst.
    cin.getline(s, LEN);          //  Leser inn tekst.
  } while (strlen(s) == 0);       //  Sjekker at tekstlengden er ulik 0.
}

void ny_ovelse()  {          //  Legger inn en ny øvelse:

//     Oppgave 2A:  Skriv innmaten
}

void ny_deltager()  {        //  Legger inn en ny deltager:

//     Oppgave 2B:  Skriv innmaten
}

void skriv_deltager()  {     //  Skriver ALT om EN deltager:

//     Oppgave 2C:  Skriv innmaten
}

void delta_i_ovelse()  {     //  EN deltager skal delta i EN ny øvelse:

//     Oppgave 2D:  Skriv innmaten
}

void skriv_ovelse()  {       //  Skriver ALLE som deltar i en øvelse:

//     Oppgave 2E:  Skriv innmaten
}

void slett_ovelse()  {       //  Sletter (om mulig) TOTALT en øvelse:

//     Oppgave 2F:  Skriv innmaten
}

void les_fra_fil()  {               //  Leser inn ALLE data om ALT fra EN fil:

//     Oppgave 2G:  Skriv innmaten
}

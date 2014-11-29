//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J05_2.CPP

//  Løsningsforslag til kontinuasjonseksamen i C++, 5.januar 2005, oppgave 2.
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
Ovelse::Ovelse(int nr) : Num_element(nr)  {  //  Constructor som leser inn
  char buffer[STRLEN];                       //     ALLE medlemsdata:
  cout << "\n\t" << nr << ", navn:  ";  cin.getline(buffer, STRLEN);
  navn = new char[strlen(buffer)+1];  strcpy(navn, buffer);
  dato =        les("Dato      ", 20050101, 20203112);
  klokkeslett = les("Klokkslett", 700, 2200);
  arena =       les("Arena     ", 1, 20);
}

                             // Constructor som leser inn medlemsdata fra fil:
Ovelse::Ovelse(int nr, istream* inn) : Num_element(nr)  {
  char buffer[STRLEN];
  (*inn).getline(buffer, STRLEN);
  navn = new char[strlen(buffer)+1];  strcpy(navn, buffer);
  *inn >> dato >> klokkeslett >> arena;  (*inn).ignore();
}


void Ovelse::display()  {           //  Skriver ut ALLE medlemsdata:
  cout << '\t' << number << ": " << navn << "\n\t\t" 
       << "Dato: " << dato << "  kl." 
       << ((klokkeslett < 1000)? "0" : "") << klokkeslett
       << "  Arena: " << arena << '\n';
}

                                    
Deltager::Deltager(char* t) : Text_element(t)  {   // Initierer hoveddataene:
  les("Land:   ", land, LANDLEN);  
  ant_ovelser = 0;
}

                             // Constructor som leser inn medlemsdata fra fil:
Deltager::Deltager(char* t, istream* inn) : Text_element(t)  {
  int i;
  (*inn).get(land, LANDLEN);
  *inn >> ant_ovelser;
  for (i = 1;  i <= ant_ovelser;  i++)
      *inn >> ovelser[i];
  (*inn).ignore();
}


void Deltager::display()  {  //  Skriver ut ALLE medlemsdataene:
  int i;
  cout << "\n\t" << text << ", " << land           //  Navn og land.
       << "\n\tskal delta i " << ant_ovelser << " øvelse(r):\n";
  for (i = 1;  i <= ant_ovelser;  i++) {           //  Øvelsene SKAL finnes og
      if (!ovelsene->display_element(ovelser[i]))  //    bli skrevet ut:
         cout << "\tFEIL: Deltar i ikke-eksisterende øvelse!\n";
  }
}

void Deltager::display2()  { //  Skriver kun navn og nasjon/land:
  cout << "\t\t" << text << ", " << land << '\n';
}
	
void Deltager::paamelde_ovelse()  {   //  Påmeldes evt. i en øvelse:
  int nr;
  if (ant_ovelser < MAXOVELS)  {             //  Kan delta i flere øvelser:
     nr = les("Delta i øvelse nr", 0, ovelse_teller); // Leser øvelsesnr.
     if (ovelsene->in_list(nr))  {              //  Øvelsen finnes:
        ovelser[++ant_ovelser] = nr;            //  Setter at deltar.
     } else
       cout << "\n\tINGEN øvelse med dette nummeret!\n";
  } else
    cout << "\n\tKan IKKE delta på flere øvelser!\n";
}


bool Deltager::deltar(int n)  {       //  Skal delta i øvelse nr.'n' eller ei:
  int i;
  for (i = 1;  i <= ant_ovelser;  i++)
      if (ovelser[i] == n) return true;  //  Match - skal delta.
  return false;                          //  Ingen match (skal IKKE delta).
}


void Deltager::kutt_ovelse(int n)  {  //  Avmeldes av øvelse nr.'n':
  int i;
  for (i = 1;  i <= ant_ovelser;  i++)
     if (ovelser[i] == n) {           //  Macth - fjernes/slettes:
        ovelser[i] = ovelser[ant_ovelser--];  //  Flytter bakerste inn
        break;                                //    i "hullet" - ferdig.
     }
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

                             //  OPPGAVE 2A:
void ny_ovelse()  {          //  Legger inn en ny øvelse:
  Ovelse* ov;                        //  Peker til ny øvelse.
  ov = new Ovelse(++ovelse_teller);  //  Oppretter med automatisk nummerering.
  ovelsene->add(ov);                 //  Legger inn i listen.
  ovelsene->display_list();          //  Får skrevet alle øvelsene.
}

                             //  OPPGAVE 2B:
void ny_deltager()  {        //  Legger inn en ny deltager:
  Deltager* delt;                    //  Peker til ny deltager.
  char nvn[STRLEN];                  //  Navnet til/på ny deltager.

  les("Ny deltagers navn", nvn, STRLEN);   //  Leser aktuelt nytt navn.
  if (!deltagere->in_list(nvn))  {         //  Finnes IKKE fra før:
     delt = new Deltager(nvn);             //  Lager/oppretter ny deltager.
     deltagere->add(delt);                 //  Legger inn i listen.
  } else
    cout << "\n\tDenne deltageren finnes allerede!\n";
}

                             //  OPPGAVE 2C:
void skriv_deltager()  {     //  Skriver ALT om EN deltager:
  char nvn[STRLEN];                             //  Deltagerens navn.
  if (!deltagere->is_empty())  {                //  Lista er IKKE tom:
     les("Skriv alt om deltager", nvn, STRLEN); //  Leser navnet.
     if (!deltagere->display_element(nvn))      //  Skriver vedkommende.
        cout << "\n\tDenne deltageren finnes IKKE!\n";
  } else
    cout << "\n\tIngen deltagere er registrert, bruk 'D' først!\n";
}

                             //  OPPGAVE 2D:
void delta_i_ovelse()  {     //  EN deltager skal delta i EN ny øvelse:
  Deltager* delt;                    //  Peker til deltager.
  char nvn[STRLEN];                  //  Navnet til/på deltageren.
 
  if (!deltagere->is_empty())  {     //  Finnes noen deltagere:
     if (ovelse_teller > 0)  {       //  Finnes noen øvelser:
        les("Ny øvelse for deltager", nvn, STRLEN);  //  Leser deltagers navn.
                                     //  Deltager finnes, tas ut av listen:
        if ((delt = (Deltager*) deltagere->remove(nvn)))  {  
           delt->paamelde_ovelse();  //  Oppdaterer at skal delta i en øvelse.
           deltagere->add(delt);     //  Legger tilbake igjen.
        } else
          cout << "\n\tDenne deltageren finnes IKKE!\n";
     } else
       cout << "\n\tIngen øvelser er registrert, bruk 'N' først!\n";
  } else
    cout << "\n\tIngen deltagere er registrert, bruk 'D' først!\n";
}

                             //  OPPGAVE 2E:
void skriv_ovelse()  {       //  Skriver ALLE som deltar i en øvelse:
  Deltager* delt;            //  Peker til deltager.
  int nr, ant, i;            //  Øvelsesnr, antall deltagere, løkkevariabel.

  nr = les("Skriv øvelse nr", 1, ovelse_teller);  //  Leser øvelsesnummer.
  if (ovelsene->display_element(nr))  {           //  Øvelsen skrives (finnes):
     cout << "\n\tDeltagere i denne øvelsen:\n";
     ant = deltagere->no_of_elements();
     for (i = 1;  i <= ant;  i++)  {    
         delt = (Deltager*) deltagere->remove_no(i);  //  Henter deltager 'i'.
         if (delt->deltar(nr))  delt->display2();     //  Skal delta: skriver.
         deltagere->add(delt);                        //  Legger tilbake igjen.
     }
  } else
    cout << "\n\tINGEN øvelse med dette nummeret!\n";
}

                             //  OPPGAVE 2F:
void slett_ovelse()  {       //  Sletter (om mulig) TOTALT en øvelse:
  Deltager* delt;            //  Peker til deltager.
  int nr, ant, i;            //  Øvelsesnr, antall deltagere, løkkevariabel.

  nr = les("Slett øvelse nr", 0, ovelse_teller);  //  Leser øvelsesnummer.
  if (ovelsene->destroy(nr))  {                   //  Øvelsen slettes:
     ant = deltagere->no_of_elements();
     for (i = 1;  i <= ant;  i++)  {
         delt = (Deltager*) deltagere->remove_no(i); //  Henter deltager 'i'.
         delt->kutt_ovelse(nr);                      //  Deltagelse fjernes.
         deltagere->add(delt);                       //  Legger tilbake igjen.
     }
     cout << "\n\tØvelsen og all deltagelse i den er fjernet/slettet!\n";
  } else
    cout << "\n\tINGEN øvelse med dette nummeret!\n";
}

                             //  OPPGAVE 2G:
void les_fra_fil()  {               //  Leser inn ALLE data om ALT fra EN fil:
  ifstream innfil("paralymp.dta");  //  Åpner aktuell fil.
  Ovelse* ov;                       //  Peker til øvelse.
  Deltager* delt;                   //  Peker til deltager.
  int ant_ov, i, nr;                //  Antall øvelser, løkkevar, øvelsenr.
  char buffer[STRLEN];              //  Deltagers navn.

  if (innfil)  {                    //  Filen finnes:
     cout << "\n\nLeser data inn fra filen 'PARALYMP.DTA'.....\n";
     innfil >> ovelse_teller >> ant_ov;   //  Leser to første single tall.
     for (i = 1;  i <= ant_ov;  i++)  {   //  For hver øvelse:
        innfil >> nr;  innfil.ignore();   //  Les dets unike nummer/ID.
        ov = new Ovelse(nr, &innfil);     //  Nytt objekt, leser resten selv.
        ovelsene->add(ov);                //  Legg inn i øvelses-listen.
     }

     innfil.getline(buffer, STRLEN);      //  Leser (om mulig) deltagernavn.
     while (!innfil.eof())  {             //  Ennå ikke filslutt:
       delt = new Deltager(buffer, &innfil);  //  Lager objekt, leser selv.
       deltagere->add(delt);              //  Legg inn i deltager-listen.
       innfil.getline(buffer, STRLEN);    //  Leser (om mulig) deltagernavn.
     }
  } else
    cout << "\n\nFant ikke filen 'PARALYMP.DTA'!";
}

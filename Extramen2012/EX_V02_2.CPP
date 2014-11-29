//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_V02_2.CPP

//  Lõsningsforslag til eksamen i C++, 24.mai 2002, oppgave 2.
//  Laget av Frode Haug, HiG, mai 2002.
//  Litt endret/modifisert av FrodeH, HiG, vÜren 2003.


//  Programmet holder oversikt over en persons tegneseriesamling.
//  Nye serier og blader kan legges inn i datastrukturen.


                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  ifstream, ofstream
#include <cstring>           //  strlen, strcpy, strcmp
#include <cctype>            //  toupper
#include "listtool.h"        //  Ulike "verktõy" fra "Listtool".

using namespace std;
                        //  CONST:
const int STRLEN     = 200;  //  Max. lengde for en tekst/streng.
const int MAX_SERIER = 100;  //  Max. antall serier i samlingen.

                        //  KLASSER:
class Blad : public Num_element  {      //  Klassen "Blad":
  private:
    int antall;              //  Antallet man har av bladet.
  public:                               //  2x constructorer:
    Blad(int nr) : Num_element(nr)         {  antall = 0;  }  
    Blad(int nr, int a) : Num_element(nr)  {  antall = a;  }
    void operator ++ ()      //  Overloading av "++":
      {  antall++;  display();  cout << '\n';  }
    void operator -- ()      //  Overloading av "--":
      {  if (antall > 0) antall--; 
         else  cout << "\n\tUmulig Ü kvitte seg med et blad man ikke har!"; 
         display();  cout << '\n';   }
    void display()           //  Utskrift av bladet (Ürstall, nr og antall):
      {  cout << "\n\t" << number/100 << '-' << number % 100 
              << ":  " << antall << " stk.";  }   //  Utskrift til fil:
    void til_fil(ostream* ut)  {  *ut << number << ' ' << antall << '\n';  }
};


class Serie  {               //  Klassen "Serie":
  private:
    char* tittel;            //  Full tittel/navn.
    char* utgiver;           //  Utgiver forlag.
    char* beskrivelse;       //  Generell info om serien.
    char* merknad;           //  Spesielle merknader.
    float hoyde, bredde;     //  Seriens mÜl (bredde og hõyde).
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
int    ant_brukt;               //  NÜvërende antall serier.


int main()   {          //  HOVEDPROGRAM:
  char kommando;             //  Brukerens valg/õnske.

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
  char buf[STRLEN];            //    vha. dialog med brukeren.
  tittel      = new char[strlen(t)+1];    strcpy(tittel, t);
  cout << "\tUtgiver:      ";  cin.getline(buf, STRLEN);
  utgiver     = new char[strlen(buf)+1];  strcpy(utgiver, buf);
  cout << "\tBeskrivelse:  ";  cin.getline(buf, STRLEN);
  beskrivelse = new char[strlen(buf)+1];  strcpy(beskrivelse, buf);
  cout << "\tMerknad:      ";  cin.getline(buf, STRLEN);
  merknad     = new char[strlen(buf)+1];  strcpy(merknad, buf);
  cout << "\tHõyde:        ";  cin >> hoyde;
  cout << "\tBredde:       ";  cin >> bredde;
  cout << "\tAntall sider: ";  cin >> ant_sider;
  blader = new List(Sorted);   //  Lager tom liste av blader.
}
                               //  Leser ALLE data om en serie
                               //    (inkl. bladene) fra fil.
Serie :: Serie(char* t, istream* inn)  {
  char buf[STRLEN];            //  Tekstbuffer.
  int n, nr,                   //  Antall ulike blader og aktuell blad-ID/-nr.
      ant, i;                  //  Antall stk. av ett gitt blad og lõkkevariabel.
  Blad* nytt_blad;             //  Hjelpepeker til ny-opprettelse.
                               //  Leser ALLE generelle data om en serie:
  tittel      = new char[strlen(t)+1];    strcpy(tittel, t);
  inn->getline(buf, STRLEN);
  utgiver     = new char[strlen(buf)+1];  strcpy(utgiver, buf);
  inn->getline(buf, STRLEN);
  beskrivelse = new char[strlen(buf)+1];  strcpy(beskrivelse, buf);
  inn->getline(buf, STRLEN);
  merknad     = new char[strlen(buf)+1];  strcpy(merknad, buf);
  *inn >> hoyde >> bredde >> ant_sider >> n;  inn->ignore();
                               // 'n' er antall blader i serien.

  blader = new List(Sorted);   //  Lager tom liste av blader.
  for (i = 1;  i <= n; i++)  {
      *inn >> nr >> ant;       //  Leser alle data om ETT blad.
      nytt_blad = new Blad(nr, ant);    //  Lager nytt blad-objekt.
      blader->add(nytt_blad);  //  Legger bladet inn i seriens liste.     
  }
  inn->ignore();               //  Forkaster '\n' etter siste leste tall.
}
 

void Serie :: endre_blad()  {  //  Endrer data om et blad.
  int   aar, nr,               //  èrstall og bladnummer.
        id;                    //  ID bygd fra 'aar' og 'nr'.
  char  stat;                  //  FÜtt (+), kvittet seg med (-)
                               //    eller bare registrere (0).
  Blad* bladet;                //  Hjelpepeker til aktuelt blad.

  cout << "\tèrstall: ";  cin >> aar;    //  Leser inn Ürstall, 
  cout << "\tNr:      ";  cin >> nr;     //    nummer og status:
  cout << "\tStatus (+, 0, -): ";  cin >> stat;  cin.ignore();
  id = aar * 100 + nr;         //  Bygger ID.
  if ((bladet = (Blad*) blader->remove(id)) == NULL)  // Bladet IKKE finnes:
     bladet = new Blad(id);           //  Lager et nytt blad-objekt.
  if (stat == '+')      ++*bladet;    //  ùker antallet igjen.
  else if (stat == '-') --*bladet;    //  Minsker antallet igjen (?)
                  //  else (stat == '0'): Antallet oppdateres ikke.
  blader->add(bladet);         //  Legger bladet tilbake (igjen).
}

                             //  Skriver alle generelle data om en serie,
void Serie :: skriv_serie()  {    //  inkl. data om alle bladene til skjerm:
  char ch;
  cout << "\tUtgiver:      " << utgiver
       << "\n\tBeskrivelse:  " << beskrivelse
       << "\n\tMerknad:      " << merknad
       << "\n\tData:         " << hoyde << " x " << bredde << " cm,   "
       << ant_sider << " sider.";
  cout << "\n\t\t\t\t\t\t\tSkriv ett tegn .....";   cin >> ch;
  blader->display_list();
}

                             //  Skriver alle generelle data om en serie,
void Serie :: til_fil(ostream* ut)  {   // inkl. data om alle bladene til fil:
  Blad* bladet;
  int i, n = blader->no_of_elements();  // Henter antall bladeri serien.

  *ut << tittel << '\n'      //  Skriver alle generelle data:
      << utgiver << '\n'
      << beskrivelse << '\n'
      << merknad << '\n'
      << hoyde << ' ' << bredde << ' ' << ant_sider << '\n'
      << n << '\n';          //  Skriver antall blader i serien.
  for (i = 1;  i <= n;  i++)  {         //  GÜr gjennom alle bladene:
      bladet = (Blad*) blader->remove_no(i);  //  Fjerner nr.'i'.
      bladet->til_fil(ut);                    //  Skriver bladet til fil.
      blader->add(bladet);                    //  Legger bladet tilbake igjen.
  }
}



                        //  DEFINISJON AV FUNKSJONER:
void skriv_meny()  {         //  Skriver meny/lovlige kommandoer til bruker:
  cout << "\n\n\nFõlgende kommandoer er lovlig:\n";
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
  char buf[STRLEN];                 //  Tekstbuffer (tittel).
        
  if (ant_brukt < MAX_SERIER)  {    //  Plass til flere serier:
     cout << "\n\tLESER DATA OM EN NY SERIE:\n";   //  Leser seriens tittel:
     cout << "\tTittel:       ";  cin.getline(buf, STRLEN);
     if (!finn_serie(buf))          //  Serien finnes IKKE allerede:
        samling[++ant_brukt] = new Serie(buf);     //  Lager nye serie.
     else                           //  Serien finnes allerede.
        cout << "\n\tDenne serien finnes allerede i samlingen!\n";
  } else                            //  Fullt med serier:
     cout << "\n\tSamling-arrayen er full av serier!\n";
}


void blad_endring()  {       //  Oppgave 2C - Endrer data om ETT blad:
  char buf[STRLEN];                 //  Tekstbuffer (tittel).
  int  nr;                          //  Seriens nummer/indeks i arrayen.
  cout << "\n\tENDRER DATA OM ETT BLAD:\n";   //  Leser seriens tittel:
  cout << "\tTittel:  ";  cin.getline(buf, STRLEN);
  if ((nr = finn_serie(buf)) != 0)            //  Serien finnes:
     samling[nr]->endre_blad();               //  Endrer ett blad i serien.
  else                                        //  Serien finnes IKKE:
     cout << "\n\tDenne serien finnes IKKE i samlingen!\n";
}


void display_en_serie()  {   //  Oppgave 2D - Skriver en serie til skjerm:
  char buf[STRLEN];                 //  Tekstbuffer (tittel).
  int  nr;                          //  Seriens nummer/indeks i arrayen.
  cout << "\n\tSKRIVER DATA OM SERIE:\n";     //  Leser seriens tittel:
  cout << "\tTittel:       ";  cin.getline(buf, STRLEN);
  if ((nr = finn_serie(buf)) != 0)  {         //  Serien finnes:
     samling[nr]->skriv_serie();  cout << '\n';  }  //  Skriver serien.
  else                                        //  Serien finnes IKKE:
     cout << "\n\tDenne serien finnes IKKE i samlingen!\n";
}


void les_fra_fil()  {        //  Oppgave 2E - Leser alle bladene fra fil:
  ifstream innfil("samling.dta");
  char buf[STRLEN];          //  Tekstbuffer (tittel).
  ant_brukt = 0;             //  Nullstiller global variabel.

  if (innfil)  {             //  Filen finnes:
     cout << "\n\tLESER INN DATA FRA FILEN 'SAMLING.DTA'.....\n";
     innfil.getline(buf, STRLEN);    //  Prõver Ü lese tittel.
                             //  Mer igjen Ü lese og fortsatt plass i arrayen:
     while (!innfil.eof()  && ant_brukt < MAX_SERIER)  {  
                             //  Leser inn resten om den nye serien:
       samling[++ant_brukt] = new Serie(buf, &innfil);
       innfil.getline(buf, STRLEN);  //  Prõver Ü lese tittel.
     }
  } else                     //  Filen finnes IKKE:
     cout << "\n\tFinner ikke filen 'SAMLING.DTA' !";
}


void skriv_til_fil()  {      //  Oppgave 2F - Skriver alle bladene til fil:
  ofstream utfil("samling.dta");
  for (int i = 1; i <= ant_brukt;  i++)   //  GÜr gjennom alle seriene,
      samling[i]->til_fil(&utfil);        //    og skriver dem til fil.
}

//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J09_2.CPP

//  Lõsningsforlag til kontinuasjonseksamen i OOP, 5.januar 2009, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2008.


//  Programmet holder orden pÜ EN banks ulike kunder og deres
//      lÜn i banken (til hvilken rente).
//
//  Det er mulig Ü:
//      - skrive alle data om en kunde (til skjerm)        (oppgave 2A)
//      - foreta en innbetaling for en kunde               (oppgave 2B)
//      - endre en kundes "program" (lÜneprosent)          (EXTRA)
//      - endre et "programs" lÜneprosent                  (oppgave 2C)
//      - legge inn en ny lÜnekunde                        (oppgave 2D)
//      - sende ut varsling til ALLE om termininnbetaling  (oppgave 2E)
//      - alle kjõretõy skrives til fil                    (oppgave 2F) 
//      - alle kjõretõy leses fra fil                      (oppgave 2G)

                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  i(f)stream, o(f)stream
#include <cstring>           //  strlen, strcpy
#include <cctype>            //  toupper
#include <cstdlib>           //  atoi, atof
#include "listtool.h"        //  "Verktõykasse" for listehÜndtering.

using namespace std;

                        //  CONST:
const int   STRLEN      =       80;  //  Standard streng-lengde (i array).
const int   ANTPROGRAM  =        5;  //  Antall ulike lÜneprogram banken har.
const int   MAXLAANEAAR =       25;  //  Max. antall lÜneÜr.
const int   MINKONTO    =  1000000;  //  Nummer pÜ fõrste kontonummer.
const int   MAXKONTO    =  9999999;  //  Nummer pÜ siste kontonummer.
const int   MINLAAN     =    10000;  //  Min. belõp pÜ lÜn (10-tusen).
const int   MAXLAAN     = 10000000;  //  Max. belõp pÜ lÜn (10 mill.).
const float MAXPROSENT  =    30.0F;  //  Max. prosent for/pÜ et lÜn.



                        //  KLASSER:
class Kunde : public Num_element  {
  private:                        //  number = kundens ID/kontonummer.
    char  * navn,                 //  Navn.
          * adr,                  //  Adresse (gate og sted).
          * mail;                 //  Mail-adresse.
    int   tlf,                    //  Telefon (fast eller mobil).
          program,                //  LÜneprogramnummer (= 1-5).
          ant_aar;                //  Antall Ür lÜnet gÜr over.
    float belop,                  //  NÜvërende lÜnebelõp.
          avdrag;                 //  MÜnedlig fast avdragsbelõp.

  public:
    Kunde(int nr);                    //  Lag innmaten ifm. oppgave 2D.
    Kunde(int nr, istream* inn);      //  Lag innmaten ifm. oppgave 2G.
    ~Kunde()  {  delete [] navn;  delete [] adr;  delete [] mail;  }
    void display();                   //  Lag innmaten ifm. oppgave 2A.
    void innbetaling();               //  Lag innmaten ifm. oppgave 2B.
    void endre_program();             //  EXTRA.
    void varsel(ostream* ut);         //  Lag innmaten ifm. oppgave 2E.
    void skriv_til_fil(ostream* ut);  //  Lag innmaten ifm. oppgave 2F.
};

class Program  {
  private:
    char* beskrivelse;            //  Beskrivelse av lÜneprogrammet.
    float prosent;                //  NÜvërende lÜneprosent pÜ programmet.

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
void  endre_kunde();                    //  EXTRA.
void  endre_program();                  //  Lag innmaten ifm. oppgave 2C.
void  ny_kunde();                       //  Lag innmaten ifm. oppgave 2D.
void  varsling();                       //  Lag innmaten ifm. oppgave 2E.
void  skriv_til_fil();                  //  Lag innmaten ifm. oppgave 2F.
void  les_fra_fil();                    //  Lag innmaten ifm. oppgave 2G.


                        //  GLOBALE VARIABLE:
List* kunder;                         //  Listen med alle lÜnekundene.
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
      case 'K': endre_kunde();   break;  //  EXTRA
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
  char buff[STRLEN];

  les("Navn     ", buff, STRLEN);           //  Navn:
       navn = new char[strlen(buff)+1];  strcpy(navn, buff);
  les("Adresse  ", buff, STRLEN);           //  Adresse (gate og sted):
       adr  = new char[strlen(buff)+1];  strcpy(adr, buff);
  les("Mail     ", buff, STRLEN);           //  Mail-adresse:
       mail = new char[strlen(buff)+1];  strcpy(mail, buff);
  tlf     = les("Telefon  ", 10000000, 99999999);  //  Telefon.
  program = les("Program  ", 1, ANTPROGRAM);       //  LÜneprogram i banken.
  ant_aar = les("Ant.Ür   ", 1, MAXLAANEAAR);      //  Antall nedbetalingsÜr.
  belop   = les("LÜnebelõp", MINLAAN, MAXLAAN);    //  Initielt lÜnebelõp.
  avdrag  = belop / (ant_aar * 12);                //  MÜnedlig FAST avdrag.
}

                                            //  Oppgave 2G - Leser ALT fra fil:
Kunde::Kunde(int nr, istream* inn) :  Num_element(nr)  {
  char buff[STRLEN];                           
  inn->getline(buff,STRLEN); navn=new char[strlen(buff)+1]; strcpy(navn,buff);
  inn->getline(buff,STRLEN); adr =new char[strlen(buff)+1]; strcpy(adr, buff);
  inn->getline(buff,STRLEN); mail=new char[strlen(buff)+1]; strcpy(mail,buff);
  *inn >> tlf >> program >> ant_aar >> belop >> avdrag;  inn->ignore();
}


void Kunde::display()  {               //  Oppgave 2A - Skriver ALT til skjerm:
  cout << '\t' << number << ":\n\t\t" << navn << "\n\t\t" << adr << "\n\t\t"
       << mail << "\ttlf: " << tlf << "\n\t\tProgram: "
       << program << "  Ant.Ür: " << ant_aar << "  LÜn: "
       << belop << "  Mnd.avdrag: " << avdrag << '\n';
}


void Kunde::innbetaling()  {           //  Oppgave 2B - Trekker fra innbetaling:
  belop -= les("Belõp", 0, belop);
}


void Kunde::endre_program()  {         //  EXTRA - Endrer lÜneprogram i banken:
  cout << "\n\tNÜvërende program: " << program << '\n';
  program = les("Endre til nr", 1, ANTPROGRAM);
}


void Kunde::varsel(ostream* ut)  {     //  Oppgave 2E - Innbet.varsel til fil:
 float prosent = programmer[program]->hent_prosent();  //  Henter lÜneprosent.
 *ut << '\t' << navn << "\n\t" << adr
     << "\n\n\tLÜn-/kundenummer: " << number
     << "\n\tPÜ vÜrt lÜneprogram nr." << program << " (" << prosent
     << "% rente) over " << ant_aar << " Ür\n\thar du et restlÜn pÜ kr." 
     << belop << ". MÜnedlig avdrag er kr." << avdrag
     << ".\n\tInkludert renter innebetales derfor den 15. denne mÜneden kr."
     << avdrag + ((belop * prosent) / (100 * 12)) << ".\n\n\n\n\n"; 
}              // Fast avdrag + siste mÜneds renter.


void Kunde::skriv_til_fil(ostream* ut)  {   //  Oppgave 2F - Skriver til fil:
  *ut << number << '\n' << navn << '\n' << adr << '\n' << mail << '\n' << tlf 
      << ' '<< program << ' '<< ant_aar << ' '<< belop << ' '<< avdrag << '\n';
}



// ********************************  PROGRAM:  ******************************

Program::Program(char* t, float p)  {     //  Oppgave 2G - Setter ALLE verdier:
  beskrivelse = new char[strlen(t)+1];  strcpy(beskrivelse, t);
  prosent = p;
}


void Program::endre_prosent()  {        //  Oppgave 2C - Endrer lÜneprograms %:
  float pro1, pro2;

  cout << "\n\t" << beskrivelse 
       << "\n\tNÜvërende prosent: " << prosent << "\n\n";

  pro1 = les("Endre til", MAXPROSENT);    //  Leser endring.
  pro2 = les("Bekreft", MAXPROSENT);      //  Leser (identisk?) bekreftelse.
  if (pro1 == pro2)  {                    //  Verdier er like:
     prosent = pro1;                      //  Setter varig endring.
     cout << "\n\tNy lÜneprosent for programmet er: " << prosent << '\n';
  } else
     cout << "\n\tVerdiene ulike, derfor ingen endring foretatt!\n\n";  
}


void Program::skriv_til_fil(ostream* ut)  { //  Oppgave 2F - Skriver til fil:
  *ut << prosent << '\n' << beskrivelse << '\n';
}


// ****************************************************************************
// ******************   DEFINISJON AV (GLOBALE) FUNKSJONER:  ******************
// ****************************************************************************

void skriv_meny()  {         //  Skriver alle mulige menyvalg:
  cout << "\n\nFùLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   S  - Skriv ALLE data om EN kunde"
       << "\n   I  - Innbetaling fra en kunde"
       << "\n   K  - endre en Kundes program"
       << "\n   P  - endre et Programs lÜneprosent"
       << "\n   N  - Ny kunde/lÜn"
       << "\n   V  - Varsle ALLE om termininnbetaling"
       << "\n   Q  - Quit / avslutt";
}


char les()  {                //  Leser og upcaser brukerens valg/õnske:
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
    cin.getline(text, STRLEN);   n = atoi(text);  // Leser som tekst - omgjõr:
  } while (n < MIN  ||  n > MAX);
  return n;
}

                             //  Leser en FLOAT mellom 0.1 og MAX:
float les(char* t, const float MAX)  {
  char text[STRLEN];
  float n;
  do  {
    cout << '\t' << t << " (0.1-" << MAX << "): ";
    cin.getline(text, STRLEN); 	n = atof(text);  // Leser som tekst - omgjõr:
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
  if (!kunder->display_element(les("Skriv kundenr", MINKONTO, MAXKONTO)))
     cout << "\n\tIngen kunde/konto med dette nummeret!\n\n";
}


void innbetaling()  {        //  Oppgave 2B - EN kunde foretar innbetaling:
  Kunde* kunde;
  int nr = les("Innbetalende kundenr", MINKONTO, MAXKONTO);  //  Leser kundenr.

  if ((kunde = (Kunde*) kunder->remove(nr)) != NULL)  {      //  Kunden finnes:
     kunde->innbetaling();        //  Innbetaling registreres.           
     kunder->add(kunde);          //  Legger kunden tilbake igjen.
  } else                          //  Ingen kunde med dette nummeret:
     cout << "\n\tIngen kunde/konto med dette nummeret!\n\n";  
}


void endre_kunde()  {        //  EXTRA - Endre en kundes program:
  Kunde* kunde;
  int nr = les("Endre kundenr", MINKONTO, MAXKONTO);         //  Leser kundenr.

  if ((kunde = (Kunde*) kunder->remove(nr)) != NULL)  {      //  Kunden finnes:
     kunde->endre_program();      //  Kundeprogram (lÜneprosent) endres.
     kunder->add(kunde);          //  Legger kunden tilbake igjen.
  } else                          //  Ingen kunde med dette nummeret:
     cout << "\n\tIngen kunde/konto med dette nummeret!\n\n";  
}


void endre_program()  {      //  Oppgave 2C - Endre et programs lÜneprosent:
  programmer[les("Endre programnr", 1, ANTPROGRAM)]->endre_prosent();
}


void ny_kunde()  {           //  Oppgave 2D - Legge inn en ny kunde/lÜn:
  int nr = les("Nytt kundenr", MINKONTO, MAXKONTO);   //  Leser kundenr.

  if (!kunder->in_list(nr))             //  Ny kunde:
     kunder->add(new Kunde(nr));        //  Oppretter og legger inn ny kunde.              
  else
     cout << "\n\tKunde/konto med dette nummeret finnes allerede!\n\n";  
}


void varsling()  {           //  Oppgave 2E - Terminvarsel til ALLE:
  int i, ant = kunder->no_of_elements();     //  Lõkkevar + henter ant.kunder.
  Kunde* kunde;                              //  Hjelpepeker til uttatt kunde.
  ofstream utfil("VARSEL.DTA");

  for (i = 1;  i <= ant;  i++)  {            //  For hver kunde:
      kunde = (Kunde*) kunder->remove_no(i); //  Tar ut kunde nr.'i'.
      kunde->varsel(&utfil);                 //  Skrive eget innbet.varsel.
      kunder->add(kunde);                    //  Legger tilbake kunden.
  }
  cout << "\n\tInnbetalingsvarsel for ALLE er skrevet til 'VARSEL.DTA'.\n\n";
}


void skriv_til_fil()  {    //  Oppgave 2F - Skriv HELE datastrukturen til fil:
  int i, ant = kunder->no_of_elements();     //  Lõkkevar + henter ant.kunder.
  Kunde* kunde;                              //  Hjelpepeker til uttatt kunde.
  ofstream utfil1("PROGRAM.DTA");            //  èpner to aktuelle filer:
  ofstream utfil2("LAANKUND.DTA");
  
  for (i = 1;  i <= ANTPROGRAM;  i++)        //  For hvert program:
      programmer[i]->skriv_til_fil(&utfil1); //  Skrive seg selv til fil.

  for (i = 1;  i <= ant;  i++)  {            //  For hver kunde:
      kunde = (Kunde*) kunder->remove_no(i); //  Tar ut kunde nr.'i'.
      kunde->skriv_til_fil(&utfil2);         //  Skrive seg selv til fil.
      kunder->add(kunde);                    //  Legger tilbake kunden.
  }
}


void les_fra_fil()  {      //  Oppgave 2G - Leser HELE datastrukturen fra fil:
  char   buffer[STRLEN*2];                   //  Tekstlinje fra den 1.filen.
  float  prosent;                            //  LÜneprosent pÜ den 1.filen.
  int    i, nr;                              //  Lõkkevariabel og kundenummer.
  ifstream innfil1("PROGRAM.DTA");           //  èpner to aktuelle filer:
  ifstream innfil2("LAANKUND.DTA");

  if (innfil1  &&  innfil2)  {               //  Begge filene finnes:
     for (i = 1;  i <= ANTPROGRAM;  i++)  {       //  For hvert program:
         innfil1 >> prosent;  innfil1.ignore();   //  Leser lÜne% (1.linje).
         innfil1.getline(buffer, STRLEN*2);       //  Leser beskrivelse.
         programmer[i] = new Program(buffer, prosent);  // Nytt program.
     }

     innfil2 >> nr;                            //  Leser (om mulig) kundenr.
     while (!innfil2.eof())  {                 //  Mer igjen pÜ filen:
        innfil2.ignore();                      //  Skipper '\n'.
        kunder->add(new Kunde(nr, &innfil2));  //  Ny kunde leser resten selv.
        innfil2 >> nr;                         //  Leser (om mulig) kundenr.
     }
//                                      kunder->display_list();
  } else
    cout << "\n\nFant ikke filen 'PROGRAM.DTA' og/eller 'LAANKUND.DTA'!\n\n";
}


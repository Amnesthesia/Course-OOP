//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J07_2.CPP

//  Løsningsforslag til kontinuasjonseksamen i C++, 5.januar 2007, oppgave 2.
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
int idag = 0;               //  Aktuell dag som det legges inn deltagere på.


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
    switch(valg)  {                          // Oppgave 2B:
      case 'S': dagene[les("Dagnummer", 1, ANTDAGER)]->display(); break; 
      case 'B': bytt_dag();          break;  //  Oppgave 2C
      case 'N': dagene[idag]->ny();  break;  //  Oppgave 2D
      case 'T': trekk();             break;  //  Oppgave 2G
      default:  skriv_meny();        break;
    }
    valg = les_kommando();
  }

//  skriv_til_fil();                      //  Oppgave 2E
  cout << "\n\n";
  return 0;
}


                        //  DEFINISJON AV MEDLEMS-FUNKSJONER:

//***************************  DELTAGER:  ***************************
                             //  OPPGAVE 2D:
Deltager::Deltager(int n) : Num_element(n)  { // Setter/leser ALLE dets data:
  char buffer[STRLEN];
  cout << "\tNavn:     ";  cin.getline(buffer, STRLEN);
  navn = new char[strlen(buffer)+1];  strcpy(navn, buffer);
  cout << "\tAdresse:  ";  cin.getline(buffer, STRLEN);
  adr  = new char[strlen(buffer)+1];  strcpy(adr, buffer);
}

                             //  OPPGAVE 2F:
Deltager::Deltager(int n, istream* inn) : Num_element(n)  {
  char buffer[STRLEN];                        //  Leser ALLE dets data fra fil:
  (*inn).getline(buffer, STRLEN);
  navn = new char[strlen(buffer)+1];  strcpy(navn, buffer);
  (*inn).getline(buffer, STRLEN);
  adr  = new char[strlen(buffer)+1];  strcpy(adr, buffer);
}

                             //  OPPGAVE 2B:
void Deltager::display()  {                   // Skriver ALLE dets data:
  cout << "\t\t" << number << "  " << navn << ", " << adr << '\n';
}


                             //  OPPGAVE 2E:
void Deltager::skriv_til_fil(ostream* ut)  { // Skriver ALLE dets data til fil:
  *ut << number << '\n' << navn << '\n' << adr << '\n';
}


//******************************  DAG:  *****************************

                             //  OPPGAVE 2A:
Dag::Dag() {                                  //  Initierer ALLE dets data:
  trukket = false;  deltagere = new List(Sorted);  vinnere = new List(FIFO);
}

                             //  OPPGAVE 2B:
void Dag::display()  {                        //  Skriver ALLE dets data:
  cout << "\n\tDagen er " << ((!trukket)? "IKKE " : "") << "trukket!\n";
  cout << "\tDeltagerliste:\n";  deltagere->display_list();
  if (trukket)  {            //  Trekning foretatt - elementer i vinnerlisten:
     cout << "\n\tVinnere:\n";     vinnere->display_list();
  }
}

                             //  OPPGAVE 2D:
void Dag::ny()  {                             //  Legger inn ny deltager:
  if (!trukket)  {                               //  Ikke trukket enn†:
     int tlf = les("Tlf ", 10000000, 99999999);  //  Leser tlf. til den nye.
     if (!deltagere->in_list(tlf))               //  Finnes ikke fra før:
        deltagere->add(new Deltager(tlf));       //  Lager ny og legger inn.
     else                                        //  Finnes fra før:
        cout << "\n\tDette telefonnummeret deltar allerede denne dagen!!!\n\n";
  } else                                         //  Ferdigtrukket allerede:
    cout << "\n\tAktuell dag er allerede ferdigtrukket!!!\n\n";
}

                             //  OPPGAVE 2E:
void Dag::skriv_til_fil(ostream* ut)  {  //  Skriver ALT om EN dag til fil:
  int i, ant;                            //  Løkkevariabel og antall deltagere.
  Deltager* delt;                        //  Hjelpepeker til en deltager.
  
  ant = deltagere->no_of_elements();     //  Antall deltagere.
  *ut << ((trukket)? 'T' : 'I') << '\n' <<  ant << '\n'; // Skriver (u)trukket.
  for (i = 1;  i <= ant;  i++)  {                   //  For hver deltager:
      delt = (Deltager*) deltagere->remove_no(i);   //  Tar ut nr.'i'.
      delt->skriv_til_fil(ut);                      //  Skriver seg til fil.
      deltagere->add(delt);                         //  Legges tilbake igjen.
  }

  ant = vinnere->no_of_elements();                  //  Antall vinnere.
  *ut << ant << '\n';                               //  Skriver antallet.
  for (i = 1;  i <= ant;  i++)  {                   //  For vinner:
      delt = (Deltager*) vinnere->remove();         //  Tar ut nr.'i'.
      delt->skriv_til_fil(ut);                      //  Skriver seg til fil.
      vinnere->add(delt);                           //  Legges tilbake igjen.
  }
}

                             //  OPPGAVE 2F:
void Dag::les_fra_fil(istream* inn)  {  //  Leser ALT om EN dag fra fil:
  char tegn;                            //  'I'(kke trukket) eller 'T'(rukket).
  int i, ant, tlf;                  //  Løkkevariabel, #deltagere og telefonnr.
  *inn >> tegn;                         //  Leser 'I' eller 'T'.
  trukket = (tegn == 'T');              //  Setter 'trukket' ut fra bokstaven.
  *inn >> ant;                          //  Leser antall deltagere:
  for (i = 1;  i <= ant;  i++)  {       //  Leser inn disse:
      *inn >> tlf;  (*inn).ignore();    //  Leser 1.felt (telefonnr).
      deltagere->add(new Deltager(tlf, inn)); // Legger inn ny som leser selv.
  }
  *inn >> ant;                          //  Leser antall vinnere:
  for (i = 1;  i <= ant;  i++)  {       //  Leser inn disse:
      *inn >> tlf;  (*inn).ignore();    //  Leser 1.felt (telefonnr).
      vinnere->add(new Deltager(tlf, inn));   // Legger inn ny som leser selv.
  }
}


                             //  OPPGAVE 2G:
void Dag::trekk()  {                    //  Foretar evt. trekning av vinnere:
  int i, ant,                           //  Løkkevariabel, antall premier.
      max, vinner;                      //  Antall deltagere igjen, vinnernr.
  Deltager* delt;                       //  Hjelpepeker til en deltager.

  max = deltagere->no_of_elements(); //  Henter antall deltagere.
  if (max > 0)  {                    //  Det finnes deltagere:
     ant = les("Antall vinnere/premier", 0, max/2);  // Leser ant. premier:
     if (ant != 0)  {                //  Premier finnes:
        trukket = true;              //  Status er at er "ferdigtrukket".
        for (i = 1;  i <= ant;  i++)  {     //  For hver premie:
            vinner = (rand() % max--) + 1;  //  Trekker en vinner:
            delt = (Deltager*) deltagere->remove_no(vinner); //Henter denne.
            cout << "\n\t" << i << ".premie:";  //  Skriver vinners data:
            delt->display();    // (Burde også til egen fil: DAG_x.DTA ...)
            vinnere->add(delt);      //  Legger inn blant vinnerne.
        }
     } else
       cout << "\n\tOK, ingen trekning ble foretatt!\n\n";
  } else
    cout << "\n\tIngen deltagere ennå denne dagen!\n\n";
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


                             //  OPPGAVE 2A:
void initier()  {                    //  Initierer alle de 24 dagene:
  for (int i = 1;  i <= ANTDAGER;  i++)
      dagene[i] = new Dag();
}

                             //  OPPGAVE 2C:
void bytt_dag()  {                   //  Bytter til annen/ny aktuell dag:
  int dag = les("\n\tDagnummer", 1, ANTDAGER); //  Leser et aktuelt dagnummer.
  if (!dagene[dag]->er_trukket())         //  Om ikke er ferdig trukket:
     idag = dag;                          //  Oppdaterer aktuell dag.
  else                                    //  Ferdigtrukket allerede:
     cout << "\n\tUlovlig dagnummer, da er allerede trukket!!!\n\n";
}

                             //  OPPGAVE 2E:
void skriv_til_fil()  {                //  Skriver HELE datastrukturen til fil:
  ofstream utfil("ADVENT.DTA");
  for (int i = 1;  i <= ANTDAGER;  i++)
      dagene[i]->skriv_til_fil(&utfil);
}

                             //  OPPGAVE 2F:
void les_fra_fil()  {                  //  Leser HELE datastrukturen fra fil:
  ifstream innfil("ADVENT.DTA");
  if (innfil)  {                       //  Filen er å finne:
      for (int i = 1;  i <= ANTDAGER;  i++)
    	  dagene[i]->les_fra_fil(&innfil);
  } else                               //  Filen finnes ikke:
     cout << "\n\tFant ikke filen 'ADVENT.DTA'!\n\n";
}

                             //  OPPGAVE 2G:
void trekk()  {                      //  Foretar evt. trekning på aktuell dag:
  char ch;                           //  Brukerens svar/ønske.

  if (!dagene[idag]->er_trukket())  {      //  Ikke trukket allerede:
     cout << "\n\tVil du VIRKELIG foreta trekning for dag nr." 
          << idag << " (j/N)?  ";   cin >> ch;
     if (toupper(ch) == 'J')               //  Ønsker trekning (svar='j'):
        dagene[idag]->trekk();             //  Foretar evt. trekning.
     else                                  //  Angret seg (svarte IKKE 'J'):
        cout << "\n\tOK, ingen trekning ble foretatt!\n\n";
  } else                                   //  Ferdigtrukket allerede:
        cout << "\n\tAktuell dag er allerede ferdigtrukket!!!\n\n";
}

//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_V12_2.CPP

//  Lõsningsforlag til eksamen i OOP, 1.juni 2012, oppgave 2.
//  Laget av Frode Haug, HiG, mai 2012.


//  Programmet holder orden pÜ to ulike klubbers fotballfans og hvordan 
//    disse fordeler seg pÜ ulike hoteller i en og samme by.

//  Det er mulig Ü:
//      - fÜ antall ulike fan pÜ de ulike hoteller          (Oppgave 2A)
//      - fÜ oversikt over de ulike fan pÜ ETT hotell       (Oppgave 2B)
//      - la en gjest dra fra et hotell                     (Oppgave 2C)
//      - la en gjest ankomme et hotell                     (Oppgave 2D)
//      - finne en navngitt person                          (Oppgave 2E)
//      - Skrive hele datastrukturen til fil                (Ferdigkodet)
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
const int MAXROMNR  =      9999;   //  Max. romnummer pÜ ett hotell.
const int MINPID    =         1;   //  Min. personnummer/-ID.
const int MAXPID    = 999999999;   //  Max. personnummer/-ID.
enum  kategori { City, United, Noytral };  //  En gjests/fans kategori/type.


                        //  KLASSER:
class Hotell  {
  private:
    char* navn;              //  Hotellets navn.
    char* data;              //  Alle andre data (adresse, tlf, ...)
    int   ant_C,             //  Antall City-fans pÜ hotellet.
          ant_U,             //  Antall United-fans pÜ hotellet.
          diff;              //  Max. differanse (antall) pÜ C- og U-fans.
    List* gjester;           //  Gjestene som for õyeblikket er pÜ hotellet.

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
    void skriv_til_fil(ostream* ut);   //  (Ferdigkodet)
};


class Gjest : public Num_element  {
  private:                   //  Number = personID (helt unikt (person)nummer).
    char*    navn;           //  Gjestens navn.
    int      romnr;          //  Romnummer pÜ hotellet.
    kategori kat;            //  Type "fan" (City, United, Noytral).

  public:
    Gjest(kategori kat2, int pID);    //  (Ferdigkodet)
    Gjest(istream* inn, int pID);     //  Lag innmaten ifm. oppgave 2F.
    ~Gjest();                         //  (Ferdigkodet)
    void display();                   //  (Ferdigkodet)
    bool operator == (kategori kat2); //  (Ferdigkodet)
    bool operator == (char* t);       //  (Ferdigkodet)
    void skriv_til_fil(ostream* ut);  //  (Ferdigkodet)
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
void skriv_til_fil();         //  (Ferdigkodet)
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
            hoteller[les("Skriv fans pÜ hotell nr", 1, ant_hoteller)]->skriv2();
                                         break;  //  Oppgave 2B
      case 'D': drar();                  break;  //  Oppgave 2C
      case 'K': kommer();                break;  //  Oppgave 2D
      case 'F': finn_person();           break;  //  Oppgave 2E
      case 'T': skriv_til_fil();         break;
      default:  skriv_meny();            break;
    }
    valg = les();
  }
  skriv_til_fil();
  cout << "\n\n";
  return 0;
}

// *************************************************************************
// ******************  DEFINISJON AV MEDLEMS-FUNKSJONER:  ******************
// *************************************************************************

//***************************  HOTELL:  *******************************

                                //  Oppgave 2F - Constructor som leser fra fil:
Hotell::Hotell(istream* inn)  {
  int i, ant, nr;                     //  Lõkkevariabel, ant.gester, persID.
  char buffer[STRLEN];                //  Tekstlinje fra fil.
  (*inn).getline(buffer, STRLEN);     //  Leser inn hotellets navn:
  navn = new char[strlen(buffer)+1]; strcpy(navn, buffer);
  (*inn).getline(buffer, STRLEN);     //  Leser inn hotellets andre data:
  data = new char[strlen(buffer)+1]; strcpy(data, buffer);
  *inn >> ant >> ant_C >> ant_U >> diff;  (*inn).ignore(); // Leser div.tall.
  gjester = new List(Sorted);         //  Oppretter tom gjesteliste.
  for (i = 1;  i <= ant;  i++) {      //  For hver gjest pÜ hotellet:
      *inn >> nr;
      gjester->add(new Gjest(inn, nr));
  }
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
       << "\tAnt.nõytrale: " << (gjester->no_of_elements() - ant_C - ant_U)
       << "\tMax.diff: " << diff;
}

                                //  Referanseoverfõrer tilbake 2x verdier:
void Hotell::hent_antall(int & an_C, int & an_U)  {
  an_C = ant_C;      an_U = ant_U;
}

                                //  Oppgave 2B - Skriver hotellets gjester - 
void Hotell::skriv2()  {        //    gruppert/sortert etter fan-grupper:
  Gjest* gjest;                           //  Hjelpepeker.
  kategori kat2;                          //  Aktuell enum-verdi.
  int i, j, n = gjester->no_of_elements();  //  Lõkkevariable og ant.i listen.
  char txt[3][8] = { "CITY", "UNITED", "NùYTRAL" };   //  Ledetekster.
  for (i = 0;  i <= 2;  i++)  {           //  GÜr gjennom fan.gruppene:
      kat2 = (kategori) i;                //  Omgjõr til enum-verdi.
      cout << "\n\n\t" << txt[i] << "-fan(s):";  // Innledningstekst pr.gruppe.
      for (j = 1;  j <= n;  j++)  {       //  GÜr gjennom listen:
          gjest = (Gjest*) gjester->remove_no(j); //  Tar ut en og en.
          if (*gjest == kat2)             //  Gjesten av aktuell fan-gruppe.
             gjest->display();            //  Gjesten skrives.
          gjester->add(gjest);            //  Legger gjesten tilbake i listen.
      }
   }
}


void Hotell::slett(int nr)  {   //  Oppgave 2C - Sletter/fjerner en gjest:
  Gjest* gjest = (Gjest*) gjester->remove(nr);  //  Prõver Ü ta ut gjesten.
  if (gjest)  {                                 //  Gjesten ble funnet:
     if (*gjest == City)  ant_C--;              //  Teller ned #City-fans.
     else if (*gjest == United)  ant_U--;       //  Teller ned #United-fans.
     delete gjest;                              //  Sletter/fjerner gjesten.
  } else
    cout << "\n\tIngen gjest pÜ hotellet med dette nummeret!\n";
}

                                //  Oppgave 2D- Prõver Ü legge inn en gjest:
bool Hotell::innlosjer(kategori kat2, int nr)  {
  if ((kat2 == City    &&  ant_C < ant_U+diff)  ||  //  Plass til fler C-fans.
      (kat2 == United  &&  ant_U < ant_C+diff)  ||  //  Plass til fler U-fans.
      (kat2 == Noytral)) {                          //  Alltid OK med nõytrale.
          gjester->add(new Gjest(kat2, nr));        //  Lager og legger inn ny.
          if (kat2 == City)  ant_C++;               //  Teller opp #C-fans
          else if (kat2 == United)  ant_U++;        //    eller #U-fans.
          return true;                              //  Gikk greit Ü legge inn.
  } else
    return false;                                   //  Ikke mulig Ü legge inn.
}

                                //  Oppgave 2E - Leter etter navngitt gjest
bool Hotell::finn_og_skriv(char* nvn)  {   //  og skriver om nõdvendig:
  int i = 0, ant = gjester->no_of_elements();  //  Teller og antall gjester.
  Gjest* gjest;                            //  Hjelpepeker.
  bool funn = false;                       //  EnnÜ ikke funnet vedkommende.
  while (!funn  &&  i < ant)  {            //  Ikke funnet ennÜ og fler igjen:
    gjest = (Gjest*) gjester->remove_no(++i); //  Tar ut en og en.
    if (*gjest == nvn) {                   //  Gjesten har aktuelt/sõkt navn:
       funn = true;                        //  Fant vedkommende.
       gjest->display();                   //  Gjesten skrives.
    }
    gjester->add(gjest);                   //  Legger gjesten tilbake i listen.
  }                                        //  Returnerer om funnet
  return funn;                             //    og skrevet eller ei.
}

                              //  Skriver ALT om hotellet til fil:
void Hotell::skriv_til_fil(ostream* ut)  {
  int ant = gjester->no_of_elements();    //  Antall gjester.
  Gjest* gjest;                           //  Hjelpepeker.
  *ut << navn << '\n' << data << '\n'     //  Skriver alle egne data:
      << ant << ' ' << ant_C << ' ' << ant_U << ' ' << diff << '\n';
  for (int i = 1;  i <= ant;  i++)  {     //  For alle hotellets gjester:
      gjest = (Gjest*) gjester->remove_no(i); //  Tar ut en og en.
      gjest->skriv_til_fil(ut);           //  Gjesten skriver seg selv til fil.
      gjester->add(gjest);                //  Legger gjesten tilbake i listen.
  }
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
  char kat2;
  char buffer[STRLEN];
  *inn >> romnr >> kat2;   (*inn).ignore();  //  Leser romnummer og fan-kat.
  (*inn).getline(buffer, STRLEN);            //  Leser gjestens navn:
  navn = new char[strlen(buffer)+1]; strcpy(navn, buffer);
  switch (kat2)  {                           //  Konverterer bokstav til enum:
    case 'C':  kat = City;     break;
    case 'U':  kat = United;   break;
    case 'N':  kat = Noytral;  break; 
  }
}


Gjest::~Gjest()  {                    //  Sletter alt allokert vha. "new":
   delete [] navn;
}


void Gjest::display()  {              //  Skriver ALLE objektets data:
   cout << "\n\t" << number << ": " << navn << "\t(rom: " << romnr << ") - ";
   switch (kat)  {                               //  Skriver enum-verdier
     case City:     cout << "City";     break;   //    som tekst:
     case United:   cout << "United";   break;
     case Noytral:  cout << "Nõytral";  break;
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

                            //  Skriver ALLE egne datamedlemmer til fil:
void Gjest::skriv_til_fil(ostream* ut)  { 
  *ut << number << ' ' << romnr << ' ';    //  PersonID og romnummer.
  switch (kat)  {                          //  Gjõr om enum-verdi til bokstav:
    case City:     *ut << 'C';    break;
    case United:   *ut << 'U';    break;
    case Noytral:  *ut << 'N';    break;
  }
  *ut << ' '  << navn << '\n';             //  Gjestens navn.
}



// ****************************************************************************
// ******************   DEFINISJON AV (GLOBALE) FUNKSJONER:  ******************
// ****************************************************************************

void skriv_meny()  {                 //  Skriver alle mulige menyvalg:
  cout << "\n\nFùLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   A  - Antall ulike fans pÜ alle byens ulike hoteller"
       << "\n   H  - skriv ett Hotell (usortert)"
       << "\n   S  - Skriv ett hotell (sortert)"
       << "\n   D  - gjest Drar"
       << "\n   K  - gjest Kommer"
       << "\n   F  - Finn en navngitt person"
       << "\n   T  - skriv Til fil"
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
int finn_gjest(int nr)  {       //     hotellets nummer der er Ü finne, evt. 0:
  for (int i = 1;  i <= ant_hoteller;  i++)   //  For hvert hotell:
      if (hoteller[i]->inneholder(nr))        //  Er Ü finne pÜ hotell nr.'i':
         return i;
  return 0;                                   //  Ingen funn - returnerer '0'.
}

                 //  Oppgave 2A - Antall C- og U-fan pÜ hvert hotell og totalt:
void antall_paa_hotellene()  {  
  int tot_C = 0,  tot_U = 0, an_C, an_U;       //  Totalt variable og retur-var.
  for (int i = 1;  i <= ant_hoteller;  i++)  { //  For hvert hotell:
      hoteller[i]->hent_antall(an_C, an_U);    //  Referanseoverfõr 2x verdier.
      cout << "\n\tHotell nr." << i << ':'     //  Skriv de 2x ut:
           << "\tAnt.City: " << an_C << "\tAnt.United: " << an_U;
      tot_C += an_C;  tot_U += an_U;           //  Tell opp totalt antall.
  }
  cout << "\n\n\tPÜ hotellene:"                //  Skriv totalt antall:
       << "\tTot.City: " << tot_C << "\tTot.United: " << tot_U;
}


void drar()  {             //  Oppgave 2C - Hotellgjest drar (fra et hotell):
  int i, pID = les("Hvilket personID drar", MINPID, MAXPID);
  if ((i = finn_gjest(pID)))  {     //  Gjest med nummer/ID finnes:
     hoteller[i]->slett(pID);       //  Fjerner/sletter fra aktuelt hotell:
     cout << "\n\tGjesten er fjernet fra hotell nr." << i << "\n\n";
  } else
    cout << "\n\tIngen person med denne ID pÜ noen av hotellene!\n\n";
}


void kommer()  {           //  Oppgave 2D - Hotellgjest ankommer (et hotell):
  int pID, hnr, kat, i;         //  PersonID, hotellnr, fan-gruppenr, teller.
  kategori kat2;                //  Fan-gruppe (enum-verdi).
  bool  ferdig = false;         //  Forelõpig ikke ferdig (plassert ny gjest).
  pID = les("Unik personID", MINPID, MAXPID);  //  Leser personID.
  if (!finn_gjest(pID))  {                     //  Finnes ikke allerede:
     i = hnr = les("ùnsker Ü bo pÜ hotell nr", 1, ant_hoteller); //Hotell-õnske
     kat = les("Fan (0=City, 1=United, 2=Nõytral)", 0, 2);  // Fan-kategori.
     kat2 = (kategori) kat;                    //  Gjõr om til enum-verdi.

     do  {                                     //  Lõkke gjennom hotellene:
       ferdig = hoteller[i]->innlosjer(kat2, pID);    //  Plass pÜ hotellet?
       if (ferdig)                                    //  "Ja":
          cout << "\n\tPlassert pÜ hotell nr." << i << "\n\n";
       else {                                         //  "Nei":
          i++;                           //  Neste hotell (i++), 
          if (i > ant_hoteller) i = 1;   //    evt. "wrapper" om til nr.1.
       }
     } while (!ferdig  &&  i != hnr);    //  EnnÜ ikke funn eller tilbake til
                                         //    hotellet der man startet (hnr).
     if (!ferdig)                                //  Ingen hoteller med plass:
        cout << "\n\tFinn deg i stedet et hotell i LivePool.\n\n";
  } else
    cout << "\n\tGjest med denne ID finnes allerede pÜ et av hotellene!\n\n";
}


void finn_person()  {  // Oppgave 2E - Leter etter navngitt person pÜ hotellene:
  char nvn[STRLEN];                           //  Sõkt gjests navn.
  bool funn;                                  //  Funnet gjesten eller ei.
  les("Sõkt persons navn", nvn, STRLEN);      //  Leser sõkenavnet.
  for (int i = 1;  i <= ant_hoteller;  i++)   //  GÜr gjennom hotellene:
      if ((funn = hoteller[i]->finn_og_skriv(nvn))) {  //  Funn og utskrift:
         cout << "\n\n\tVedkommende bor pÜ hotell nr." << i << "\n\n";
         break;                               //  Slutter Ü lete.
      }
  if (!funn)                                  //  Ikke pÜ noen av hotellene:
     cout << "\n\tIngen gjest med dette navnet pÜ noen av hotellene!\n\n";
}


void skriv_til_fil()  {    //  Skrive HELE datastrukturen til fil:
  ofstream utfil("FANS_HTL.DT2");            //  Aktuell fil Üpnes.
  cout << "\n\nSkriver til 'FANS_HTL.DTA' .....\n\n";
  utfil << ant_hoteller << '\n';             //  Skriver antall hoteller.
  for (int i = 1;  i <= ant_hoteller;  i++)  //  For alle aktuelle hoteller:
      hoteller[i]->skriv_til_fil(&utfil); // Hoteller(+gjester) skrives til fil.
}


void les_fra_fil()  {       //  Oppgave 2F - Leser HELE datastrukturen fra fil:
  ifstream innfil("FANS_HTL.DTA");                 //  Aktuell fil Üpnes.
  if (innfil)  {                                   //  Filen finnes:
     innfil >>  ant_hoteller;   innfil.ignore();   //  Leser ant.hoteller.
     if (ant_hoteller <= MAXHOTELL)  {             //  Sprenger IKKE array:
        for (int i = 1;  i <= ant_hoteller;  i++)  //  For hvert hotell:
            hoteller[i] = new Hotell(&innfil); //  Nytt opprettes. Leser resten
     } else                                    //    selv, inkl. sine gjester.
       cout << "\nFor mange hoteller pÜ filen 'FANS_HTL.DTA'.\n\n";
  } else
    cout << "\n\nFinner ikke filen 'FANS_HTL.DTA'.\n\n";
}


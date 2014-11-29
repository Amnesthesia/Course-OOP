//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J08_2.TPL

//  Hovedrisset til kontinuasjonseksamen i OOP, 4.januar 2008, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2007.


//  Programmet holder orden p† ulike DVDer (med unike numre) i ulike kategorier.
//
//  Det er mulig †:
//      - skrive ut alle hoveddata om kategoriene
//      - skrive ut ALT om EN kategori (inkl. DVDene)
//      - legge inn en ny kategori
//      - legge inn en ny DVD
//      - slette/fjerne en DVD
//      - slette/fjerne en kategori (og da slette eller flytte DVDene)
//      - lese fra (/skrive til) fil

                        //  INCLUDE:
#include <iostream>          //  cin, cout
#include <fstream>           //  i(f)stream, o(f)stream
#include <iomanip>           //  setw
#include <cstring>           //  strlen, strcpy
#include <cctype>            //  toupper
#include <cstdlib>           //  atoi
#include "listtool.h"        //  "Verkt›ykasse" for listeh†ndtering.

using namespace std;

                        //  CONST:
const int STRLEN   =  80;    //  Max. streng-lengde.
const int MAXKAT   =  50;    //  Max. antall kategorier med DVDer.


                        //  KLASSER:
class DVD : public Text_element  {
  private:                   //  Text=13-sifret unikt tall (int er for liten).
    char* tittel;            //  Filmens/DVDens tittel.
    char* beskr;             //  Beskrivelse av selve filmen/innholdet.
    char* extra;             //  beskrivelse av ekstramaterialet.
    int aar;                 //  Utgivelses†r.
                             //  Kunne ha v‘rt MASSE andre data ogs† ......
  public:                    //  Funksjons-deklarasjoner:
    DVD(char t[]);                     //  Lag innmaten ifm. oppgave 2D
    ~DVD();
    void display();                    //  Lag innmaten ifm. oppgave 2A
    void les_data();                   //  Lag innmaten ifm. oppgave 2D
    void les_fra_fil(istream *inn);    //  Lag innmaten ifm. oppgave 2G
};


class Kategori  {
  private:
    char* navn;              //  Kategoriens navn.
    List* dvdene;            //  Liste med/av DVDene i kategorien.

  public:                    //  Funksjons-deklarasjoner:
    Kategori(char t[]);                //  Lag innmaten ifm. oppgave 2B
    ~Kategori();
    void skriv();                      //  Lag innmaten ifm. oppgave 2A
    void skriv_alt();                  //  Lag innmaten ifm. oppgave 2A
    bool inneholder(char t[]);         //  Lag innmaten ifm. oppgave 2C
    void ny(char t[]);                 //  Lag innmaten ifm. oppgave 2D
    void ny(DVD* d);                   //  Lag innmaten ifm. oppgave 2F
    void slett(char t[]);              //  Lag innmaten ifm. oppgave 2E
    bool tom();                        //  Lag innmaten ifm. oppgave 2F
    DVD* hent_forste();                //  Lag innmaten ifm. oppgave 2F
    void les_fra_fil(istream *inn);    //  Lag innmaten ifm. oppgave 2G
};

                        //  DEKLARASJON AV FUNKSJONER:
void skriv_meny();
char les();
int  les(char* t, const int MIN, const int MAX);
void les(const char t[], char s[], const int LEN);
void skriv_kategoriene();              //  Oppgave 2A
void skriv_en_kategori();              //  Oppgave 2A
void ny_kategori();                    //  Oppgave 2B
int  finn_DVD();                       //  Oppgave 2C
void ny_DVD();                         //  Oppgave 2D
void slett_DVD();                      //  Oppgave 2E
void slett_kategori();                 //  Oppgave 2F
void les_fra_fil();                    //  Oppgave 2G
//  void skriv_til_fil();              //  EXTRA - IKKE implementert/laget.

                        //  GLOBALE VARIABLE:
Kategori* kategoriene[MAXKAT+1];       //  Datastrukturen (bruker 1-50).
int  siste_kat;                        //  Brukt av arrayen over.

                        //  HOVEDPROGRAM:
int main()  {
  char valg;

  les_fra_fil();                                //  Oppgave 2G
  skriv_meny();
  valg = les();
  while (valg != 'Q')  {
    switch(valg)  {
      case 'K': skriv_kategoriene();   break;	//  Oppgave 2A
      case 'S': skriv_en_kategori();   break;	//  Oppgave 2A
      case 'N': ny_kategori();         break;	//  Oppgave 2B
      case 'D': ny_DVD();              break;	//  Oppgave 2D
      case 'F': slett_DVD();           break;	//  Oppgave 2E
      case 'X': slett_kategori();      break;	//  Oppgave 2F
      default:  skriv_meny();          break;
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


// ********************************  DVD:  *******************************

DVD::DVD(char t[]) : Text_element(t)  {   //  Nullstiller:
        //  Oppgave 2D:  Lag innmaten   
}

DVD::~DVD()  {                            //  Frigir alt allokert:
  delete [] tittel;  delete [] beskr;  delete [] extra;
}


void DVD::display()  {                    //  Skriver alle data:
        //  Oppgave 2A:  Lag innmaten   
}


void DVD::les_data()  {                   //  Leser inn ALLE data:
        //  Oppgave 2D:  Lag innmaten   
}


void DVD::les_fra_fil(istream *inn)  {    //  Leser ALT fra fil:
        //  Oppgave 2G:  Lag innmaten   
}


// ******************************  KATEGORI:  ******************************

Kategori::Kategori(char t[])  {      //  Initierer ALLE data:
        //  Oppgave 2B:  Lag innmaten   
}


Kategori::~Kategori()     {  delete [] navn;  delete dvdene;  }


void Kategori::skriv()  {            //  Skriver navn og antall DVDer:
        //  Oppgave 2A:  Lag innmaten   
}


void Kategori::skriv_alt() {         //  Skriver ALT:
        //  Oppgave 2A:  Lag innmaten   
}

                                     //  Returnerer om noen DVD har 't' som ID:
bool Kategori::inneholder(char t[])  {    
        //  Oppgave 2C:  Lag innmaten   
}


void Kategori::ny(char t[])  {       //  Legger inn ny DVD:
        //  Oppgave 2D:  Lag innmaten   
}


void Kategori::ny(DVD* d)  {         //  Legger inn DVD:
        //  Oppgave 2F:  Lag innmaten   
}


void Kategori::slett(char t[])  {    //  Sletter/fjerner DVD med ID lik 't':
        //  Oppgave 2E:  Lag innmaten   
}


bool Kategori::tom()  {              // Returnerer om kategori er tom eller ei:
        //  Oppgave 2F:  Lag innmaten   
}


DVD* Kategori::hent_forste()  {      //  Returnerer med f›rste DVD i lista:
        //  Oppgave 2F:  Lag innmaten   
}


void Kategori::les_fra_fil(istream *inn)  {  //  Leser fra fil:
        //  Oppgave 2G:  Lag innmaten   
}


// ****************************************************************************
// ******************   DEFINISJON AV (GLOBALE) FUNKSJONER:  ******************
// ****************************************************************************

void skriv_meny()  {                 //  Skriver alle mulige menyvalg:
  cout << "\n\nFLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n   K  - skriv Kategori(navnene)"
       << "\n   S  - Skriv en kategori(s DVDer)"
       << "\n   N  - Ny kategori"
       << "\n   D  - ny DVD"
       << "\n   F  - Fjern/slett en DVD"
       << "\n   X  - fjern/slett en kategori - evt. flytt/slett dets DVDer"
       << "\n   Q  - Quit / avslutt";
}


char les()  {                //  Leser og upcaser brukerens valg/›nske:
  char ch;
  cout << "\n\nKommando: ";
  cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                             //  Leser et TALL mellom MIN og MAX:
int les(char* t, const int MIN, const int MAX)  {
  char text[STRLEN];
  int n;
  do  {
    cout << '\t' << t << " (" << MIN << '-' << MAX << "): ";
    cin.getline(text, STRLEN);   n = atoi(text);  // Leser som tekst - omgj›r:
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


void skriv_kategoriene()  {  //  Skriver ALLE kategorienes navn:
        //  Oppgave 2A:  Lag innmaten   
}


void skriv_en_kategori()  {  //  Skriver ALT om EN kategori:
        //  Oppgave 2A:  Lag innmaten   
}


void ny_kategori()  {        //  Legger inn en ny kategori:
        //  Oppgave 2B:  Lag innmaten   
}

                             //  Finner (om mulig) og returnerer indeks for
int finn_DVD(char t[])  {    //    kategori der DVD med ID lik 't' er:
        //  Oppgave 2C:  Lag innmaten   
}


void ny_DVD()  {             //  Legger inn ny DVD i kategori:
        //  Oppgave 2D:  Lag innmaten   
}

void slett_DVD()  {          //  Slett/fjern en gitt DVD:
        //  Oppgave 2E:  Lag innmaten   
}

                             //  Sletter en hel kategori, men tilbyr
void slett_kategori()  {     //    brukeren † flytte alle dets DVDer:
        //  Oppgave 2F:  Lag innmaten   
}


void les_fra_fil()  {        //  Leser HELE datastrukturen fra fil:
        //  Oppgave 2G:  Lag innmaten   
}

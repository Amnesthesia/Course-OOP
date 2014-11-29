//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J08_2.CPP

//  L›sningsforslag til kontinuasjonseksamen i OOP, 4.januar 2008, oppgave 2.
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

DVD::DVD(char t[]) : Text_element(t)  {   //  OPPGAVE 2D - Nullstiller:
  tittel = beskr = extra = NULL;  aar = 0;
}

DVD::~DVD()  {                            //  Frigir alt allokert:
  delete [] tittel;  delete [] beskr;  delete [] extra;
}


void DVD::display()  {                    //  OPPGAVE 2A - Skriver alle data:
  cout << '\t' << tittel << "  (nr." << text << "),  "  << aar
       << "\n\t\t" << beskr << "\n\t\t" << extra << '\n'; 
}


void DVD::les_data()  {                   //  OPPGAVE 2D - Leser inn ALLE data:
  char buff[STRLEN*2];
  les("Tittel     ", buff, STRLEN); tittel=new char[strlen(buff)+1]; strcpy(tittel,buff);
  les("Beskrivelse", buff, STRLEN); beskr =new char[strlen(buff)+1]; strcpy(beskr,buff);
  les("Extra-matr.", buff, STRLEN); extra =new char[strlen(buff)+1]; strcpy(extra,buff);
  aar = les("Produksjons†r", 1920, 2010);
}


void DVD::les_fra_fil(istream *inn)  {    //  OPPGAVE 2G - Leser ALT fra fil:
  char buff[STRLEN*2];
  *inn >> aar;  inn->ignore();
  inn->getline(buff, STRLEN);   tittel=new char[strlen(buff)+1]; strcpy(tittel,buff);
  inn->getline(buff, STRLEN*2); beskr =new char[strlen(buff)+1]; strcpy(beskr, buff);
  inn->getline(buff, STRLEN*2); extra =new char[strlen(buff)+1]; strcpy(extra, buff);
}


// ******************************  KATEGORI:  ******************************

Kategori::Kategori(char t[])  {           //  OPPGAVE 2B - Initierer ALLE data:
  navn = new char[strlen(t)+1];  strcpy(navn, t);
  dvdene = new List(Sorted);
}


Kategori::~Kategori()     {  delete [] navn;  delete dvdene;  }


void Kategori::skriv()  {                 //  OPPGAVE 2A - Skriver navn og ant:
  cout << '\t' << navn << "   #DVDer: " << dvdene->no_of_elements() << '\n'; 
}


void Kategori::skriv_alt() {              //  OPPGAVE 2A - Skriver ALT:
  skriv(); 
  dvdene->display_list(); 
}


bool Kategori::inneholder(char t[])  {    //  OPPGAVE 2C - Returnerer om noen
  return (dvdene->in_list(t));            //    DVD har 't' som ID:
}


void Kategori::ny(char t[])  {            //  OPPGAVE 2D - Legger inn ny DVD:
  DVD* dvd = new DVD(t);                      //  Lager ny.
  dvd->les_data();                            //  Leser resten av alle datene.
  dvdene->add(dvd);                           //  Legger inn den nye.
}


void Kategori::ny(DVD* d)  {              //  OPPGAVE 2F - Legger inn DVD:
  dvdene->add(d);
}


void Kategori::slett(char t[])  {         //  OPPGAVE 2E - Sletter/fjerner DVD
  dvdene->destroy(t);                     //      med ID lik 't':
}


bool Kategori::tom()  {                   //  OPPGAVE 2F - Returnerer om
  return (dvdene->is_empty());            //      kategori er tom eller ei:
}


DVD* Kategori::hent_forste()  {           //  OPPGAVE 2F - Returnerer med
  return ((DVD*) dvdene->remove_no(1));   //      f›rste DVD i lista:
}


void Kategori::les_fra_fil(istream *inn)  {  //  OPPGAVE 2G - Leser fra fil:
  int ant;                                   //  Antall DVDer i kategorien.
  char titt[STRLEN];                         //  Ny DVDs tittel.
  DVD* dvd;                                  //  Nytt DVD-objekt.

  *inn >> ant;                               //  Leser antall DVD i kategori.
  for (int i = 1;  i <= ant;  i++)  {        //  For hver DVD: 
      *inn >> titt;                          //  Leser tittel (13-sifre).
      dvd = new DVD(titt);                   //  Lager ny DVD.
      dvd->les_fra_fil(inn);                 //  Den leser resten selv fra fil.
      dvdene->add(dvd);                      //  Legger inn ny DVD.
  }
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


void skriv_kategoriene()  {  //  Oppgave 2A - Skriver ALLE kategorienes navn:
  for (int i = 1;  i <= siste_kat;  i++)  {   //  G†r gjennom alle kategorier:
      cout << '\t' << setw(2) << i << ":";    //  Skriver hvers indeks/nummer.
      kategoriene[i]->skriv();                //  Hver skriver resten selv.
  }
}


void skriv_en_kategori()  {  //  Oppgave 2A - Skriver ALT om EN kategori:
  kategoriene[les("Kategorinr", 1, siste_kat)]->skriv_alt();
}


void ny_kategori()  {        //  Oppgave 2B - Legger inn en ny kategori:
  char navn[STRLEN];               //  Ny kategoris navn.
  if (siste_kat < MAXKAT)  {       //  Plass til flere:
     les("Ny kategoris navn", navn, STRLEN);         //  Leser nytt kat.navn.
     kategoriene[++siste_kat] = new Kategori(navn);  //  Legger inn ny kat.
     cout << "\n\tKategorien fikk nr." << siste_kat << '\n';
  } else                           //  IKKE plass til flere:
     cout << "\n\tKartoteket FULLT med " << MAXKAT 
          << " kategorier allerede!\n\n";
}

                             //  Oppgave 2C - Finner (om mulig) og returnerer
int finn_DVD(char t[])  {    //    indeks for kat. der DVD med ID lik 't' er:
  for (int i = 1;  i <= siste_kat;  i++)
      if (kategoriene[i]->inneholder(t)) return i;   //  Funn/treff/match.
  return 0;                  //  Ingen funn/treff/match.
}


void ny_DVD()  {             //  Oppgave 2D - Legger inn ny DVD i kategori:
  int n,                          //  Kategori-nummer om evt. allerede finnes.
      nr;                         //  Kategori-nummer ny DVD ›nskes inn i.
  char nummer[STRLEN/4];          //  (Unikt?) DVD-nummer.

  les("Ny DVDs nr", nummer, STRLEN/4);           //  Leser ny DVDs ID.
  if ((n = finn_DVD(nummer)) == 0)  {            //  Finnes IKKE fra f›r:
     nr = les("Inn i kategorinr", 0, siste_kat); //  Skal inn i kat.nr.'nr'.
     if (nr)  {                                  //  Reelt nummer > 0:
        kategoriene[nr]->ny(nummer);          //  (Lager og) legger inn ny DVD.
        cout << "\n\tNy DVD er lagt inn.\n";
     } else                                      //  Valgte kat.nr.0:
        cout << "\n\tIngen ny DVD lagt inn.\n";
  } else                                         //  DVDs ID finnes allerede:
    cout << "\n\tDette nummeret finnes allerde i kategori nr." << n << ".\n";
}


void slett_DVD()  {          //  Oppgave 2E - Slett/fjern en gitt DVD:
  int n;                          //  Kategori-nummer der DVD evt. er † finne.
  char nummer[STRLEN/4];          //  DVD-nummer som ›nskes slettet/fjernet.

  les("Slett DVD-nr", nummer, STRLEN/4);  //  Leser DVDs ID.
  if ((n = finn_DVD(nummer)) != 0)  {     //  Den er † finne/eksisterer:
     kategoriene[n]->slett(nummer);       //  F†r den slettet/fjernet.
     cout << "\n\tDVD'en er fjernet fra kategori nr." << n << ".\n";
  } else                                  //  DVD finnes ikke:
     cout << "\n\tIngen DVD med dette nummeret.\n";
}

                             //  Oppgave 2F - Sletter en hel kategori, men
void slett_kategori()  {     //    tilbyr brukeren † flytte alle dets DVDer:
  int  n,                    //  Kategori-nummer der flyttes DVD til.
       nr;                   //  Kategori-nummer som ›nskes slettet/fjernet.
  DVD* dvd;                  //  Peker til DVDer som blir flyttet(/slettet).

  nr = les("Slette kategorinr", 0, siste_kat);  //  Leser nr som skal slettes.
  if (nr != 0)  {                               //  Reelt nummer:
     while (!kategoriene[nr]->tom()) {          //  Fortsatt DVDer igjen i kat:
        dvd = kategoriene[nr]->hent_forste();   //  Henter den f›rste.
        dvd->display();                         //  Skriver dets data.
                      // Flytte til kat.nr. evt. 'O' om ›nskes slettet/fjernet:
        n = les("Flyttes til kategorinr (0=slett DVD)", 0, siste_kat);
        if (n)  {                               //  nskes FLYTTET:
           kategoriene[n]->ny(dvd);             //  Flytter.
           cout << "\t\tDVD er flyttet.\n";
        } else  {                               //  nskes SLETTET:
           delete dvd;                          //  Sletter/fjerner.
           cout << "\t\tDVD er slettet/fjernet.\n";
        }
     }                  //  Bakerste/siste kategori flyttes inn i/til "hullet":
     delete kategoriene[nr];                     // Sletter kategorien, flytter
     kategoriene[nr] = kategoriene[siste_kat--]; //   og teller ned antallet.
     cout << "\n\tSiste kategori er flyttet til den slettedes plass/nummer.\n";
  } else                                       //  Nummer==0, dvs. IKKE slette:
    cout << "\n\tIngen kategori ble slettet/fjernet.\n";
}


void les_fra_fil()  {       //  Oppgave 2G - Leser HELE datastrukturen fra fil:
  char buff[STRLEN*2];                  //  Kategoris navn.
  ifstream innfil("DVD.DTA");           //  Filen det leses fra.
  siste_kat = 0;                        //  Nullstiller (for sikkerhets skyld).

  if (innfil)  {                        //  Filen finnes:
     innfil.getline(buff, STRLEN);      //  Henter (om mulig) kategorinavn.
     while (!innfil.eof()  &&  siste_kat < MAXKAT)  {  // Mer igjen og plass:
        kategoriene[++siste_kat] = new Kategori(buff); // Lager/legger inn ny.
        kategoriene[siste_kat]->les_fra_fil(&innfil);  // Leser resten selv.
        innfil.getline(buff, STRLEN);   //  Henter (om mulig) kategorinavn.
     }
  } else
    cout << "\n\tFant ikke filen 'DVD.DTA'!\n";
}

//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J01_2.CPP

//  L›sningsforslag til eksamen i C++, 3.januar 2001, oppgave 2.
//  Laget av Frode Haug, HiG, desember 2000.
//  Litt endret/modifisert av FrodeH, HiG, v†ren 2003.


//  Programmet holder orden p† personer som plukker epler,
//  moreller, solb‘r og jordb‘r p† en og samme g†rd.
//  Man kan:
//     - legge inn en ny plukker
//     - la en plukker slutte, og f† oppgj›r for arbeidet
//     - registrere at en har plukket noen kilo
//     - leser/skriver dataene fra/til fil
//   Dessuten holder programmet orden p† prisen en plukker
//   f†r for † plukke en kilo av en gitt frukt/b‘r.


#include <iostream>             //  cout, cin
#include <fstream>              //  ifstream, ofstream
#include <cstring>              //  strcpy
#include <cctype>               //  toupper
#include "listtool.h"           //  Ulike "verkt›y" fra "Listtool".

using namespace std;
                           //  CONST:
const int ANT_SLAG  =  4;       //  Antall ulike frukt-/b‘rslag.
const int NVNLEN    = 30;       //  Max.lengde for personnavn.

			   //  GLOBALE VARIABLE (1):
int nummer;                     //  Holder orden p† siste plukkers unike nummer.

                           //  KLASSER:
                           //  OPPGAVE 2A
class Kilopris  {               //  Data om de ulike slagenes kilopris.
  private:
    float pris[ANT_SLAG];       //  Array med prisene en plukker f†r pr.kilo
  public:                       //    hun/han plukker av vedkommende frukt/b‘r.
    Kilopris()  {               //  Constructor som leser kilopriser 
      ifstream innfil("kilopris.dta");      //  inn fra fil:
      int i;
      if (innfil)
         for (i = 0;  i < ANT_SLAG;  i++)   //  Leser 'ANT_SLAG' priser:
             innfil >> pris[i];
      else  cout << "\n\nFEIL - Fant ikke filen 'KILOPRIS.DTA'";
    }
    float hent(char slag)  {    //  Funksjon som returnerer en kilopris,
      switch (slag)  {          //    ut fra en gitt bokstav:
        case 'E':  return pris[0];
        case 'M':  return pris[1];
        case 'S':  return pris[2];
        case 'J':  return pris[3];
        default:  cout << "\n\nFEIL - Ulovlig b‘r-/frukttype!"; return 0;
      }
    }
};

                                //  En plukker med unik nummer-ID:
class Plukker : public Num_element  {
  private:                      //  NB: Har ogs† arvet "number" !
    char navn[NVNLEN];          //  Navnet.
    int  ant_kilo;              //  Plukket antall kilo frukt/b‘r.
    char slag;                  //  Slag av frukt/b‘r som vedkommende plukker
                                //     (kan kun v‘re 'E', 'M', 'S' eller 'J').
  public:                       //  Constructor nr.1:
    Plukker(char* nvn, char s) : Num_element(0)  {
      number = ++nummer;  ant_kilo = 0;  strcpy(navn, nvn);  slag = s;
    }                           //  Constructor nr.2:
    Plukker(istream* inn, int nr) : Num_element(nr)  {
      (*inn).get(navn, 3);   (*inn).get(navn, NVNLEN);   //  Leser resten inn
      *inn >> ant_kilo >> slag;                          //    fra fil.
    }
    int  hent_nr()    {  return number;    }             //  Returnerer ulike
    int  hent_kilo()  {  return ant_kilo;  }             //    datamedlemmer.
    char hent_slag()  {  return slag;      }             //  Viser dataene:
    void display()    {  cout << "\n\t" << number << ": " << navn
                              << " har plukket " << ant_kilo 
                              << " kilo av typen " << slag; }
    void skriv_til_fil(ostream* ut)  {                   //  Skriver alle
      *ut << number << "  " << navn << '\n'              //    dataene til fil:
          << ant_kilo << "  " << slag << '\n';
    }
    void operator += (int n)  {  ant_kilo += n;  }       //  ker 'ant_kilo'.
};

			   //  GLOBALE VARIABLE (2):
List*     plukkere;             //  Listen (sortert p† nummer) av plukkere.
Kilopris* pris;                 //  ETT objekt med alle kiloprisene.


void skriv_meny();         //  DEKLARASJON AV FUNKSJONER:
char les();
void ny_plukker();
void plukker_slutter();
void plukket_kilo();
void les_fra_fil();
void skriv_til_fil();


int main()  {              //  HOVEDPROGRAMMET:
  char kommando;

  pris = new Kilopris;                             //  Oppgave 2a
  plukkere = new List(Sorted);
  les_fra_fil();                                   //  Oppgave 2e
  skriv_meny();

  kommando = les();
  while (kommando != 'Q')  {
    switch(kommando)  {
      case 'N': ny_plukker();              break;  //  Oppgave 2b
      case 'S': plukker_slutter();         break;  //  Oppgave 2c
      case 'P': plukket_kilo();            break;  //  Oppgave 2d
      case 'F': skriv_til_fil();           break;  //  Oppgave 2f
      case 'D': plukkere->display_list();  break;
      default:  skriv_meny();              break;
    }
    kommando = les();
  }
  return 0;
}

			   //  DEFINISJON AV FUNKSJONER:
void skriv_meny()  {            //  Skriver brukerens meny/valg:
  cout << "\n\nF›lgende kommandoer er lovlig:";
  cout << "\n\tN  - Ny plukker ankommer.";
  cout << "\n\tS  - plukker Slutter.";
  cout << "\n\tP  - Plukket N nye kilo.";
  cout << "\n\tF  - skriv data til Fil.";
  cout << "\n\tD  - Display listen av plukkere.";
  cout << "\n\tQ  - Quit / avslutt";
}


char les()  {                   //  Leser og returnerer ETT upcaset tegn.
  char ch;
  cout << "\n\nKommando:  ";   cin >> ch;   cin.ignore();
  return (toupper(ch));
}

                             //  OPPGAVE 2B
void ny_plukker()  {            //  Ny plukker starter † arbeide.
  Plukker* ny;                  //  Peker til nyopprettet plukker.
  char navn[NVNLEN];            //  Ny plukkers navn.
  char type;                    //  Slag/type frukt/b‘r hun/han skal plukke.

  cout << "\n\tNy plukkers navn: ";
  cin.getline(navn, NVNLEN);    //  Leser ny plukkers navn.
  do  {                         //  Leser lovlig slag/type som skal plukkes:
    cout << "\tSkal plukke (E, M, S, J): ";
    cin >> type;  cin.ignore();   type = toupper(type);
  } while (type != 'E'  &&  type != 'M'  &&  type != 'S'  &&  type != 'J');
  ny = new Plukker(navn, type); //  Oppretter nytt plukker-objekt.
  cout << "\n\n\tPlukkeren har f†tt nr: " << ny->hent_nr();  // Avleser ID.
  plukkere->add(ny);            //  Legger inn i listen.
}

                             //  OPPGAVE 2C
void plukker_slutter()  {       //  En plukker slutter arbeidet sitt helt.
  int nr;                       //  Plukkerens nummer/ID.
  Plukker* plukker;             //  Plukker-objektet.

  cout << "\n\tAngi plukkers nummer: ";    //  Leser unikt nummer.
  cin >> nr;  cin.ignore();                //  Pr›ver † finne vedkommende:
  if ((plukker = (Plukker*) plukkere->remove(nr))) {   // Ble funnet:
     plukker->display();                   //  Skriver plukkers data.
     cout << "\n\tUtbetaling: "            //  Regner ut utbetalingen:
          << plukker->hent_kilo() * pris->hent(plukker->hent_slag()) 
          << " kroner.";
     delete plukker;                       //  Sletter plukker-objektet.
     cout << "\n\tPlukkeren er n† slettet fra systemet.";
  } else cout << "\tIngen plukker har dette nummeret!";
}

                             //  OPPGAVE 2D
void plukket_kilo()  {          //  Har plukket N ny kilo med frukt/b‘r.
  int nr;                       //  Plukkerens nummer/ID.
  int  kilo;                    //  Antall kilo plukket.
  Plukker* plukker;             //  Plukker-objektet.

  cout << "\n\tAngi plukkers nummer: ";    //  Leser unikt nummer.
  cin >> nr;  cin.ignore();                //  Pr›ver † finne vedkommende:
  if ((plukker = (Plukker*) plukkere->remove(nr))) {   // Ble funnet:
     plukker->display();                   //  Skriver plukkers data.
     do  {                                 //  Leser et LOVLIG antall kilo:
       cout << "\n\tAntall kilo plukket: ";
       cin >> kilo;  cin.ignore();
     } while (kilo < 0  ||  kilo > 100);   //  Kiloene registreres/legges                            
     *plukker += kilo;                     //    til hos vedkommende.
     plukker->display();                   //  Skriver plukkers data IGJEN.
     plukkere->add(plukker);               //  Legger tilbake i listen.
  } else cout << "\tIngen plukker har dette nummeret!";
}

                             //  OPPGAVE 2E
void les_fra_fil()  {           //  Leser data om alle plukkerne fra fil.
  ifstream innfil("plukkere.dta");
  Plukker* ny;                  //  Peker til nyopprettet plukker.
  int nr;                       //  Plukkerens nummer/ID.
  if (innfil)  {                //  Filen finnes:
     innfil >> nr;              //  Pr›ver † lese neste nummer/ID.
     while (!innfil.eof()) {    //  Enn† ikke slutt p† filen:
       ny = new Plukker(&innfil, nr);  //  Ber objektet selv lese resten.
       plukkere->add(ny);       //  Legger ny plukker inn i listen.
       innfil >> nr;            //  Pr›ver † lese neste nummer/ID.
     }                          //  Oppdaterer den globale "nummer" med det
     nummer = nr;               //    siste innleste nummer for en plukker.
     cout << "\n\nHar lest data fra filen 'PLUKKERE.DTA'.";
  } else
    cout << "\n\nFEIL - Fant ikke filen 'PLUKKERE.DTA'!\n\n";
}

                             //  OPPGAVE 2F
void skriv_til_fil()  {         //  Skriver alle plukkerne til fil.
  ofstream innfil("plukkere.dta");
  Plukker* plukker;             //  Plukker-objektet.
  int i, ant = plukkere->no_of_elements();        //  Antall plukkere i liten.

  for (i = 1;  i <= ant;  i++)  {                 //  G†r gjennom hele listen:
    plukker = (Plukker*) plukkere->remove_no(i);  //  Tar ut plukker nr.i. 
    plukker->skriv_til_fil(&innfil);          //  Objektet skriver resten selv.
    plukkere->add(plukker);                       //  Legger tilbake i listen.
  }
  cout << "\n\n\tHar skrevet data til filen 'PLUKKERE.DTA'.";
}

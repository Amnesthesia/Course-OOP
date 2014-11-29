//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_J01_2.TPL

//  Litt endret/modifisert av FrodeH, HiG, v†ren 2003

#include <iostream>             //  cout, cin
#include <fstream>              //  ifstream, ofstream
#include <cctype>               //  toupper
#include "listtool.h"           //  Ulike "verkt›y" fra "Listtool".

using namespace std;
                           //  CONST:
const int ANT_SLAG  =  4;       //  Antall ulike frukt-/b‘rslag.
const int NVNLEN    = 30;       //  Max.lengde for personnavn.

			   //  GLOBALE VARIABLE (1):
int nummer;                     //  Holder orden p† siste plukkers unike nummer.

                           //  KLASSER:
class Kilopris  {               //  Data om de ulike slagenes kilopris.
  private:
    float pris[ANT_SLAG];       //  Array med prisene en plukker f†r pr.kilo

  public:                       //    hun/han plukker av vedkommende frukt/b‘r.
    Kilopris()  {             //  Constructor som leser kilopriser inn fra fil:
//   OPPGAVE 2A: Skriv innmaten
    }
               //  Funksjon som returnerer en kilopris, ut fra en gitt bokstav:
    float hent(char slag)  {   
//   OPPGAVE 2A: Skriv innmaten
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
//  Ut fra oppgavene 2b-2f m† det her lages flere funksjoner.
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


void ny_plukker()  {

//   OPPGAVE 2B: Skriv innmaten
}


void plukker_slutter()  {

//   OPPGAVE 2C: Skriv innmaten
}


void plukket_kilo()  {

//   OPPGAVE 2D: Skriv innmaten
}


void les_fra_fil()  {

//   OPPGAVE 2E: Skriv innmaten
}


void skriv_til_fil()  {

//   OPPGAVE 2F: Skriv innmaten
}

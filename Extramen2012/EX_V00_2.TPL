//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_V00_2.TPL

//  Litt endret/modifisert av FrodeH, HiG, v†ren 2003


#include <fstream>         //  ifstream
#include <iostream>        //  cout, cin
#include <cctype>          //  toupper
#include <cstring>         //  strcmp
#include "listtool.h"      //  Ulike "verkt›y" fra "Listtool".

using namespace std;
			   //  CONST:
const int ANT_KAIPLASSER = 20;    //  Max. antall kaiplasser p† havnen.
const int IDNR_LEN       = 11;    //  Lengde for container id (inkl.'\0').
const int FILNAVN_LEN    = 13;    //  Max. lengde p† filnavn (inkl.'\0').


                           //  KLASSE:

//   Oppgave 2a:  Deklarer aktuell(e) klasse(r) med heading (arv),
//                datamedlemmer, constructor og display-funksjon.


			   //  GLOBALE VARIABLE:
List* ankomst;                 //  Listen av containere som kun er avlesset.
List* farlig;                  //  Listen av containere med farlig innhold.
List* kjol;                    //  Listen av containere med kj›rlig innhold.
List* andre;                   //  Listen av containere med alt annet innhold.
List* kaiplass[ANT_KAIPLASSER+1];    //  Lister av containere som er p† 
                                     //    (vei til) kaiplass nr.'i'.


void skriv_meny();         //  DEKLARASJON AV FUNKSJONER:
char les();
void initier_lister();
void avlessing();
void omlasting();
void utskiping();
void baatavgang();
void finn();


int main()  {             //  HOVEDPROGRAMMET:
  char kommando;

  initier_lister();                           //  Oppgave 2a
  skriv_meny();

  kommando = les();
  while (kommando != 'Q')  {
    switch(kommando)  {
      case 'A': avlessing();       break;     //  Oppgave 2b
      case 'O': omlasting();       break;     //  Oppgave 2c
      case 'U': utskiping();       break;     //  Oppgave 2d
      case 'B': baatavgang();      break;     //  Oppgave 2e
      case 'F': finn();            break;     //  Oppgave 2f 
      default:  skriv_meny();      break;
    }
    kommando = les();
  }
  return 0;
}

			   //  DEFINISJON AV FUNKSJONER:
void skriv_meny()  {
  cout << "\n\n\n\nF›lgende kommandoer er lovlig:";
  cout << "\n\tA <idnr> <kat> <vekt> - Avlessing fra en semi-trailer.";
  cout << "\n\tO                     - Omlasting til annet passende omr†de.";
  cout << "\n\tU <plassnr> <filnavn> - Utskiping fra omr†de til en kaiplass/b†t.";
  cout << "\n\tB <plassnr>           - B†t forlater kaiplass/havnen.";
  cout << "\n\tF <idnr>              - Finn hvilken liste en gitt container er i.";
  cout << "\n\tQ                     - Quit / avslutt";
}


char les()  {                     //  Leser og returnerer ETT upcaset tegn.
  char ch;
  cout << "\n\nKommando:  ";
  cin >> ch;   cin.ignore();
  return (toupper(ch));
}


void initier_lister()  {          //  Oppretter/lager tomme lister.

//   Oppgave 2a:  Skriv innmaten
}


void avlessing()  {               //  Ny container plasseres i ankomst-omr†det.

//   Oppgave 2b:  Skriv innmaten
}


void omlasting()  {               //  Container omflyttes til aktuelt omr†de.

//   Oppgave 2c:  Skriv innmaten
}


void utskiping()  {               //  Containere innsamles til kaiplass/b†t.

//   Oppgave 2d:  Skriv innmaten
}


void baatavgang()  {              //  B†t forlater havneomr†det.

//   Oppgave 2e:  Skriv innmaten
}


void finn()  {                    //  Finn en gitt container p† HELE omr†det.

//   Oppgave 2f:  Skriv innmaten
}

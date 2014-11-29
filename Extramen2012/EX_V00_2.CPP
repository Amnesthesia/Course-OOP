//  Fil:  FRODEH \ OO \ EXTRAMEN \ EX_V00_2.CPP

//  L›sningsforslag til eksamen i C++, 25.mai 2000, oppgave 2.
//  Laget av Frode Haug, HiG, mai 2000.
//  Litt endret/modifisert av FrodeH, HiG, v†ren 2003


//  Programmet registrerer nye ankomne containere p† et havneanlegg ('A').
//  Ut fra typen gods i hver container, s† flyttes ('O') deretter hver
//  container til ulike omr†der p† anlegget: Farlig, Kj›l og Andre.
//  N†r en b†t ankommer p† en kaiplass, og skal laste, s† samles ('U')
//  containere sammen fra de ulike omr†dene og bringes til aktuell kaiplass/b†t.
//  N†r b†ten drar med lasten/containere, s† slettes de fra systemet ('B').
//  Det g†r ogs† an † lete etter en gitt container p† havneanlegget ('F').


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


			   //  KLASSE:       //  OPPGAVE 2A
class Container : public Text_element  {     // Klassen 'Container':
  private:                        //  Arver "text".
    char kategori;                //  Kategori ('F', 'K', 'A').
    float vekt;                   //  Vekt (i kilo).

  public:
    Container(char* t, char kat, float v): Text_element(t) 
      {  kategori = kat;  vekt = v;  }       //  Constructor.

    void display()                           //  Viser objektets data.
      {  cout << "\n\t" << text << "  " << kategori << "  "  << vekt;  }

    char hent_kategori()                     //  Returnerer objektets kategori.
      {  return kategori;  }

    int operator == (char* t)                //  Returnerer '1' dersom ER like,
      {  return (!strcmp(text, t));  }       //    '0' returneres ellers.
};


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
void display_liste();


int main()  {              //  HOVEDPROGRAMMET:
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
      case 'D': display_liste();   break;     //  SKAL IKKE LAGES !
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
  cout << "\n\tD <1-24>              - Display/vis en listes innhold.";
  cout << "\n\tQ                     - Quit / avslutt";
}


char les()  {                     //  Leser og returnerer ETT upcaset tegn.
  char ch;
  cout << "\n\nKommando:  ";
  cin >> ch;   cin.ignore();
  return (toupper(ch));
}


void initier_lister()  {          //  OPPGAVE 2A
  ankomst  = new List(FIFO);                  //  Oppretter fire tomme separate
  farlig   = new List(Sorted);                //    lister og 20 andre, en for
  kjol     = new List(Sorted);                //    hver kaiplass/b†t.
  andre    = new List(Sorted);
  for (int i = 1;  i <= ANT_KAIPLASSER;  i++)
      kaiplass[i] = new List(LIFO);
}


void avlessing()  {               //  OPPGAVE 2B
  char  idnr[IDNR_LEN];                       // Containers id/nummer.
  char  kat;                                  // Containers kategori.
  float vekt;                                 // Containers vekt.
  Container* container;                       // Peker til nytt objekt.

  cin >> idnr >> kat >> vekt;     //  Leser inn tre KORREKTE (?) parametre.
  kat = toupper(kat);             //  Gj›r om til stor bokstav.
  container = new Container(idnr, kat, vekt); //  Oppretter nytt objekt.
  ankomst->add(container);                    //  Legger inn i listen. 
  cout << "\n\tNy container p† ANKOMST-omr†det.";
}


void omlasting()  {               //  OPPGAVE 2C
  Container* container;                       //  Peker til objekt som flyttes.
  char kat;
  if (!ankomst->is_empty())  {                //  Det ER noen i ankomst-k›en:
     container = (Container*) ankomst->remove();   //  Tar ut den forreste.
     kat = container->hent_kategori();             //  Avleser dens kategori.
     switch (kat)  {
       case 'F':  farlig->add(container);
                  cout << "\n\tContainer flyttes fra ANKOMST- til FARLIG-omr†det.";
                  break;
       case 'K':  kjol->add(container);    
                  cout << "\n\tContainer flyttes fra ANKOMST- til KJLE-omr†det.";
                  break;
       case 'A':  andre->add(container);   
                  cout << "\n\tContainer flyttes fra ANKOMST- til ANDRE-omr†det.";
                  break;
       default:   andre->add(container);   
                  cout << "\n\tContainer flyttes fra ANKOMST- til ANDRE-omr†det,"
                       << "\n\tselv om kategori-bokstaven (=" 
                       << kat << ") var FEIL !";
                  break;
     }
  } else                                      //  Ankomst-k›en er tom:
    cout << "\n\tANKOMST-omr†det er TOMT, ingenting † omlaste.";
}


void utskiping()  {               //  OPPGAVE 2D
  int  plassnr;                        //  Kaiplassnummer som skal brukes.
  char filnavn[FILNAVN_LEN];           //  Aktuell fil det skal leses fra.
  char idnr[IDNR_LEN];                 //  Containers id/nummer (fra fil).
  Container* container;                //  Peker til objektet som flyttes.

  cin >> plassnr >> filnavn;           //  Leser to stk. parametre.

  if (plassnr >= 1  &&  plassnr <= ANT_KAIPLASSER)  {   //  Lovlig kaiplass:
     ifstream innfil(filnavn);         //  Pr›ver † †pne fil.
     if (innfil)  {                    //  Filen ble funnet:
        innfil >> idnr;
        while (!innfil.eof())  {
          if ((container = (Container*) farlig->remove(idnr)))
             kaiplass[plassnr]->add(container);
          else if ((container = (Container*) kjol->remove(idnr)))
             kaiplass[plassnr]->add(container);
          else if ((container = (Container*) andre->remove(idnr)))
             kaiplass[plassnr]->add(container);
          else
             cout << "\n\tIngen container p† de tre omr†dene med id lik: "
                  << idnr;
          innfil >> idnr;
        }
     } else
       cout << "\n\tFinner ikke noen fil med navnet: " << filnavn;
  } else
    cout << "\n\t'Plassnr' utenfor intervallet 1-" << ANT_KAIPLASSER << " !";
}


void baatavgang()  {              //  OPPGAVE 2E
  int plassnr;                         //  Kaiplassnummer som blir ledig.
  cin >> plassnr;                      
  if (plassnr >= 1  &&  plassnr <= ANT_KAIPLASSER)  {  // Nr. i rett intervall.
     if (!kaiplass[plassnr]->is_empty())  {            // Noe p† kaiplassen:
        delete kaiplass[plassnr];                      // Sletter aktuell liste.
        kaiplass[plassnr] = new List(LIFO);            // Oppretter ny tom liste.
        cout << "\n\tPlassen er frigitt/nullstilt.";
     } else
       cout << "\n\tKaiplassen er allerede TOM !  Har du tastet feil nummer ?";
  } else                               //  Nr. utenfor lovlig intervall:
    cout << "\n\t'Plassnr' utenfor intervallet 1-" << ANT_KAIPLASSER << " !";
}


void finn()  {                    //  OPPGAVE 2F
  char  idnr[IDNR_LEN];               //  Containers id/nummer.
  int ant, i;                         //  Antall objekter i ANKOMST-listen.
  bool finnes = false;                //  Om funnet containeren eller ei.
  Container* container;               //  Peker til objektet som inspiseres.

  cin >> idnr;                        //  Leser aktuelt containernummer.

  if ((finnes = farlig->in_list(idnr)))                        //  Finner den
     cout << "\n\tContainer befinner seg p† FARLIG-omr†det.";  //   p† en av
  else if ((finnes = kjol->in_list(idnr)))                     //   de aktuelle
     cout << "\n\tContainer befinner seg p† KJLE-omr†det.";   //   omr†dene:
  else if ((finnes = andre->in_list(idnr)))
     cout << "\n\tContainer befinner seg p† ANDRE-omr†det.";
  else  {                         // Den KAN fortsatt v‘re p† ANKOMST-omr†det
                                  //   (eller p† en av de 20 kaiplassene):
     ant = ankomst->no_of_elements();                    //  Eller at den er p†
     for (i = 1;  i <= ant;  i++)  {                     //    ANKOMST-omr†det.
         container = (Container*) ankomst->remove();
         if (*container == idnr)  {
            finnes = true;
            cout << "\n\tContainer befinner seg p† ANKOMST-omr†det.";
         }
         ankomst->add(container);
     }
  }
  if (!finnes)
     cout << "\n\tFant ikke containeren, men den KAN v‘re p† en av kaiplassene.";

//  Det er mer tuklete † finne et gitt element p† kaiplassene (LIFO-lister).
//  Dette skyldes at hverken 'remove_no' eller 'in_list' er tilgjengelig.
//  Ei heller vil 'display_element' gi ›nsket effekt (v‘re korrekt † tilkalle).
//  Vi kan heller ikke benytte teknikken ovenfor med † sirkulere listen,
//  da 'add' alltid bare legger inn igjen forrest i listen.

//  L›sningen m†tte v‘re † ta ut ett og ett element og legge det over i
//  en annen LIFO-liste. Deretter flytter man dem alle tilbake igjen til
//  den opprinnelige listen, samtidig som man sammenligner dens id med
//  "idnr" (vha. den overloadede funkjonen "==").
}


void display_liste()  {           //  Viser innoldet i ulike listene:
  int n;
  cin >> n;                                           // Leser aktuelt listenr.
  switch(n)  {
    case 21:  ankomst->display_list();       break;   //  Viser innholdet i
    case 22:  farlig->display_list();        break;   //    de fire separate
    case 23:  kjol->display_list();          break;   //    listene:
    case 24:  andre->display_list();         break;
    default: if (n >= 1  &&  n <= ANT_KAIPLASSER)     //  ALLE andre verdier:
                kaiplass[n]->display_list();
             else
               cout << "\n\tNummer M v‘re i intervallet 1-24 !";  break;
  }
}

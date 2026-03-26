#include <iostream>
#include <string>
using namespace std;

void dodajOsobe(string nazwiska[], string nazwisko) {
    for(int i = 0; i < 10; i++) {
        if(nazwiska[i] == "") {
            nazwiska[i] = nazwisko;
            break;
        }
    }
    return;
}

void ustawObecnosc(string nazwiska[], bool obecnosci[], int indeks, bool obecnosc) {
    if (nazwiska[indeks] != "") {
        obecnosci[indeks] = obecnosc;
    }
    return;
}

void wyswietl(string nazwiska[], bool obecnosci[]) {
    for(int i = 0; i < 10; i++) {
        if(nazwiska[i] == "") break;
        cout << "Indeks\tNazwisko\tObecnosc\n"
             << i <<".\t" << nazwiska[i] << "\t" << obecnosci[i] << "\n";
    }
    return;
}

int main() {
    string tabNazwiska[10];
    bool tabObecnosc[10];
    int opcja;

    do {
        cout << "\nT A B E L A   O B E C N O S C I\n"
            << "1. Wyswietl\n"
            << "2. Dodaj osobe\n"
            << "3. Dodaj obecnosc\n"
            << "0. Wyjdz\n";

            cin >> opcja;

        
            if (opcja == 1){
                wyswietl(tabNazwiska, tabObecnosc);
            }
            else if (opcja == 2) {
                string nazwisko;

                cout << "Podaj nazwisko: ";
                cin >> nazwisko;

                dodajOsobe(tabNazwiska, nazwisko);
            }
            else if (opcja == 3) {
                int indeks;
                bool obecnosc;

                cout << "Podaj indeks osoby (0-9): ";
                cin >> indeks;
                cout << "Podaj obecnosc (0/1): ";
                cin >> obecnosc;

                ustawObecnosc(tabNazwiska, tabObecnosc, indeks, obecnosc);
            }
            else {
                cout << "Wybierz odpowiednia opcje!";
            }
         } while (opcja != 0);

    return 0;
}

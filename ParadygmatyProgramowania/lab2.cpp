#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class Osoba {
    private:
    int indeks;
    string imie;
    string nazwisko;
    bool obecnosc;

    public:

    Osoba() {
        indeks = 0;
        imie = "";
        nazwisko = "";
        obecnosc = false;
    }

    void setImie(string wartosc) {

    }
};

void dodajOsobe(Osoba &os, int indeks, string imie, string nazwisko) {
    for(int i = 0; i < MAX; i++) {
        if(os.nazwisko == "") {
            os.imie = imie;
            os.nazwisko = nazwisko;
            os.indeks = indeks;
            os.obecnosc = false;
            break;
        }
    }
    return;
}

void ustawObecnosc(Osoba &os, int i, bool obecnosc) {
    if (i >= 0 && i < MAX && os.nazwisko != "") {
        os.obecnosc = obecnosc;
    }
    return;
}

void edytujOsobe(
    Osoba &os, 
    int i, string imie, string nazwisko, int indeks
) {
    if(imie != "") os.imie = imie;
    if(nazwisko != "") os.nazwisko = nazwisko;
    if(indeks != -1) os.indeks = indeks;
    return;
}

void usunOsobe(*tabOsob, int i) {
    for(int j = i; j < MAX-1; j++) {
        tabOsob[j].imie = tabOsob[j+1].imie;
        tabOsob[j].nazwisko = tabOsob[j+1].nazwisko;
        tabOsob[j].indeks = tabOsob[j+1].indeks;
        tabOsob[j].obecnosc = tabOsob[j+1].obecnosc;
    }

    tabOsob[MAX-1].imie = "";
    tabOsob[MAX-1].nazwisko = "";
    tabOsob[MAX-1].indeks = 0;
    tabOsob[MAX-1].obecnosc = false;
    return;
}

void wyswietl(Osoba &os) {
    cout << "Nr.\tIndeks\tImie\tNazwisko\tObecnosc\n";

    for(int i = 0; i < MAX; i++) {
        if(os.nazwisko == "") break;
        cout << i << ".\t"
             << os.indeks << "\t"
             << os.imie << "\t" 
             << os.nazwisko << "\t" 
             << os.obecnosc << "\n";
    }
    return;
}

int main() {
    Osoba tabOsob[MAX];

    int opcja;

    do {
        cout << "\nT A B E L A   O B E C N O S C I\n"
            << "1. Wyswietl\n"
            << "2. Dodaj osobe\n"
            << "3. Ustaw obecnosc\n"
            << "4. Edytuj osobe\n"
            << "5. Usun osobe\n"
            << "0. Wyjdz\n";

            cin >> opcja;
        
            if(opcja == 1){
                wyswietl(tabOsob[i]);
            }
            else if(opcja == 2) {
                int indeks;
                string imie, nazwisko;
                cout << "Podaj indeks: ";
                cin >> indeks;

                cout << "Podaj imie: ";
                cin >> imie;

                cout << "Podaj nazwisko: ";
                cin >> nazwisko;

                dodajOsobe(
                    tabOsob[i],
                    indeks,
                    imie,
                    nazwisko
                );
            }
            else if(opcja == 3) {
                int i;
                bool obecnosc;

                cout << "Podaj nr. osoby (0-9): ";
                cin >> i;
                cout << "Podaj obecnosc (0/1): ";
                cin >> obecnosc;

                ustawObecnosc(tabOsob[i], i, obecnosc);
            }
            else if(opcja == 4) {
                int i;
                int indeks = -1;
                string imie, nazwisko, indeksStr;

                cout << "Podaj nr osoby (0-9): ";
                cin >> i;
                cin.ignore();

                cout << "Nowy indeks (puste pole = bez zmian): ";
                getline(cin, indeksStr);

                if(indeksStr != "") indeks = stoi(indeksStr);

                cout << "Nowe imie (puste pole = bez zmian): ";
                getline(cin, imie);

                cout << "Nowe nazwisko (puste pole = bez zmian): ";
                getline(cin, nazwisko);

                edytujOsobe(
                    tabOsob[i],
                    i,
                    imie,
                    nazwisko,
                    indeks
                );
            }
            else if(opcja == 5) {
                int i;

                cout << "Podaj nr osoby do usuniecia: ";
                cin >> i;

                usunOsobe(tabOsob[i], i);
            }
            else {
                cout << "Wybierz odpowiednia opcje!";
            }
         } while (opcja != 0);

    return 0;
}


// mamy wskaźniki do obiektów, żeby się nie duplikowały
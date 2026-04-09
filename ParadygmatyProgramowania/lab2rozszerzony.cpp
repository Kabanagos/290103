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
    }

    int setImie(string wartosc) {
        if(wartosc.length() < 2) 
            return -1;

        imie = wartosc;
        return 0;
    }

    int setNazwisko(string wartosc) {
        if(wartosc.length() < 2) 
            return -1;

        nazwisko = wartosc;
        return 0;
    }

    void setIndeks(int wartosc) {
        indeks = wartosc;
    }

    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    int getIndeks() { return indeks; }
};

void dodajOsobe(
    Osoba *tabOsob[],
    bool obecnosc[],
    int indeks, 
    string imie, 
    string nazwisko
) {
    for(int i = 0; i < MAX; i++) {
        if(tabOsob[i] == nullptr) {
            tabOsob[i] = new Osoba;

            tabOsob[i]->setImie(imie);
            tabOsob[i]->setNazwisko(nazwisko);
            tabOsob[i]->setIndeks(indeks);

            obecnosc[i] = false;

            break;
        }
    }
}

void ustawObecnosc(bool obecnosc[], int i, bool wartosc) {
    if (i >= 0 && i < MAX) {
        obecnosc[i] = wartosc;
    }
}

void edytujOsobe(
    Osoba *tabOsob[], 
    int i, 
    string imie, 
    string nazwisko, 
    int indeks
) {
    if(tabOsob[i] == nullptr)
        return;

    if(imie != "")
        tabOsob[i]->setImie(imie);

    if(nazwisko != "")
        tabOsob[i]->setNazwisko(nazwisko);

    if(indeks != -1)
        tabOsob[i]->setIndeks(indeks);
}

void usunOsobe(
    Osoba *tabOsob[],
    bool obecnosc[],
    int i
) {
    if(tabOsob[i] == nullptr)
        return;

    delete tabOsob[i];

    for(int j = i; j < MAX - 1; j++) {
        tabOsob[j] = tabOsob[j+1];
        obecnosc[j] = obecnosc[j+1];
    }

    tabOsob[MAX-1] = nullptr;
    obecnosc[MAX-1] = false;
}

void wyswietl(
    Osoba *tabOsob[],
    bool obecnosc[]
) {
    cout << "Nr.\tIndeks\tImie\tNazwisko\tObecnosc\n";

    for(int i = 0; i < MAX; i++) {
        if(tabOsob[i] == nullptr)
            continue;

        cout << i << ".\t"
             << tabOsob[i]->getIndeks() << "\t"
             << tabOsob[i]->getImie() << "\t"
             << tabOsob[i]->getNazwisko() << "\t"
             << obecnosc[i] << "\n";
    }
}

int main() {
    Osoba *tabOsob[MAX];
    bool tabObecnosc[MAX];

    for(int i = 0; i < MAX; i++) {
        tabOsob[i] = nullptr;
        tabObecnosc[i] = false;
    }

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
                wyswietl(tabOsob, tabObecnosc);
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
                    tabOsob,
                    tabObecnosc,
                    indeks,
                    imie,
                    nazwisko
                );
            }
            else if(opcja == 3) {
                int i;
                bool wartoscObec;

                cout << "Podaj nr. osoby (0-9): ";
                cin >> i;
                cout << "Podaj obecnosc (0/1): ";
                cin >> wartoscObec;

                ustawObecnosc(tabObecnosc, i, wartoscObec);
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

                if(indeksStr != "") 
                    indeks = stoi(indeksStr);

                cout << "Nowe imie (puste pole = bez zmian): ";
                getline(cin, imie);

                cout << "Nowe nazwisko (puste pole = bez zmian): ";
                getline(cin, nazwisko);

                edytujOsobe(
                    tabOsob,
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

                usunOsobe(
                    tabOsob, 
                    tabObecnosc,
                    i
                );
            }
            else {
                cout << "Wybierz odpowiednia opcje!";
            }
         } while (opcja != 0);
    
    for(int i = 0; i < MAX; i++) {
        delete tabOsob[i];
    }

    return 0;
}

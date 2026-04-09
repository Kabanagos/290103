#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;
const int iloscList = 2;

 // lista obecności zawiera w sobie odwołania do osób
 // lista obecności nie jest szczególnym przypadkiem osoby

class Osoba {
private:
    int indeks;
    string imie;
    string nazwisko;

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


class listaObecnosci {
private:
    Osoba **tabOsob;
    bool *tabObecnosc;
    int rozmiar;

public:
    listaObecnosci(int max = MAX);

    void dodajOsobe(int indeks, string imie, string nazwisko);
    void ustawObecnosc(int i, bool wartosc);
    void usunOsobe(int i);
    void wyswietl();

    Osoba* getOsoba(int i);
    ~listaObecnosci();
};

listaObecnosci::listaObecnosci(int max) {
    rozmiar = max;

    tabOsob = new Osoba*[rozmiar];
    tabObecnosc = new bool[rozmiar];

    for(int i = 0; i < rozmiar; i++) {
        tabOsob[i] = nullptr;
        tabObecnosc[i] = false;
    }
}

void listaObecnosci::dodajOsobe(
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

            tabObecnosc[i] = false;

            break;
        }
    }
}

void listaObecnosci::ustawObecnosc(int i, bool wartosc) {
    if (i >= 0 && i < MAX) {
        tabObecnosc[i] = wartosc;
    }
}

void listaObecnosci::wyswietl() {
    cout << "Nr.\tIndeks\tImie\tNazwisko\tObecnosc\n";

    for(int i = 0; i < MAX; i++) {
        if(tabOsob[i] == nullptr)
            continue;

        cout << i << ".\t"
             << tabOsob[i]->getIndeks() << "\t"
             << tabOsob[i]->getImie() << "\t"
             << tabOsob[i]->getNazwisko() << "\t"
             << tabObecnosc[i] << "\n";
    }
}

Osoba* listaObecnosci::getOsoba(int i) {
    if (i < 0 || i >= rozmiar)
        return nullptr;

    return tabOsob[i];
}

listaObecnosci::~listaObecnosci() {
    for(int i = 0; i < MAX; i++) {
        delete tabOsob[i];
    }

    delete[] tabObecnosc;
    delete[] tabOsob;
}

void edytujOsobe(
    Osoba *os, 
    string imie, 
    string nazwisko, 
    int indeks
) {
    if(os == nullptr)
        return;

    if(imie != "")
        os->setImie(imie);

    if(nazwisko != "")
        os->setNazwisko(nazwisko);

    if(indeks != -1)
        os->setIndeks(indeks);
}

void listaObecnosci::usunOsobe(int i) {
    if(tabOsob[i] == nullptr)
        return;

    delete tabOsob[i];

    for(int j = i; j < MAX - 1; j++) {
        tabOsob[j] = tabOsob[j+1];
        tabObecnosc[j] = tabObecnosc[j+1];
    }

    tabOsob[MAX-1] = nullptr;
    tabObecnosc[MAX-1] = false;
}

int main() {
    listaObecnosci *tabList[iloscList];

    int aktywnaLista = 0;
    int opcja;

    do {
        cout << "\nT A B E L A   O B E C N O S C I\n"
            << "1. Wyswietl\n"
            << "2. Dodaj osobe\n"
            << "3. Ustaw obecnosc\n"
            << "4. Edytuj osobe\n"
            << "5. Usun osobe\n"
            << "6. Nowa lista\n"
            << "7. Wybierz liste\n"
            << "0. Wyjdz\n";

            cin >> opcja;
        
            if(opcja == 1){
                tabList[aktywnaLista]->wyswietl();
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

                tabList[aktywnaLista]->dodajOsobe(
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

                tabList[aktywnaLista]->ustawObecnosc(i, wartoscObec);
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
                    tabList[aktywnaLista]->getOsoba(i),
                    imie,
                    nazwisko,
                    indeks
                );
            }
            else if(opcja == 5) {
                int i;

                cout << "Podaj nr osoby do usuniecia: ";
                cin >> i;

                tabList[aktywnaLista]->usunOsobe(i);
            }
            else if(opcja == 6) {
                for(int i = 0; i < iloscList; i++) {
                    if(tabList[i] == nullptr) {
                        tabList[i] = new listaObecnosci;
                        cout << "Utworzona liste nr: " << i << "\n";
                        break;
                    }
                }
            }
            else if(opcja == 7) {
                int nr;

                cout << "Podaj numer listy: ";
                cin >> nr;

                if (nr >= 0 && nr < iloscList && tabList[nr] != nullptr) {
                    aktywnaLista = nr;
                }
                else {
                    cout << "Wybrana lista nie istnieje!";
                }
            }
            else {
                cout << "Wybierz odpowiednia opcje!";
            }
         } while (opcja != 0);

    return 0;
}
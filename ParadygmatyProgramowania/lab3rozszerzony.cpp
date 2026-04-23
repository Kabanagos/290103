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

    int ustawDane(string i, string n, int ind) {
        if (i.length() < 2 || n.length() < 2) {
            return -1;
        }
        imie = i;
        nazwisko = n;
        indeks = ind;
        return 0;
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
    int aktualnaIlosc = 0;

public:
    listaObecnosci(int max = MAX);

    void dodajOsobe(Osoba *os);
    void ustawObecnosc(string nazwisko, bool wartosc);
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

void listaObecnosci::dodajOsobe(Osoba *os) {
    if (aktualnaIlosc < rozmiar) {
            tabOsob[aktualnaIlosc] = os;
            tabObecnosc[aktualnaIlosc] = false;
            aktualnaIlosc++;
        }
}

void listaObecnosci::ustawObecnosc(string nazwisko, bool wartosc) {
    for (int i = 0; i < aktualnaIlosc; i++) {
            if (tabOsob[i]->getNazwisko() == nazwisko) {
                tabObecnosc[i] = wartosc;
            }
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

    for(int j = i; j < MAX - 1; j++) {
        tabOsob[j] = tabOsob[j+1];
        tabObecnosc[j] = tabObecnosc[j+1];
    }

    aktualnaIlosc--;
    tabOsob[MAX-1] = nullptr;
    tabObecnosc[MAX-1] = false;
}

class InterfejsUzytkownika {
private:
    Osoba *tabOsob;
    int iloscOsob;
    listaObecnosci *tablicaList;
    int iloscList;
    
    int licznikOsob;
    int licznikList;

    void dodajOsobe() {
        if (licznikOsob < iloscOsob) {
            string i, n;
            int ind;
            cout << "Imie: "; cin >> i;
            cout << "Nazwisko: "; cin >> n;
            cout << "Indeks: "; cin >> ind;
            if (tabOsob[licznikOsob].ustawDane(i, n, ind) == 0) {
                licznikOsob++;
                cout << "Dodano osobe do bazy.\n";
            } else {
                cout << "Blad: Dane zbyt krotkie!\n";
            }
        }
    }

    void dodajListe() {
        if (licznikList < iloscList) {
            licznikList++;
            cout << "Dodano nowa liste. Aktywne: " << licznikList << endl;
        }
    }

    void dodajOsobeDoListy() {
        int nrL, nrO;
        cout << "Nr listy (0-" << licznikList - 1 << "): "; cin >> nrL;
        cout << "Nr osoby z bazy (0-" << licznikOsob - 1 << "): "; cin >> nrO;
        if (nrL >= 0 && nrL < licznikList && nrO >= 0 && nrO < licznikOsob) {
            tablicaList[nrL].dodajOsobe(&tabOsob[nrO]);
        }
    }

    void ustawObecnosc() {
        int nrL;
        string nazwisko;
        bool stan;
        cout << "Nr listy: "; cin >> nrL;
        cout << "Nazwisko: "; cin >> nazwisko;
        cout << "Obecny (1/0): "; cin >> stan;
        if (nrL >= 0 && nrL < licznikList) {
            tablicaList[nrL].ustawObecnosc(nazwisko, stan);
        }
    }

    void usunOsobe() {
        int nrL, nrO;
        cout << "Nr listy: "; cin >> nrL;
        cout << "Nr na liscie: "; cin >> nrO;
        if (nrL >= 0 && nrL < licznikList) {
            tablicaList[nrL].usunOsobe(nrO);
        }
    }

    void edytujOsobe() {
        int nrO;
        cout << "Nr osoby w bazie (0-" << licznikOsob - 1 << "): "; cin >> nrO;
        if (nrO >= 0 && nrO < licznikOsob) {
            string i, n;
            int ind;
            cout << "Nowe imie: "; cin >> i;
            cout << "Nowe nazwisko: "; cin >> n;
            cout << "Nowy indeks: "; cin >> ind;
            tabOsob[nrO].ustawDane(i, n, ind);
        }
    }

public:
    InterfejsUzytkownika(Osoba *tO, int nO, listaObecnosci *tL, int nL) {
        tabOsob = tO;
        iloscOsob = nO;
        tablicaList = tL;
        iloscList = nL;
        licznikOsob = 0;
        licznikList = 0;
    }

    void loop() {
        int wybor;
        do {
            cout << "\n1. Dodaj osobe\n2. Dodaj liste\n3. Przypisz do listy\n"
                 << "4. Ustaw obecnosc\n5. Usun osobe\n6. Edytuj osobe\n"
                 << "7. Wyswietl\n0. Wyjscie\nWybor: ";
            cin >> wybor;

            switch (wybor) {
                case 1: dodajOsobe(); break;
                case 2: dodajListe(); break;
                case 3: dodajOsobeDoListy(); break;
                case 4: ustawObecnosc(); break;
                case 5: usunOsobe(); break;
                case 6: edytujOsobe(); break;
                case 7: {
                    int nr;
                    cout << "Nr listy: "; cin >> nr;
                    if (nr >= 0 && nr < licznikList) tablicaList[nr].wyswietl();
                    break;
                }
            }
        } while (wybor != 0);
    }
};

int main() {
    Osoba tabOsob[MAX];
    listaObecnosci tabList[2];

    InterfejsUzytkownika ui(tabOsob, MAX, tabList, 2);
    ui.loop();

    return 0;
}
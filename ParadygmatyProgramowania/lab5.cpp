#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class Osoba {
protected:
    string imie;
    string nazwisko;
public:
    Osoba() : imie(""), nazwisko("") {}
    void ustawDane(string i, string n) { imie = i; nazwisko = n; }
    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }

    virtual void przedstawSie() {
        cout << imie << " " << nazwisko;
    }
    virtual ~Osoba() {}
};

class Student : public Osoba {
private:
    int indeks;
public:
    Student() : Osoba(), indeks(0) {}
    void ustawWszystko(string i, string n, int ind) {
        ustawDane(i, n);
        indeks = ind;
    }
    int getIndeks() { return indeks; }

    void przedstawSie() {
        cout << "Student: " << imie << " " << nazwisko << " (Indeks: " << indeks <<")";
    }
};

class Pracownik : public Osoba {
private:
    int id_prac;
public:
    Pracownik() : Osoba(), id_prac(0) {}
    void ustawDanePracownika(string i, string n, int id) {
        ustawDane(i, n);
        id_prac = id;
    }
    int getID() {return id_prac; }

    void przedstawSie() {
        cout << "Pracownik " << imie << " " << nazwisko << " (ID Pracownika: " << id_prac << ")";
    }
};

class listaObecnosci {
private:
    Student **tabOsob;
    bool *tabObecnosc;
    int rozmiar;
    int aktualnaIlosc;

public:
    listaObecnosci(int max = MAX) : rozmiar(max), aktualnaIlosc(0) {
        tabOsob = new Student*[rozmiar];
        tabObecnosc = new bool[rozmiar];
        for(int i = 0; i < rozmiar; i++) {
            tabOsob[i] = nullptr;
            tabObecnosc[i] = false;
        }
    }

    void dodajOsobe(Student *os) {
        if (aktualnaIlosc < rozmiar) {
            tabOsob[aktualnaIlosc] = os;
            tabObecnosc[aktualnaIlosc] = false;
            aktualnaIlosc++;
        }
    }

    void ustawObecnosc(int nrOsoby, bool wartosc) {
        if (nrOsoby >= 0 && nrOsoby < aktualnaIlosc) {
            tabObecnosc[nrOsoby] = wartosc;
            cout << "Zmieniono status obecnosci dla: " << tabOsob[nrOsoby]->getNazwisko() << endl;
        } else {
            cout << "Blad: Nie ma osoby o takim numerze na tej liscie!" << endl;
        }
    }

    void usunOsobe(int i) {
        if (i < 0 || i >= aktualnaIlosc || tabOsob[i] == nullptr) return;
        for (int j = i; j < aktualnaIlosc - 1; j++) {
            tabOsob[j] = tabOsob[j + 1];
            tabObecnosc[j] = tabObecnosc[j + 1];
        }
        aktualnaIlosc--;
        tabOsob[aktualnaIlosc] = nullptr;
    }

    void wyswietl() {
        cout << "\nNr.\tIndeks\tImie\tNazwisko\tObecnosc\n";
        for(int i = 0; i < aktualnaIlosc; i++) {
            cout << i << ".\t" << tabOsob[i]->getIndeks() << "\t"
                 << tabOsob[i]->getImie() << "\t" << tabOsob[i]->getNazwisko() << "\t"
                 << (tabObecnosc[i] ? "1" : "0") << "\n";
        }
    }

    ~listaObecnosci() { delete[] tabObecnosc; delete[] tabOsob; }
};

class InterfejsUzytkownika {
private:
    Student *tabOsob;
    int iloscOsob;
    listaObecnosci *tablicaList;
    int iloscList;
    int licznikOsob;
    int licznikList;

    void dodajOsobe() {
        if (licznikOsob < iloscOsob) {
            string i, n; int ind;
            cout << "Imie: "; cin >> i;
            cout << "Nazwisko: "; cin >> n;
            cout << "Indeks: "; cin >> ind;
            tabOsob[licznikOsob].ustawWszystko(i, n, ind);
            licznikOsob++;
            cout << "Dodano osobe.\n";
        }
    }

    void dodajListe() {
        if (licznikList < iloscList) {
            licznikList++;
            cout << "Dodano liste. Aktywne: " << licznikList << endl;
        }
    }

    void dodajOsobeDoListy() {
        int nrListy, nrOsoby;
        cout << "Nr listy (0-" << licznikList - 1 << "): "; cin >> nrListy;
        cout << "Nr osoby z bazy (0-" << licznikOsob - 1 << "): "; cin >> nrOsoby;
        if (nrListy >= 0 && nrListy < licznikList && nrOsoby >= 0 && nrOsoby < licznikOsob) {
            tablicaList[nrListy].dodajOsobe(&tabOsob[nrOsoby]);
        }
    }

    void ustawObecnosc() {
        int nrListy, nrOsoby; 
        bool stan;
        cout << "Nr listy (0-" << licznikList - 1 << "): "; cin >> nrListy;
        cout << "Nr osoby na liscie (0-" << licznikOsob - 1 << "): "; cin >> nrOsoby;
        cout << "Obecny (1/0): "; cin >> stan;
        
        if (nrListy >= 0 && nrListy < licznikList) {
            tablicaList[nrListy].ustawObecnosc(nrOsoby, stan);
        }
    }

    void usunZListy() {
        int nrListy, nrOsoby;
        cout << "Nr listy (0-" << licznikList - 1 << "): "; cin >> nrListy;
        cout << "Nr na liscie: "; cin >> nrOsoby;
        if (nrListy >= 0 && nrListy < licznikList) tablicaList[nrListy].usunOsobe(nrOsoby);
    }

    void edytujOsobe() {
        int nrOsoby;
        cout << "Nr osoby w bazie (0-" << licznikOsob - 1 << "): "; cin >> nrOsoby;
        if (nrOsoby >= 0 && nrOsoby < licznikOsob) {
            cin.ignore(1000, '\n');
            string noweImie, noweNazwisko, nowyIndeksStr;
        
            cout << "Nowe imie (Enter aby pominac): " << flush;
            getline(cin, noweImie);
            
            cout << "Nowe nazwisko (Enter aby pominac): " << flush;
            getline(cin, noweNazwisko);
            
            cout << "Nowy indeks (Enter aby pominac): " << flush;
            getline(cin, nowyIndeksStr);

            string i = (noweImie != "") ? noweImie : tabOsob[nrOsoby].getImie();
            string n = (noweNazwisko != "") ? noweNazwisko : tabOsob[nrOsoby].getNazwisko();
            int ind = (nowyIndeksStr != "") ? stoi(nowyIndeksStr) : tabOsob[nrOsoby].getIndeks();

            tabOsob[nrOsoby].ustawWszystko(i, n, ind);
            cout << "Dane zaktualizowane." << endl;
        }
    }

public:
    InterfejsUzytkownika(Student *tO, int nO, listaObecnosci *tL, int nL) 
        : tabOsob(tO), iloscOsob(nO), tablicaList(tL), iloscList(nL), licznikOsob(0), licznikList(0) {}

    void petla() {
        int wybor;
        do {
            cout << "\n- - - L I S T A   O B E C N O S C I - - -\n" 
                 << "\n1. Dodaj osobe\n2. Dodaj liste\n3. Przypisz do listy\n"
                 << "4. Ustaw obecnosc\n5. Usun z listy\n6. Edytuj osobe\n"
                 << "7. Wyswietl liste\n0. Wyjscie\n\nWybor: " << flush;

            cin >> wybor;
            cin.ignore(1000, '\n');

            switch (wybor) {
                case 1: dodajOsobe(); break;
                case 2: dodajListe(); break;
                case 3: dodajOsobeDoListy(); break;
                case 4: ustawObecnosc(); break;
                case 5: usunZListy(); break;
                case 6: edytujOsobe(); break;
                case 7: {
                    int nr; cout << "Nr listy  (0-" << licznikList - 1 << "): "; cin >> nr;
                    if (nr >= 0 && nr < licznikList) tablicaList[nr].wyswietl();
                    break;
                }
            }
        } while (wybor != 0);
    }
};

int main() {
    const int maxList = 2;

    Student tablicaOsob[MAX]; 
    listaObecnosci tablicaList[maxList];

    InterfejsUzytkownika ui(tablicaOsob, MAX, tablicaList, maxList);
    ui.petla();

    return 0;
}
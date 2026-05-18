#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class IDrukowalny {
public:
    virtual string przedstawSie() = 0;
    virtual ~IDrukowalny() {}
};

class Osoba : public IDrukowalny {
protected:
    string imie;
    string nazwisko;
    int typ;
public:
    Osoba() : imie(""), nazwisko("") {}
    void ustawDane(string i, string n) { imie = i; nazwisko = n; }
    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    int getTyp() { return typ; }

    string przedstawSie() override {
        return "Osoba: " + imie + " " + nazwisko;
    }
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

    string przedstawSie() override {
        return "Student: " + imie + " " + nazwisko + " (Indeks: " + to_string(indeks) + ")";
    }
};

class Pracownik : public Osoba {
private:
    int id_prac;
public:
    Pracownik() : Osoba(), id_prac(0) {}
    void ustawWszystko(string i, string n, int id) {
        ustawDane(i, n);
        id_prac = id;
    }
    int getID() { return id_prac; }

    string przedstawSie() override {
        return "Pracownik: " + imie + " " + nazwisko + " (ID Pracownika: " + to_string(id_prac) + ")";
    }
};


void drukuj(IDrukowalny *obj) {
    if(obj != nullptr) {
        cout << obj->przedstawSie() << endl;
    }
}

class listaObecnosci {
private:
    Osoba **tabOsob;
    bool *tabObecnosc;
    int rozmiar;
    int aktualnaIlosc;

public:
    listaObecnosci(int max = MAX) : rozmiar(max), aktualnaIlosc(0) {
        tabOsob = new Osoba*[rozmiar];
        tabObecnosc = new bool[rozmiar];
        for(int i = 0; i < rozmiar; i++) {
            tabOsob[i] = nullptr;
            tabObecnosc[i] = false;
        }
    }

    void dodajOsobe(Osoba *os) {
        if (os != nullptr && aktualnaIlosc < rozmiar) {
            tabOsob[aktualnaIlosc] = os;
            tabObecnosc[aktualnaIlosc] = false;
            aktualnaIlosc++;
        }
    }

    void ustawObecnosc(int nrOsoby, bool wartosc) {
        if (nrOsoby >= 0 && nrOsoby < aktualnaIlosc && tabOsob[nrOsoby] != nullptr) {
            tabObecnosc[nrOsoby] = wartosc;
            cout << "Zmieniono status obecnosci dla: " << tabOsob[nrOsoby]->getNazwisko() << endl;
        } else {
            cout << "Blad: Nieprawidlowy numer osoby lub osoba nie istnieje!" << endl;
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
        cout << "\n- - Lista Obecnosci nr " << " (mixed types) - -\n";
        cout << "\nNr.\tObecnosc\tOpis osoby\n";
        for(int i = 0; i < aktualnaIlosc; i++) {
            if(tabOsob[i] != nullptr) {
                cout << i << ".\t"
                     << (tabObecnosc[i] ? "[X]" : "[ ]") << "\t\t"
                     << tabOsob[i]->przedstawSie() << "\n";
            }
        }
    }

    ~listaObecnosci() {
        delete[] tabObecnosc;
        delete[] tabOsob;
    }
};


class InterfejsUzytkownika {
private:
    Osoba **tabOsob;
    int iloscOsob;
    listaObecnosci *tablicaList;
    int iloscList;
    int licznikOsob;
    int licznikList;

    void wyczyscCin() {
        cin.clear();
        cin.ignore(10000, '\n');
    }

    void dodajOsobe() {
        if (licznikOsob < iloscOsob) {
            int typ;
            string i, n;
            cout << "Typ osoby (1-Student, 2-Pracownik): " << flush;
            if (!(cin >> typ)) { wyczyscCin(); return; }
            cin.ignore(1000, '\n');

            if(typ != 1 && typ != 2) {
                cout << "Blad: Nieznany typ osoby!\n";
                return;
            }

            cout << "Imie: " << flush; getline(cin, i);
            cout << "Nazwisko: " << flush; getline(cin, n);

            if(typ == 1) {
                int ind;
                cout << "Indeks: " << flush;
                if (!(cin >> ind)) { wyczyscCin(); return; }
                cin.ignore(1000, '\n');

                tabOsob[licznikOsob] = new Student();
                dynamic_cast<Student*>(tabOsob[licznikOsob])->ustawWszystko(i, n, ind);
            } else {
                int id;
                cout << "ID Pracownika: " << flush;
                if (!(cin >> id)) { wyczyscCin(); return; }
                cin.ignore(1000, '\n');

                tabOsob[licznikOsob] = new Pracownik();
                dynamic_cast<Pracownik*>(tabOsob[licznikOsob])->ustawWszystko(i, n, id);
            }

            licznikOsob++;
            cout << "Dodano osobe.\n";
        } else {
            cout << "Baza osob jest pelna!\n";
        }
    }

    void dodajListe() {
        if (licznikList < iloscList) {
            licznikList++;
            cout << "Dodano liste. Aktywne: " << licznikList << endl;
        } else {
            cout << "Maksymalna ilosc list osiagnieta!\n";
        }
    }

    void dodajOsobeDoListy() {
        int nrListy, nrOsoby;
        cout << "Nr listy (0-" << licznikList - 1 << "): " << flush; cin >> nrListy;
        cout << "Nr osoby z bazy (0-" << licznikOsob - 1 << "): " << flush; cin >> nrOsoby;
        wyczyscCin();

        if (nrListy >= 0 && nrListy < licznikList && nrOsoby >= 0 && nrOsoby < licznikOsob) {
            tablicaList[nrListy].dodajOsobe(tabOsob[nrOsoby]);
            cout << "Przypisano osobe na liste.\n";
        } else {
            cout << "Blad: Nieprawidlowy numer listy lub osoby!\n";
        }
    }

    void ustawObecnosc() {
        int nrListy, nrOsoby;
        bool stan;
        cout << "Nr listy (0-" << licznikList - 1 << "): " << flush; cin >> nrListy;
        cout << "Nr osoby na liscie: " << flush; cin >> nrOsoby;
        cout << "Obecny (1/0): " << flush; cin >> stan;
        wyczyscCin();

        if (nrListy >= 0 && nrListy < licznikList) {
            tablicaList[nrListy].ustawObecnosc(nrOsoby, stan);
        } else {
            cout << "Blad: Nieprawidlowy numer listy!\n";
        }
    }

    void usunZListy() {
        int nrListy, nrOsoby;
        cout << "Nr listy (0-" << licznikList - 1 << "): " << flush; cin >> nrListy;
        cout << "Nr na liscie: " << flush; cin >> nrOsoby;
        wyczyscCin();
        if (nrListy >= 0 && nrListy < licznikList) {
            tablicaList[nrListy].usunOsobe(nrOsoby);
            cout << "Usunieto osobe z listy.\n";
        }
    }

    void edytujOsobe() {
        int nrOsoby;
        cout << "Nr osoby w bazie (0-" << licznikOsob - 1 << "): " << flush; cin >> nrOsoby;
        wyczyscCin();

        if (nrOsoby >= 0 && nrOsoby < licznikOsob && tabOsob[nrOsoby] != nullptr) {
            string noweImie, noweNazwisko;
            cout << "Nowe imie (Enter aby pominac): " << flush; getline(cin, noweImie);
            cout << "Nowe nazwisko (Enter aby pominac): " << flush; getline(cin, noweNazwisko);

            string i = (noweImie != "") ? noweImie : tabOsob[nrOsoby]->getImie();
            string n = (noweNazwisko != "") ? noweNazwisko : tabOsob[nrOsoby]->getNazwisko();

            if (tabOsob[nrOsoby]->getTyp() == 1) {
                Student* s = (Student*)tabOsob[nrOsoby];
                
                string nowyIndStr;
                cout << "Nowy indeks (Enter aby pominac): " << flush; getline(cin, nowyIndStr);
                int ind = (nowyIndStr != "") ? stoi(nowyIndStr) : s->getIndeks();
                s->ustawWszystko(i, n, ind);
            } 

            else if (tabOsob[nrOsoby]->getTyp() == 2) {
                Pracownik* p = (Pracownik*)tabOsob[nrOsoby];
                
                string nowyIdStr;
                cout << "Nowy ID Pracownika (Enter aby pominac): " << flush; getline(cin, nowyIdStr);
                int id = (nowyIdStr != "") ? stoi(nowyIdStr) : p->getID();
                p->ustawWszystko(i, n, id);
            }

            cout << "Dane zaktualizowane.\n";
        } else {
            cout << "Blad: Nieprawidlowy numer osoby lub osoba nie istnieje!\n";
        }
    }

    void testDrukuj() {
        int nrO;
        cout << "Nr osoby w bazie (0-" << licznikOsob - 1 << ") do testu uniwersalnego: " << flush; cin >> nrO;
        wyczyscCin();
        if(nrO >= 0 && nrO < licznikOsob && tabOsob[nrO] != nullptr) {
            cout << "Wywolanie uniwersalnej funkcji void drukuj(IDrukowalny*):\n";
            drukuj(tabOsob[nrO]);
        }
    }

public:
    InterfejsUzytkownika(Osoba **tO, int nO, listaObecnosci *tL, int nL)
        : tabOsob(tO), iloscOsob(nO), tablicaList(tL), iloscList(nL), licznikOsob(0), licznikList(0) {}

    void petla() {
        int wybor;
        do {
            cout << "\n- - - L I S T A   O B E C N O S C I - - -\n"
                 << "\n1. Dodaj osobe\n2. Dodaj liste\n3. Przypisz do listy\n"
                 << "4. Ustaw obecnosc\n5. Usun z listy\n6. Edytuj osobe\n"
                 << "7. Wyswietl liste\n8. Test druku uniwersalnego\n0. Wyjscie\n\nWybor: " << flush;

            if(!(cin >> wybor)) { wyczyscCin(); continue; }
            cin.ignore(1000, '\n');

            switch (wybor) {
                case 1: dodajOsobe(); break;
                case 2: dodajListe(); break;
                case 3: dodajOsobeDoListy(); break;
                case 4: ustawObecnosc(); break;
                case 5: usunZListy(); break;
                case 6: edytujOsobe(); break;
                case 7: {
                    int nr; cout << "Nr listy (0-" << licznikList - 1 << "): "; cin >> nr;
                    if (nr >= 0 && nr < licznikList) tablicaList[nr].wyswietl();
                    break;
                }
                case 8: testDrukuj(); break;
            }
        } while (wybor != 0);
    }

    ~InterfejsUzytkownika() {
        for(int i=0; i<iloscOsob; i++) {
            if(tabOsob[i] != nullptr) {
                delete tabOsob[i];
            }
        }
    }
};

int main() {
    const int maxList = 2;

    Osoba* tablicaOsob[MAX];
    for(int i=0; i<MAX; i++) tablicaOsob[i] = nullptr;

    listaObecnosci tablicaList[maxList];

    InterfejsUzytkownika ui(tablicaOsob, MAX, tablicaList, maxList);
    ui.petla();

    return 0;
}
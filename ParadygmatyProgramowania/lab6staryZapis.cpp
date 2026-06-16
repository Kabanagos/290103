#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

const int MAX = 10;

class ISerializable {
public:
    virtual string serialize() = 0;
    virtual ~ISerializable() {}
};

class IEksportowalny {
    public:
        virtual map<string, string> eksportuj() = 0;
        virtual int getTypEksportu() = 0;
        virtual ~IEksportowalny() {}
};

class IEksporter {
    public:
        virtual void wykonajEksport(IEksportowalny *obj, string nazwaPliku) = 0;
        virtual ~IEksporter() {}
};

class Osoba : public ISerializable, public IEksportowalny {
protected:
    string imie;
    string nazwisko;
    int typ;
public:
    Osoba() : imie(""), nazwisko("") {}
    void ustawDane(string i, string n, int t) { 
        imie = i; 
        nazwisko = n; 
        typ = t;
    }
    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    int getTyp() { return typ; }

    int getTypEksportu() override { return 1; }

    string serialize() override {
        return "Osoba: " + imie + " " + nazwisko;
    }

    map<string, string> eksportuj() override {
        map<string, string> dane;
        dane["1_Typ"] = (typ == 1 ? "Student" : "Pracownik");
        dane["2_Imie"] = imie;
        dane["3_Nazwisko"] = nazwisko;
        return dane;
    }
};

class Student : public Osoba {
private:
    int indeks;
public:
    Student() : Osoba(), indeks(0) {}
    void ustawWszystko(string i, string n, int idx) {
        ustawDane(i, n, 1);
        indeks = idx;
    }
    int getIndeks() { return indeks; }

    string serialize() override {
        return "Student: " + imie + " " + nazwisko + " (Indeks: " + to_string(indeks) + ")";
    }

    map<string, string> eksportuj() override {
            map<string, string> dane = Osoba::eksportuj(); 
            dane["4_Detal"] = to_string(indeks);
            return dane;
        }
};

class Pracownik : public Osoba {
private:
    int id_prac;
public:
    Pracownik() : Osoba(), id_prac(0) {}
    void ustawWszystko(string i, string n, int id) {
        ustawDane(i, n, 2);
        id_prac = id;
    }
    int getID() { return id_prac; }

    string serialize() override {
        return "Pracownik: " + imie + " " + nazwisko + " (ID Pracownika: " + to_string(id_prac) + ")";
    }

    map<string, string> eksportuj() override {
            map<string, string> dane = Osoba::eksportuj(); 
            dane["4_Detal"] = to_string(id_prac);
            return dane;
        }
};

void drukuj(ISerializable *obj) {
    if(obj != nullptr) {
        cout << obj->serialize() << endl;
    }
} 

void zapiszDoPliku(ISerializable *obj, string nazwaPliku, bool nadpisanie) {
    if (obj == nullptr) return;
    
    ofstream plik;
    if (nadpisanie) {
        plik.open(nazwaPliku);
    } else {
        plik.open(nazwaPliku, ios::app);
    }

    if (plik.is_open()) {
        plik << obj->serialize() << "\n";
        plik.close();
        cout << "Pomyślnie zapisano dane do pliku: " << nazwaPliku << "\n";
    } else {
        cout << "Blad! Nie udalo sie otworzyc pliku!\n";
    }
}

class listaObecnosci : public ISerializable, public IEksportowalny {
private:
    Osoba **tabOsob;
    bool *tabObecnosc;
    int rozmiar;
    int aktualnaIlosc;

public:
    int getAktualnaIlosc() { return aktualnaIlosc; }
    Osoba* getOsoba(int indeks) { return tabOsob[indeks]; }
    bool getObecnosc(int indeks) { return tabObecnosc[indeks]; }

    int getTypEksportu() override { return 2; }
    
    string serialize() override {
        string wynik = "- - - S T A N   L I S T Y   O B E C N O S C I - - -\n";
        for (int i = 0; i < aktualnaIlosc; i++) {
            if (tabOsob[i] != nullptr) {
                wynik += to_string(i) + ".\t"
                       + (tabObecnosc[i] ? "[X] Tak" : "[ ] Nie") + "\t\t"
                       + tabOsob[i]->serialize() + "\n";
            }
        }
        return wynik;
    }

    listaObecnosci(int max = MAX) : rozmiar(max), aktualnaIlosc(0) {
        tabOsob = new Osoba*[rozmiar];
        tabObecnosc = new bool[rozmiar];
        for(int i = 0; i < rozmiar; i++) {
            tabOsob[i] = nullptr;
            tabObecnosc[i] = false;
        }
    }

    map<string, string> eksportuj() override {
            map<string, string> dane;
            dane["1_TypObiektu"] = "ListaObecnosci";
            dane["2_LiczbaOsob"] = to_string(aktualnaIlosc);
            return dane;
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

    void wyswietl(int nrListy) {
        cout << "\n- - - L I S T A   NR " << nrListy << " - - -\n";
        cout << "\nNr.\tObecnosc\tOpis osoby\n";
        for(int i = 0; i < aktualnaIlosc; i++) {
            if(tabOsob[i] != nullptr) {
                cout << i << ".\t"
                     << (tabObecnosc[i] ? "[X]" : "[ ]") << "\t\t"
                     << tabOsob[i]->serialize() << "\n";
            }
        }
    }

    ~listaObecnosci() {
        delete[] tabObecnosc;
        delete[] tabOsob;
    }
};

class EksporterTXT : public IEksporter {
public:
    void wykonajEksport(IEksportowalny *obj, string nazwaPliku) override {
        if (obj == nullptr) return;
        ofstream plik(nazwaPliku, ios::app);

        if (plik.is_open()) {
            if (obj->getTypEksportu() == 2) {          
                listaObecnosci* lista = static_cast<listaObecnosci*>(obj);
        
                if (lista != nullptr) {
                    plik << "- - - S P I S   L I S T Y   O B E C N O S C I - - -\n";
                    plik << "Liczba osob: " << lista->getAktualnaIlosc() << "\n\n";
        
                    for (int i = 0; i < lista->getAktualnaIlosc(); i++) {
                        if (lista->getOsoba(i) != nullptr) {
                            plik << "Pozycja nr " << i << "\n";
                            plik << "Obecnosc: " << (lista->getObecnosc(i) ? "TAK" : "NIE") << "\n";
                            
                            map<string, string> daneOsoby = lista->getOsoba(i)->eksportuj();
                            map<string, string>::iterator it;
                            for(it = daneOsoby.begin(); it != daneOsoby.end(); ++it) {
                                plik << "  " << it->first << ": " << it->second << "\n";
                            }
                            plik << "- - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                        }
                    }
                }
            }
            else {
                map<string, string> dane = obj->eksportuj();
                map<string, string>::iterator it;
                plik << "- - - W P I S   P O J E D Y N C Z E J   O S O B Y - - -\n";
                for(it = dane.begin(); it != dane.end(); ++it) {
                    plik << it->first << ": " << it->second << "\n";
                }
                plik << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
            }
        plik.close();
        cout << "[TXT] Eksport zakonczony sukcesem.\n";
        }
    }
};

class EksporterCSV : public IEksporter {
public:
    void wykonajEksport(IEksportowalny *obj, string nazwaPliku) override {
        if (obj == nullptr) return;
        ofstream plik(nazwaPliku, ios::app);

        if (plik.is_open()) {
            if (obj->getTypEksportu() == 2) {
                listaObecnosci* lista = static_cast<listaObecnosci*>(obj);
        
                for (int i = 0; i < lista->getAktualnaIlosc(); i++) {
                    if (lista->getOsoba(i) != nullptr) {
                        map<string, string> daneOsoby = lista->getOsoba(i)->eksportuj();
                        map<string, string>::iterator it;
                        
                        bool pierwszy = true;
                        for(it = daneOsoby.begin(); it != daneOsoby.end(); ++it) {
                            if(!pierwszy) plik << ";";
                            plik << it->second;
                            pierwszy = false;
                        }
                        
                        plik << ";" << (lista->getObecnosc(i) ? "TAK" : "NIE") << "\n";
                    }
                }
            } 
            else {
                map<string, string> dane = obj->eksportuj();
                map<string, string>::iterator it;
                bool pierwszy = true;
                for(it = dane.begin(); it != dane.end(); ++it) {
                    if(!pierwszy) plik << ";";
                    plik << it->second;
                    pierwszy = false;
                }
                plik << "\n";
            }
            plik.close();
            cout << "[CSV] Eksport do arkusza zakonczony sukcesem.\n";
        }
    }
};

class InterfejsUzytkownika {
private:
    Osoba **tabOsob;
    int iloscOsob;
    listaObecnosci *tabList;
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
            cout << "Typ osoby (1: Student, 2: Pracownik): " << flush;
            if (!(cin >> typ)) { wyczyscCin(); return; }
            cin.ignore(1000, '\n');

            if(typ != 1 && typ != 2) {
                cout << "Blad: Nieznany typ osoby!\n";
                return;
            }

            cout << "Imie: " << flush; getline(cin, i);
            cout << "Nazwisko: " << flush; getline(cin, n);

            if(typ == 1) {
                int idx;
                cout << "Indeks: " << flush;
                if (!(cin >> idx)) { wyczyscCin(); return; }
                cin.ignore(1000, '\n');

                Student* nowyStudent = new Student();
                nowyStudent->ustawWszystko(i, n, idx);
                tabOsob[licznikOsob] = nowyStudent;
            } else {
                int id;
                cout << "ID Pracownika: " << flush;
                if (!(cin >> id)) { wyczyscCin(); return; }
                cin.ignore(1000, '\n');

                Pracownik* nowyPracownik = new Pracownik();
                nowyPracownik->ustawWszystko(i, n, id);
                tabOsob[licznikOsob] = nowyPracownik;
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
            tabList[nrListy].dodajOsobe(tabOsob[nrOsoby]);
            cout << "Przypisano osobe na liste.\n";
        } else {
            cout << "Blad: Nieprawidlowy numer listy lub osoby!\n";
        }
    }

    void ustawObecnosc() {
        int nrListy, nrOsoby;
        bool stan;
        cout << "Nr listy (0-" << licznikList - 1 << "): " << flush; cin >> nrListy;
        cout << "Nr osoby na liscie (0-" << licznikOsob -1 << "): " << flush; cin >> nrOsoby;
        cout << "Obecny (1/0): " << flush; cin >> stan;
        wyczyscCin();

        if (nrListy >= 0 && nrListy < licznikList) {
            tabList[nrListy].ustawObecnosc(nrOsoby, stan);
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
            tabList[nrListy].usunOsobe(nrOsoby);
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
            cout << "Wywolanie uniwersalnej funkcji void drukuj(ISerializable*):\n";
            drukuj(tabOsob[nrO]);
        }
    }

    void zapiszDoPlikuUI() {
        int wybor;
        cout << "Co chcesz zapisac do pliku?\n1. Pojedyncza osobe z bazy\n2. Cala liste obecnosci\nWybor: ";
        if (!(cin >> wybor)) { wyczyscCin(); return; }
        wyczyscCin();

        if (wybor == 1) {
            int nrOsoby;
            cout << "Nr osoby w bazie (0-" << licznikOsob - 1 << ") do zapisu: " << flush; cin >> nrOsoby;
            wyczyscCin();
            
            if (nrOsoby >= 0 && nrOsoby < licznikOsob && tabOsob[nrOsoby] != nullptr) {
                zapiszDoPliku(tabOsob[nrOsoby], "osoba.txt", false);
            } else {
                cout << "Niepoprawny numer osoby!\n";
            }
        }
        else if (wybor == 2) {
            int nrListy;
            cout << "Nr listy w bazie (0-" << licznikList - 1 << ") do zapisu: " << flush; cin >> nrListy;
            wyczyscCin();
    
            if (nrListy >= 0 && nrListy < licznikList) {
                zapiszDoPliku(&tabList[nrListy], "lista_nr_" + to_string(nrListy) + ".txt", true);
            } else {
                cout << "Niepoprawny numer listy!\n";
            }
        }
        else {
            cout << "Niepoprawny wybor!\n";
        }
    }

    void EksportUI() {
        int zrodlo, format;
        cout << "Co chcesz wyeksportowac?\n1. Pojedyncza osobe z bazy\n2. Cala liste\nWybor: ";
        cin >> zrodlo;
        cout << "\nFormat eksportu?\n1. TXT\n2. CSV\nWybor: ";
        cin >> format;
        wyczyscCin();
    
        IEksporter* eksporter = nullptr;
        if (format == 1) eksporter = new EksporterTXT();
        else if (format == 2) eksporter = new EksporterCSV();
        else { cout << "Niepoprawny format!\n"; return; }
    
        if (zrodlo == 1) {
            int nr; cout << "Nr osoby w bazie (0-" << licznikOsob - 1 << "): "; cin >> nr;
            if (nr >= 0 && nr < licznikOsob && tabOsob[nr] != nullptr) {
                eksporter->wykonajEksport(tabOsob[nr], format == 1 ? "eksport_osob.txt" : "eksport_osob.csv");
            }
        } else if (zrodlo == 2) {
            int nr; cout << "Nr listy w bazie (0-" << licznikList - 1 << "): "; cin >> nr;
            if (nr >= 0 && nr < licznikList) {
                eksporter->wykonajEksport(&tabList[nr], format == 1 ? "eksport_listy.txt" : "eksport_listy.csv");
            }
        }
        
        delete eksporter;
    }

public:
    InterfejsUzytkownika(Osoba **tabOsob, int iloscOsob, listaObecnosci *tabList, int iloscList)
        : tabOsob(tabOsob), iloscOsob(iloscOsob), tabList(tabList), iloscList(iloscList), licznikOsob(0), licznikList(0) {}

    void petla() {
        int wybor;
        do {
            cout << "\n- - - L I S T A   O B E C N O S C I - - -\n"
                 << "\n1. Dodaj osobe\n2. Dodaj liste\n3. Przypisz do listy\n"
                 << "4. Ustaw obecnosc\n5. Usun z listy\n6. Edytuj osobe\n"
                 << "7. Wyswietl liste\n8. Test druku uniwersalnego\n9. Stary zapis do pliku\n10. Eksportuj do pliku\n"
                 << "0. Wyjscie\n\nWybor: " << flush;

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
                    if (nr >= 0 && nr < licznikList) tabList[nr].wyswietl(nr);
                    break;
                }
                case 8: testDrukuj(); break;
                case 9: zapiszDoPlikuUI(); break;
                case 10: EksportUI(); break;
            }
        } while (wybor != 0);
    }

    ~InterfejsUzytkownika() {
        for(int i = 0; i < iloscOsob; i++) {
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

    listaObecnosci tabList[maxList];

    InterfejsUzytkownika ui(tablicaOsob, MAX, tabList, maxList);
    ui.petla();

    return 0;
}
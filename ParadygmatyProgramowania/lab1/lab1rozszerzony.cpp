#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

void dodajOsobe(
    int indeksy[], string imiona[], string nazwiska[], bool obecnosci[],
    string imie, string nazwisko, int indeks
) {
    for(int i = 0; i < MAX; i++) {
        if(nazwiska[i] == "") {
            imiona[i] = imie;
            nazwiska[i] = nazwisko;
            indeksy[i] = indeks;
            obecnosci[i] = false;
            break;
        }
    }
    return;
}

void ustawObecnosc(string nazwiska[], bool obecnosci[], int i, bool obecnosc) {
    if (i >= 0 && i < MAX && nazwiska[i] != "") {
        obecnosci[i] = obecnosc;
    }
    return;
}

void edytujOsobe(
    int indeksy[], string imiona[], string nazwiska[], 
    int i, string imie, string nazwisko, int indeks
) {
    if(imie != "") imiona[i] = imie;
    if(nazwisko != "") nazwiska[i] = nazwisko;
    if(indeks != -1) indeksy[i] = indeks;
    return;
}

void usunOsobe(
    int indeksy[],
    string imiona[],
    string nazwiska[],
    bool obecnosci[],
    int i
) {
    for(int j = i; j < MAX-1; j++) {
        imiona[j] = imiona[j+1];
        nazwiska[j] = nazwiska[j+1];
        indeksy[j] = indeksy[j+1];
        obecnosci[j] = obecnosci[j+1];
    }

    imiona[MAX-1] = "";
    nazwiska[MAX-1] = "";
    indeksy[MAX-1] = 0;
    obecnosci[MAX-1] = false;
    return;
}

void wyswietl(int indeksy[], string imiona[], string nazwiska[], bool obecnosci[]) {
    cout << "Nr.\tIndeks\tImie\tNazwisko\tObecnosc\n";

    for(int i = 0; i < MAX; i++) {
        if(nazwiska[i] == "") break;
        cout << i << ".\t"
             << indeksy[i] << "\t"
             << imiona[i] << "\t" 
             << nazwiska[i] << "\t" 
             << obecnosci[i] << "\n";
    }
    return;
}

int main() {
    int tabIndeksy[MAX];
    string tabImiona[MAX];
    string tabNazwiska[MAX];
    bool tabObecnosc[MAX];

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
                wyswietl(tabIndeksy, tabImiona, tabNazwiska, tabObecnosc);
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
                    tabIndeksy,
                    tabImiona,
                    tabNazwiska,
                    tabObecnosc,
                    imie,
                    nazwisko,
                    indeks
                );
            }
            else if(opcja == 3) {
                int i;
                bool obecnosc;

                cout << "Podaj nr. osoby (0-9): ";
                cin >> i;
                cout << "Podaj obecnosc (0/1): ";
                cin >> obecnosc;

                ustawObecnosc(tabNazwiska, tabObecnosc, i, obecnosc);
            }
            else if(opcja == 4) {
                int i;
                int indeks = -1;
                string imie, nazwisko, indeksStr;

                cout << "Podaj nr osoby (0-9): ";
                cin >> i;
                cin.ignore();

                cout << "Nowy indeks (jesli nie chcesz zmieniac zostaw pole puste): ";
                getline(cin, indeksStr);

                if(indeksStr != "") indeks = stoi(indeksStr);

                cout << "Nowe imie(jesli nie chcesz zmieniac zostaw pole puste): ";
                getline(cin, imie);

                cout << "Nowe nazwisko(jesli nie chcesz zmieniac zostaw pole puste): ";
                getline(cin, nazwisko);

                edytujOsobe(
                    tabIndeksy,
                    tabImiona,
                    tabNazwiska,
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
                    tabIndeksy,
                    tabImiona,
                    tabNazwiska,
                    tabObecnosc,
                    i
                );
            }
            else {
                cout << "Wybierz odpowiednia opcje!";
            }
         } while (opcja != 0);

    return 0;
}

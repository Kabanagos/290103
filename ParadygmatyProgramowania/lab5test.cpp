#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class Osoba {
protected:
    string imie;
    string nazwisko;
public:
    Osoba(string i, string n) : imie(i), nazwisko(n) {}

    virtual void przedstawSie() {
        cout << imie << " " << nazwisko << "\n";
    }
    virtual ~Osoba() {}
};

class Student : public Osoba {
private:
    int indeks;
public:
    Student(string i, string n, int idx) : Osoba(i, n), indeks(idx) {}

    void przedstawSie() override {
        cout << "Student: " << imie << " " << nazwisko << " (Indeks: " << indeks <<")\n";
    }
};

class Pracownik : public Osoba {
private:
    int id_prac;
public:
    Pracownik(string i, string n, int id) : Osoba(i, n), id_prac(id) {}

    void przedstawSie() override {
        cout << "Pracownik: " << imie << " " << nazwisko << " (ID Pracownika: " << id_prac << ")\n";
    }
};

int main() {
    Osoba* tabOsob[3];
    tabOsob[0] = new Osoba("Jan", "Kowalski");
    tabOsob[1] = new Student("Adrian", "Nowak", 103);
    tabOsob[2] = new Pracownik("Michał", "Disowski", 2);

    for(int i = 0; i < 3; i++) {
        tabOsob[i]->przedstawSie();
    }

    for(int i = 0; i < 3; i++) {
        delete tabOsob[i];
    }

    return 0;
}
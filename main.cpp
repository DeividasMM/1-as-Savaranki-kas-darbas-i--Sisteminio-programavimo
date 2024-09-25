#include "mylib.h"

char skaiciavimas = 'v'; // Pasirinkimas: 'v' - vidurkis, 'm' - mediana

int main() {
    cout << "Kaip skaiciuoti galutini bala? (v - vidurkis, m - mediana): ";
    cin >> skaiciavimas;

    vector<Studentas> grupe;
    char pridetiDarVienas = 't';

    while (pridetiDarVienas == 't') {
        Studentas K;
        grupe.push_back(K);
        cout << "Ar norite prideti dar viena studenta? (t/n): ";
        cin >> pridetiDarVienas;
    }

    cout << endl << "Ivesti studentai:" << endl;
    printf("|%-20s|%-20s|%20s|\n", "Pavarde", "Vardas",
        skaiciavimas == 'm' ? "Galutinis (Med.)" : "Galutinis (Vid.)");
    printf("--------------------------------------------------------------\n");

    for (auto& studentas : grupe) {
        studentas.print_galutinis();
    }

    return 0;
}

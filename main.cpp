#include "mylib.h"

char skaiciavimoStrategija = 'v'; // Pasirinkimas: 'v' - vidurkis, 'm' - mediana

int main() {
    cout << "Kaip skaiciuoti galutini bala? (v - vidurkis, m - mediana): ";
    cin >> skaiciavimoStrategija;

    vector<Studentas> studentuGrupe;
    int studentuKiekis;
    cout << "Kiek studentu bus ivesta? ";
    cin >> studentuKiekis;


    for (int i = 0; i < studentuKiekis; i++) {
        Studentas naujasStudentas;
        studentuGrupe.push_back(naujasStudentas);
    }


    int maxPazymiuKiekis = 0;
    for (const auto& studentas : studentuGrupe) {
        if (studentas.gautiPazymiuKieki() > maxPazymiuKiekis) {
            maxPazymiuKiekis = studentas.gautiPazymiuKieki();
        }
    }

    cout << endl << studentuGrupe.size() << " studentai ivesti." << endl;


    cout << setw(14) << left << "Pavarde"
        << setw(12) << left << "Vardas";

    for (int i = 0; i < maxPazymiuKiekis; i++) {
        cout << setw(5) << left << "ND" + to_string(i + 1);
    }

    cout << setw(10) << left << "Egzaminas"
        << setw(15) << left << (skaiciavimoStrategija == 'm' ? "Galutinis (Med.)" : "Galutinis (Vid.)")
        << endl;

    cout << "-----------------------------------------------------------------------------------------------" << endl;


    for (auto& studentas : studentuGrupe) {
        cout << setw(14) << left << studentas.gautiPavarde()
            << setw(12) << left << studentas.gautiVarda();

        int currentPazymiuKiekis = studentas.gautiPazymiuKieki();
        for (int i = 0; i < currentPazymiuKiekis; i++) {
            cout << setw(5) << left << studentas.gautiPazymius()[i];
        }


        for (int i = currentPazymiuKiekis; i < maxPazymiuKiekis; i++) {
            cout << setw(5) << left << "";
        }

        cout << setw(10) << left << studentas.gautiEgzaminoBala()
            << setw(15) << left;

        if (skaiciavimoStrategija == 'v') {
            cout << fixed << setprecision(2) << studentas.gautiGalutiniBalaVidurkis();
        }
        else if (skaiciavimoStrategija == 'm') {
            cout << fixed << setprecision(2) << studentas.gautiGalutiniBalaMediana();
        }

        cout << endl;
    }

    return 0;
}

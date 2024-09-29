#include "mylib.h"


int main() {
    char skaiciavimoStrategija = 'v';

    cout << "Kaip skaiciuoti galutini bala? (v - vidurkis, m - mediana): ";
    cin >> skaiciavimoStrategija;

    if (skaiciavimoStrategija != 'v' && skaiciavimoStrategija != 'm') {
        cout << "Neteisinga strategija. Naudojamas vidurkis (v)." << endl;
        skaiciavimoStrategija = 'v';
    }

    vector<Studentas> studentuGrupe;
    string eilute;

    ifstream failas("kursiokai.txt");
    try {
        if (!failas.is_open()) {
            throw runtime_error("Klaida atidarant failą.");
        }

        getline(failas, eilute);

        while (getline(failas, eilute)) {
            string vardas, pavarde;
            int egzaminas;
            vector<int> pazymiai;

            istringstream iss(eilute);
            iss >> vardas >> pavarde;

            int pazymys;
            while (iss >> pazymys) {
                pazymiai.push_back(pazymys);
            }

            if (pazymiai.empty()) {
                throw runtime_error("Studento pazymiu sarasas tuscias.");
            }

            egzaminas = pazymiai.back();
            pazymiai.pop_back();

            Studentas naujasStudentas(vardas, pavarde, pazymiai, egzaminas, skaiciavimoStrategija);
            studentuGrupe.push_back(naujasStudentas);
        }

        failas.close();

        cout << studentuGrupe.size() << " studentai nuskaityti." << endl;

    }
    catch (const std::exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
        return 1;
    }

    int maxPazymiuKiekis = 0;
    for (const auto& studentas : studentuGrupe) {
        maxPazymiuKiekis = std::max(maxPazymiuKiekis, studentas.gautiPazymiuKieki());
    }

    cout << setw(14) << left << "Pavarde"
        << setw(12) << left << "Vardas";

    for (int i = 0; i < maxPazymiuKiekis; i++) {
        cout << setw(5) << left << "ND" + to_string(i + 1);
    }

    cout << setw(10) << left << "Egzaminas"
        << setw(20) << left << (skaiciavimoStrategija == 'm' ? "Galutinis (Med.)" : "Galutinis (Vid.)")
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
            << setw(20) << left;

        if (skaiciavimoStrategija == 'v') {
            cout << fixed << setprecision(2) << studentas.gautiGalutiniBalaVidurkis();
        }
        else {
            cout << fixed << setprecision(2) << studentas.gautiGalutiniBalaMediana();
        }

        cout << endl;
    }

    return 0;
}

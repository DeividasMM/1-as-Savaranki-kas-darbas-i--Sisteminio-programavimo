#include "mylib.h"

Studentas ivestiNaujaStudenta() {
    string vardas, pavarde;
    vector<int> pazymiai(7);
    int egzaminas;
    char skaiciavimoStrategija;

    cout << "Iveskite studento varda: ";
    cin >> vardas;

    cout << "Iveskite studento pavarde: ";
    cin >> pavarde;

    cout << "Iveskite 7 namu darbu pazymius:\n";
    for (int i = 0; i < 7; ++i) {
        cout << "ND" << (i + 1) << ": ";
        cin >> pazymiai[i];
    }

    cout << "Iveskite egzamino pazymi: ";
    cin >> egzaminas;

    cout << "Kaip norite skaiciuoti galutini bala? (v - vidurkis, m - mediana): ";
    cin >> skaiciavimoStrategija;

    if (skaiciavimoStrategija != 'v' && skaiciavimoStrategija != 'm') {
        cout << "Neteisinga strategija. Naudojamas vidurkis (v)." << endl;
        skaiciavimoStrategija = 'v';
    }

    Studentas naujasStudentas(vardas, pavarde, pazymiai, egzaminas, skaiciavimoStrategija);
    return naujasStudentas;
}

void rusiavimasStudentu(vector<Studentas>& studentuGrupe, vector<Studentas>& vargsiukai, vector<Studentas>& kietiakiai) {
    for (const auto& studentas : studentuGrupe) {
        if (studentas.gautiGalutiniBala() < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }

    sort(vargsiukai.begin(), vargsiukai.end(), [](const Studentas& a, const Studentas& b) {
        return a.gautiGalutiniBala() > b.gautiGalutiniBala();
        });

    sort(kietiakiai.begin(), kietiakiai.end(), [](const Studentas& a, const Studentas& b) {
        return a.gautiGalutiniBala() > b.gautiGalutiniBala();
        });
}

void isvedimasIFailus(const vector<Studentas>& vargsiukai, const vector<Studentas>& kietiakiai) {
    ofstream vargsiukuFailas("vargsiukai.txt");
    ofstream kietiakiuFailas("kietiakiai.txt");

    vargsiukuFailas << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis balas" << endl;
    vargsiukuFailas << "--------------------------------------------------" << endl;

    kietiakiuFailas << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis balas" << endl;
    kietiakiuFailas << "--------------------------------------------------" << endl;

    for (const auto& studentas : vargsiukai) {
        vargsiukuFailas << left << setw(15) << studentas.gautiVarda()
            << setw(15) << studentas.gautiPavarde()
            << right << setw(20) << fixed << setprecision(2) << studentas.gautiGalutiniBala()
            << endl;
    }

    for (const auto& studentas : kietiakiai) {
        kietiakiuFailas << left << setw(15) << studentas.gautiVarda()
            << setw(15) << studentas.gautiPavarde()
            << right << setw(20) << fixed << setprecision(2) << studentas.gautiGalutiniBala()
            << endl;
    }

    vargsiukuFailas.close();
    kietiakiuFailas.close();

    cout << "Is viso studentu: " << vargsiukai.size() + kietiakiai.size() << endl;
    cout << "Vargsiukai: " << vargsiukai.size() << ", Kietiakiai: " << kietiakiai.size() << endl;
}

int main() {
    vector<Studentas> studentuGrupe;
    string eilute;
    int pasirinkimas = 0;

    cout << "Pasirinkite, koki faila norite sugeneruoti:\n";
    cout << "1 - 1000 studentu\n";
    cout << "2 - 10000 studentu\n";
    cout << "3 - 100000 studentu\n";
    cout << "4 - 1000000 studentu\n";
    cout << "5 - 10000000 studentu\n";
    cout << "Iveskite pasirinkima (1-5): ";
    cin >> pasirinkimas;

    int irasuKiekis = 0;
    string failoPavadinimas;
    switch (pasirinkimas) {
    case 1:
        irasuKiekis = 1000;
        failoPavadinimas = "studentai_1000.txt";
        break;
    case 2:
        irasuKiekis = 10000;
        failoPavadinimas = "studentai_10000.txt";
        break;
    case 3:
        irasuKiekis = 100000;
        failoPavadinimas = "studentai_100000.txt";
        break;
    case 4:
        irasuKiekis = 1000000;
        failoPavadinimas = "studentai_1000000.txt";
        break;
    case 5:
        irasuKiekis = 10000000;
        failoPavadinimas = "studentai_10000000.txt";
        break;
    default:
        cout << "Neteisingas pasirinkimas, generuojama 1000 studentu." << endl;
        irasuKiekis = 1000;
        failoPavadinimas = "studentai_1000.txt";
        break;
    }

    auto start_nuskaitymas = std::chrono::high_resolution_clock::now();

    ifstream failas(failoPavadinimas);
    if (failas.is_open()) {
        getline(failas, eilute);
        while (getline(failas, eilute)) {
            string vardas, pavarde;
            vector<int> pazymiai;
            int egzaminas;

            istringstream iss(eilute);
            iss >> vardas >> pavarde;

            int pazymys;
            while (iss >> pazymys) {
                pazymiai.push_back(pazymys);
            }

            egzaminas = pazymiai.back();
            pazymiai.pop_back();

            Studentas naujasStudentas(vardas, pavarde, pazymiai, egzaminas, 'v');
            studentuGrupe.push_back(naujasStudentas);
        }
        failas.close();
    }
    else {
        cout << "Nepavyko atidaryti failo " << failoPavadinimas << endl;
    }

    auto end_nuskaitymas = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trukme_nuskaitymas = end_nuskaitymas - start_nuskaitymas;
    cout << "Duomenu nuskaitymo trukme: " << trukme_nuskaitymas.count() << " sekundziu\n";

    char ivestiNauja;
    cout << "Ar norite ivesti nauja studenta? (y/n): ";
    cin >> ivestiNauja;

    if (ivestiNauja == 'y' || ivestiNauja == 'Y') {
        Studentas naujasStudentas = ivestiNaujaStudenta();
        studentuGrupe.push_back(naujasStudentas);
    }

    auto start_rusiavimas = std::chrono::high_resolution_clock::now();

    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;
    rusiavimasStudentu(studentuGrupe, vargsiukai, kietiakiai);

    auto end_rusiavimas = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trukme_rusiavimas = end_rusiavimas - start_rusiavimas;
    cout << "Studentu rusiavimo trukme: " << trukme_rusiavimas.count() << " sekundziu\n";

    auto start_isvedimas = std::chrono::high_resolution_clock::now();

    isvedimasIFailus(vargsiukai, kietiakiai);

    auto end_isvedimas = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trukme_isvedimas = end_isvedimas - start_isvedimas;
    cout << "Duomenu isvedimo i failus trukme: " << trukme_isvedimas.count() << " sekundziu\n";

    return 0;
}

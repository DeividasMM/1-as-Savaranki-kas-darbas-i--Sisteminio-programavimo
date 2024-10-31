#include "mylib.h"

template <typename Container>
void sortContainer(Container& container) {
    sort(container.begin(), container.end(), [](const Studentas& a, const Studentas& b) {
        return a.gautiGalutiniBala() > b.gautiGalutiniBala();
        });
}

template <typename Container>
void rusiavimasStudentu(Container& studentuGrupe, Container& vargsiukai, Container& kietiakiai) {
    for (const auto& studentas : studentuGrupe) {
        if (studentas.gautiGalutiniBala() < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }

    sortContainer(vargsiukai);
    sortContainer(kietiakiai);
}

template <typename Container>
void isvedimasIFailus(const Container& vargsiukai, const Container& kietiakiai) {
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

template <typename Container>
void runProgram() {
    Container studentuGrupe;
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
        Studentas naujasStudentas = Studentas::ivestiNaujaStudenta();
        studentuGrupe.push_back(naujasStudentas);
    }

    auto start_rusiavimas = std::chrono::high_resolution_clock::now();

    Container vargsiukai;
    Container kietiakiai;
    rusiavimasStudentu(studentuGrupe, vargsiukai, kietiakiai);

    auto end_rusiavimas = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trukme_rusiavimas = end_rusiavimas - start_rusiavimas;
    cout << "Studentu rusiavimo trukme: " << trukme_rusiavimas.count() << " sekundziu\n";

    auto start_isvedimas = std::chrono::high_resolution_clock::now();

    isvedimasIFailus(vargsiukai, kietiakiai);

    auto end_isvedimas = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trukme_isvedimas = end_isvedimas - start_isvedimas;
    cout << "Duomenu isvedimo i failus trukme: " << trukme_isvedimas.count() << " sekundziu\n";
}

int main() {
    cout << "Koki konteineri noretumete patikrinti, Vector, List, Deque: ";
    string containerChoice;
    cin >> containerChoice;

    if (containerChoice == "Vector" || containerChoice == "vector") {
        runProgram<vector<Studentas>>();
    }
    else if (containerChoice == "List" || containerChoice == "list") {
        runProgram<list<Studentas>>();
    }
    else if (containerChoice == "Deque" || containerChoice == "deque") {
        runProgram<deque<Studentas>>();
    }
    else {
        cout << "Neteisingas pasirinkimas, naudojamas vector" << endl;
        runProgram<vector<Studentas>>();
    }

    return 0;
}

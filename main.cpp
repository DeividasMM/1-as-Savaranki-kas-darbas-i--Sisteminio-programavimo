#include "mylib.h"

bool compareByFinalScore(const Studentas& a, const Studentas& b) {
    return a.gautiGalutiniBala() < b.gautiGalutiniBala();
}

int main() {

    char skaiciavimoStrategija = 'v';
    string failoPavadinimas;

    cout << "Pasirinkite studentu faila (1k, 10k, 100k, 1M, 10M): ";
    string pasirinkimas;
    cin >> pasirinkimas;
    if (pasirinkimas == "1k") failoPavadinimas = "studentai1000.txt";
    else if (pasirinkimas == "10k") failoPavadinimas = "studentai10000.txt";
    else if (pasirinkimas == "100k") failoPavadinimas = "studentai100000.txt";
    else if (pasirinkimas == "1M") failoPavadinimas = "studentai1000000.txt";
    else if (pasirinkimas == "10M") failoPavadinimas = "studentai10000000.txt";
    else {
        cout << "Neteisingas pasirinkimas. Naudojamas 1k failas." << endl;
        failoPavadinimas = "studentai1000.txt";
    }

    cout << "Kaip skaiciuoti galutini bala? (v - vidurkis, m - mediana): ";
    cin >> skaiciavimoStrategija;

    if (skaiciavimoStrategija != 'v' && skaiciavimoStrategija != 'm') {
        cout << "Neteisinga strategija. Naudojamas vidurkis (v)." << endl;
        skaiciavimoStrategija = 'v';
    }

    auto startRead = high_resolution_clock::now();

    vector<Studentas> studentuGrupe;
    string eilute;

    ifstream failas(failoPavadinimas);
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
            if (skaiciavimoStrategija == 'v') {
                naujasStudentas.skaiciuotiGalutiniVidurki();
            }
            else {
                naujasStudentas.skaiciuotiGalutiniMediana();
            }

            studentuGrupe.push_back(naujasStudentas);
        }

        failas.close();

        cout << studentuGrupe.size() << " studentai nuskaityti." << endl;

    }
    catch (const exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
        return 1;
    }

    auto endRead = high_resolution_clock::now();
    auto readDuration = duration<double>(endRead - startRead).count();
    cout << "Failo nuskaitymas uztruko: " << readDuration << " sec" << endl;

    auto startSort = high_resolution_clock::now();

    sort(studentuGrupe.begin(), studentuGrupe.end(), compareByFinalScore);

    auto endSort = high_resolution_clock::now();
    auto sortDuration = duration<double>(endSort - startSort).count();
    cout << "Rusiavimas uztruko: " << sortDuration << " sec" << endl;

    auto startWrite = high_resolution_clock::now();

    ofstream vargsiukuFailas("vargsiukai.txt", ios::app);
    ofstream kietiakuFailas("kietiakiai.txt", ios::app);

    for (const auto& studentas : studentuGrupe) {
        if (studentas.gautiGalutiniBala() < 5.0) {
            vargsiukuFailas << studentas << endl;
        }
        else {
            kietiakuFailas << studentas << endl;
        }
    }

    vargsiukuFailas.close();
    kietiakuFailas.close();

    auto endWrite = high_resolution_clock::now();
    auto writeDuration = duration<double>(endWrite - startWrite).count();
    cout << "Isvedimas i failus uztruko: " << writeDuration << " sec" << endl;

    cout << "Vargsiukai isvesti i 'vargsiukai.txt'. Kietiakiai isvesti i 'kietiakiai.txt'." << endl;

    cout << "\nAr norite ivesti nauja studenta? (taip/ne): ";
    string atsakymas;
    cin >> atsakymas;

    if (atsakymas == "taip") {

        string vardas, pavarde;
        vector<int> pazymiai;
        int egzaminas;

        cout << "Iveskite naujo studento varda, pavarde, pazymius (suvesti 0 kad baigti):" << endl;
        cin >> vardas >> pavarde;

        int pazymys;
        while (true) {
            cin >> pazymys;
            if (pazymys == 0) break;
            pazymiai.push_back(pazymys);
        }

        egzaminas = pazymiai.back();
        pazymiai.pop_back();

        Studentas naujasStudentas(vardas, pavarde, pazymiai, egzaminas, skaiciavimoStrategija);
        if (skaiciavimoStrategija == 'v') {
            naujasStudentas.skaiciuotiGalutiniVidurki();
        }
        else {
            naujasStudentas.skaiciuotiGalutiniMediana();
        }

        if (naujasStudentas.gautiGalutiniBala() < 5.0) {
            ofstream vargsiukuFailas("vargsiukai.txt", ios::app);
            vargsiukuFailas << naujasStudentas << endl;
            vargsiukuFailas.close();
            cout << "Naujas studentas priskirtas 'vargsiukai.txt'." << endl;
        }
        else {
            ofstream kietiakuFailas("kietiakiai.txt", ios::app);
            kietiakuFailas << naujasStudentas << endl;
            kietiakuFailas.close();
            cout << "Naujas studentas priskirtas 'kietiakiai.txt'." << endl;
        }
    }

    return 0;
}

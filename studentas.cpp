#include "mylib.h"


Studentas::Studentas() {
    srand(time(0));

    cout << "Iveskite studento pavarde: "; cin >> pavarde;
    cout << "Iveskite studento varda: "; cin >> vardas;
    cout << "Kiek pazymiu buvo semestre? ";
    int pazymiuKiekis; cin >> pazymiuKiekis;

    for (int i = 0; i < pazymiuKiekis; i++) {
        int pazymys = rand() % 10 + 1;
        pazymiai.push_back(pazymys);
    }

    egzaminas = rand() % 10 + 1;

}

Studentas::Studentas(string vardas, string pavarde, vector<int> pazymiai, int egzaminas, char strategija)
    : vardas(vardas), pavarde(pavarde), pazymiai(pazymiai), egzaminas(egzaminas), skaiciavimoStrategija(strategija) {
    if (skaiciavimoStrategija == 'm') {
        skaiciuotiGalutiniMediana();
    }
    else {
        skaiciuotiGalutiniVidurki();
    }
}

Studentas::Studentas(const Studentas& temp)
    : vardas(temp.vardas), pavarde(temp.pavarde), pazymiai(temp.pazymiai), egzaminas(temp.egzaminas), skaiciavimoStrategija(temp.skaiciavimoStrategija) {
    if (skaiciavimoStrategija == 'm') {
        skaiciuotiGalutiniMediana();
    }
    else {
        skaiciuotiGalutiniVidurki();
    }
}

Studentas& Studentas::operator=(const Studentas& temp) {
    if (this == &temp) return *this;
    vardas = temp.vardas;
    pavarde = temp.pavarde;
    pazymiai = temp.pazymiai;
    egzaminas = temp.egzaminas;
    skaiciavimoStrategija = temp.skaiciavimoStrategija;

    if (skaiciavimoStrategija == 'm') {
        skaiciuotiGalutiniMediana();
    }
    else {
        skaiciuotiGalutiniVidurki();
    }
    return *this;
}

Studentas::~Studentas() {
    vardas.clear();
    pavarde.clear();
    pazymiai.clear();
}

void Studentas::spausdinti() {
    printf("|%-20s|%-20s|", pavarde.c_str(), vardas.c_str());
    for (auto& pazymys : pazymiai) printf("%3d|", pazymys);
    printf("%10d|", egzaminas);
}

void Studentas::spausdintiGalutiniBala() {
    printf("|%-20s|%-20s|%20.2f|", pavarde.c_str(), vardas.c_str(), galutinisBalas);
}

void Studentas::skaiciuotiGalutiniVidurki() {
    float suma = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0f);
    galutinisBalas = (suma / pazymiai.size()) * 0.4f + egzaminas * 0.6f;
}

void Studentas::skaiciuotiGalutiniMediana() {
    galutinisBalas = skaiciuotiMediana(pazymiai) * 0.4f + egzaminas * 0.6f;
}

double Studentas::skaiciuotiMediana(vector<int> vec) {
    if (vec.empty())
        throw domain_error("Negalima skaiciuoti medianos tusciam vektoriui");
    sort(vec.begin(), vec.end());
    size_t vid = vec.size() / 2;
    return vec.size() % 2 == 0 ? (vec[vid] + vec[vid - 1]) / 2.0 : vec[vid];
}

istream& operator>>(istream& input, Studentas& studentas) {
    input >> studentas.pavarde >> studentas.vardas;
    int n;
    input >> n;
    studentas.pazymiai.resize(n);
    for (int& paz : studentas.pazymiai) input >> paz;
    input >> studentas.egzaminas;

    return input;
}

ostream& operator<<(ostream& output, const Studentas& studentas) {
    output << "Vardas: " << studentas.gautiVarda() << endl;
    output << "Pavarde: " << studentas.gautiPavarde() << endl;
    output << "Pazymiai: ";
    for (const auto& paz : studentas.gautiPazymius()) output << paz << " ";
    output << endl;
    output << "Egzaminino pazymys: " << studentas.gautiEgzaminoBala() << endl;
    output << "Galutinis balas: " << fixed << setprecision(2) << studentas.gautiGalutiniBala() << endl;
    return output;
}

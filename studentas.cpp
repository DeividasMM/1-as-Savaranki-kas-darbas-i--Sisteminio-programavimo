#include "mylib.h"

// Konstruktorius be parametrų
Studentas::Studentas() {
    srand(time(0));//random skaiciu generatorius

    cout << "Iveskite studento pavarde: "; cin >> pavarde;
    cout << "Iveskite studento varda: "; cin >> vardas;
    cout << "Kiek pazymiu buvo semestre? ";
    int pazymiuKiekis; cin >> pazymiuKiekis;

    for (int i = 0; i < pazymiuKiekis; i++) {
        int pazymys = rand() % 10 + 1; // Random pazymys tarp 1 ir 10
        pazymiai.push_back(pazymys);
    }

    egzaminas = rand() % 10 + 1; // Random egzaminas tarp 1 ir 10
    skaiciavimoStrategija == 'm' ? skaiciuotiGalutiniMediana() : skaiciuotiGalutiniVidurki();
}

// Konstruktorius su parametrais
Studentas::Studentas(string vardas, string pavarde, vector<int> pazymiai, int egzaminas)
    : vardas(vardas), pavarde(pavarde), pazymiai(pazymiai), egzaminas(egzaminas) {
    skaiciavimoStrategija == 'm' ? skaiciuotiGalutiniMediana() : skaiciuotiGalutiniVidurki();
}

// Kopijavimo konstruktorius
Studentas::Studentas(const Studentas& temp)
    : vardas(temp.vardas), pavarde(temp.pavarde), pazymiai(temp.pazymiai), egzaminas(temp.egzaminas) {
    skaiciavimoStrategija == 'm' ? skaiciuotiGalutiniMediana() : skaiciuotiGalutiniVidurki();
}

// Kopijavimo priskyrimo operatorius
Studentas& Studentas::operator=(const Studentas& temp) {
    if (this == &temp) return *this;
    vardas = temp.vardas; pavarde = temp.pavarde;
    pazymiai = temp.pazymiai; egzaminas = temp.egzaminas;
    skaiciavimoStrategija == 'm' ? skaiciuotiGalutiniMediana() : skaiciuotiGalutiniVidurki();
    return *this;
}

// Destruktorius
Studentas::~Studentas() {
    vardas.clear(); pavarde.clear(); pazymiai.clear();
}

// Išvedimas be galutinio balo
void Studentas::spausdinti() {
    printf("|%-20s|%-20s|", pavarde.c_str(), vardas.c_str());
    for (auto& pazymys : pazymiai) printf("%3d|", pazymys);
    printf("%10d|", egzaminas);
}

// Išvedimas su galutiniu balu
void Studentas::spausdintiGalutiniBala() {
    printf("|%-20s|%-20s|%20.2f|", pavarde.c_str(), vardas.c_str(), galutinisBalas);
}

// Galutinio balo skaičiavimas pagal vidurkį
void Studentas::skaiciuotiGalutiniVidurki() {
    float suma = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0);
    galutinisBalas = suma / pazymiai.size() * 0.4 + egzaminas * 0.6;
}

// Galutinio balo skaičiavimas pagal medianą
void Studentas::skaiciuotiGalutiniMediana() {
    galutinisBalas = skaiciuotiMediana(pazymiai) * 0.4 + egzaminas * 0.6;
}

// Medianos skaičiavimas
double Studentas::skaiciuotiMediana(vector<int> vec) {
    if (vec.empty())
        throw std::domain_error("Negalima skaiciuoti medianos tusciam vektoriui");
    sort(vec.begin(), vec.end());
    size_t vid = vec.size() / 2;
    return vec.size() % 2 == 0 ? (vec[vid] + vec[vid - 1]) / 2.0 : vec[vid];
}

// Perdengtas cin
void Studentas::operator>>(std::istream& input) {
    input >> pavarde >> vardas;
    int n; input >> n;
    pazymiai.resize(n);
    for (int& paz : pazymiai) input >> paz;
    input >> egzaminas;
    skaiciavimoStrategija == 'm' ? skaiciuotiGalutiniMediana() : skaiciuotiGalutiniVidurki();
}

// Perdengtas cout
void Studentas::operator<<(std::ostream& output) {
    output << "Vardas: " << vardas << endl;
    output << "Pavarde: " << pavarde << endl;
    output << "Pazymiai: ";
    for (const auto& paz : pazymiai) output << paz << " ";
    output << endl;
    output << "Egzamino pazymys: " << egzaminas << endl;
    output << "Galutinis balas: " << fixed << setprecision(2) << galutinisBalas << endl;
}

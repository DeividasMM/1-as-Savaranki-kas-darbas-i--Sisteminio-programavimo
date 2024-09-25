#include "mylib.h"

// Konstruktorius be parametrų
Studentas::Studentas() {
    cout << "Iveskite studento pavarde: "; cin >> pavarde;
    cout << "Iveskite studento varda: "; cin >> vardas;
    cout << "Kiek pazymiu buvo semestre? ";
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        int k;
        cout << "Ivesk " << i + 1 << " semestro pazymi: "; cin >> k; nd_paz.push_back(k);
    }

    cout << "Iveskite egzamino pazymi: "; cin >> egzaminas;
    skaiciavimas == 'm' ? galutinis_med() : galutinis_vid();
}

// Konstruktorius su parametrais
Studentas::Studentas(string Vard, string Pavard, vector<int> nd, int Egz)
    : vardas(Vard), pavarde(Pavard), nd_paz(nd), egzaminas(Egz) {
    skaiciavimas == 'm' ? galutinis_med() : galutinis_vid();
}

// Kopijavimo konstruktorius
Studentas::Studentas(const Studentas& temp)
    : vardas(temp.vardas), pavarde(temp.pavarde), nd_paz(temp.nd_paz), egzaminas(temp.egzaminas) {
    skaiciavimas == 'm' ? galutinis_med() : galutinis_vid();
}

// Kopijavimo priskyrimo operatorius
Studentas& Studentas::operator=(const Studentas& temp) {
    if (this == &temp) return *this;
    vardas = temp.vardas; pavarde = temp.pavarde;
    nd_paz = temp.nd_paz; egzaminas = temp.egzaminas;
    skaiciavimas == 'm' ? galutinis_med() : galutinis_vid();
    return *this;
}

// Destruktorius
Studentas::~Studentas() {
    vardas.clear(); pavarde.clear(); nd_paz.clear();
}

// Išvedimas be galutinio balo
void Studentas::print() {
    printf("|%-20s|%-20s|", pavarde.c_str(), vardas.c_str());
    for (auto& pazymys : nd_paz) printf("%3d|", pazymys);
    printf("%10d|\n", egzaminas);
}

// Išvedimas su galutiniu balu
void Studentas::print_galutinis() {
    printf("|%-20s|%-20s|%20.2f|\n", pavarde.c_str(), vardas.c_str(), galutinis);
}

// Galutinio balo skaičiavimas pagal vidurkį
void Studentas::galutinis_vid() {
    float suma = std::accumulate(nd_paz.begin(), nd_paz.end(), 0.0);
    galutinis = suma / nd_paz.size() * 0.4 + egzaminas * 0.6;
}

// Galutinio balo skaičiavimas pagal medianą
void Studentas::galutinis_med() {
    galutinis = med(nd_paz) * 0.4 + egzaminas * 0.6;
}

// Medianos skaičiavimas
double Studentas::med(vector<int> vec) {
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
    nd_paz.resize(n);
    for (int& paz : nd_paz) input >> paz;
    input >> egzaminas;
    skaiciavimas == 'm' ? galutinis_med() : galutinis_vid();
}

// Perdengtas cout
void Studentas::operator<<(std::ostream& output) {
    output << "Vardas: " << vardas << endl;
    output << "Pavarde: " << pavarde << endl;
    output << "Pazymiai: ";
    for (const auto& paz : nd_paz) output << paz << " ";
    output << endl;
    output << "Egzamino pazymys: " << egzaminas << endl;
    output << "Galutinis balas: " << fixed << setprecision(2) << galutinis << endl;
}

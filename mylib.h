#ifndef mylib
#define mylib
#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::fixed;
using std::setprecision;
using std::sort;
using std::domain_error;
using std::array;
using std::setw;
using std::left;
using std::right;
using std::to_string;

// Išorinis kintamasis galutinio balo skaičiavimo pasirinkimui
extern char skaiciavimoStrategija;

// Studentas klasės aprašymas
class Studentas {
    string vardas, pavarde;
    vector<int> pazymiai;
    int egzaminas;
    float galutinisBalas;

public:
    Studentas();  // Konstruktorius be parametru
    Studentas(string vardas, string pavarde, vector<int> pazymiai, int egzaminas); // Konstruktorius su parametrais
    Studentas(const Studentas& temp); // Kopijavimo konstruktorius
    Studentas& operator=(const Studentas& temp); // Kopijavimo priskyrimo operatorius
    ~Studentas(); // Destruktorius

    void spausdinti();
    void spausdintiGalutiniBala(); // Išvedimas su galutiniu balu

    void skaiciuotiGalutiniVidurki(); // Metodas skaičiuojantis galutinį pažymį pagal vidurkį
    void skaiciuotiGalutiniMediana(); // Metodas skaičiuojantis galutinį pažymį pagal medianą

    double skaiciuotiMediana(vector<int> vec); // Funkcija skaičiuojanti medianą

    void operator>>(std::istream& input);  // Perdenčia cin operatorių
    void operator<<(std::ostream& output); // Perdenčia cout operatorių

    // Getteriai, pažymėti kaip const
    inline string gautiVarda() const { return vardas; }
    inline string gautiPavarde() const { return pavarde; }
    inline vector<int> gautiPazymius() const { return pazymiai; }
    inline int gautiEgzaminoBala() const { return egzaminas; }
    inline float gautiGalutiniBalaVidurkis() const { return galutinisBalas; }
    inline float gautiGalutiniBalaMediana() const { return galutinisBalas; }
    inline int gautiPazymiuKieki() const { return pazymiai.size(); }
};

#endif

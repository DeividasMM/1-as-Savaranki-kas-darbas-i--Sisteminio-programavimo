#ifndef mylib
#define mylib

#include <iostream>
#include <numeric>
#include <string>
#include <array>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::array;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::sort;
using std::domain_error;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::istream;
using std::ostream;
using std::istringstream;
using std::runtime_error;
using std::to_string;

class Studentas {
    string vardas, pavarde;
    vector<int> pazymiai;
    int egzaminas;
    float galutinisBalas;
    char skaiciavimoStrategija;

public:

    Studentas();
    Studentas(string vardas, string pavarde, vector<int> pazymiai, int egzaminas, char strategija);
    Studentas(const Studentas& temp);
    Studentas& operator=(const Studentas& temp);
    ~Studentas();

    void spausdinti();
    void spausdintiGalutiniBala();

    void skaiciuotiGalutiniVidurki();
    void skaiciuotiGalutiniMediana();
    double skaiciuotiMediana(vector<int> vec);

    inline string gautiVarda() const { return vardas; }
    inline string gautiPavarde() const { return pavarde; }
    inline vector<int> gautiPazymius() const { return pazymiai; }
    inline int gautiEgzaminoBala() const { return egzaminas; }
    inline float gautiGalutiniBala() const { return galutinisBalas; }
    inline char gautiSkaiciavimoStrategija() const { return skaiciavimoStrategija; }

    inline int gautiPazymiuKieki() const { return pazymiai.size(); }

    inline float gautiGalutiniBalaVidurkis() const { return galutinisBalas; }
    inline float gautiGalutiniBalaMediana() const { return galutinisBalas; }

    inline void nustatytiSkaiciavimoStrategija(char strategija) { skaiciavimoStrategija = strategija; }

    friend istream& operator>>(istream& input, Studentas& studentas);
    friend ostream& operator<<(ostream& output, const Studentas& studentas);
};

#endif

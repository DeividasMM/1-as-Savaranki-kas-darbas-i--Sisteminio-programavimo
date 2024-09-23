#ifndef mylib
#define mylib

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

// Išorinis kintamasis galutinio balo skaičiavimo pasirinkimui
extern char skaiciavimas;

// Studentas klasės aprašymas
class Studentas {
    string vardas, pavarde;
    vector<int> nd_paz;
    int egzaminas;
    float galutinis;

public:
    Studentas();  // Konstruktorius be parametru
    Studentas(string vardas, string pavarde, vector<int> nd_paz, int egzaminas); // Konstruktorius su parametrais
    Studentas(const Studentas& temp); // Kopijavimo konstruktorius
    Studentas& operator=(const Studentas& temp); // Kopijavimo priskyrimo operatorius
    ~Studentas(); // Destruktorius

    void print();
    void print_galutinis();
    void galutinis_vid();
    void galutinis_med();

    void operator>>(std::istream& input);
    void operator<<(std::ostream& out);

    double med(vector<int> vector);

    inline string getVardas() { return vardas; }
    inline int getPazNr() { return nd_paz.size(); }
    inline void setVardas(string t) { vardas = t; }
};

#endif

#pragma once
#include <string>
#include <vector>
#include <iostream>

class Studentas {
private:
    std::string name;
    std::string surname;

    // C dinaminis masyvas (dėl užduoties reikalavimo)
    int* ndC;
    int ndCount;

    // Pagrindinis saugojimas (vektorinė versija)
    std::vector<int> nd;

    int egz;
    double galVid;
    double galMed;

public:
    // Konstruktoriai
    Studentas();
    Studentas(const std::string& n, const std::string& s);

    // Rule of three
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    ~Studentas();

    // Set
    void setName(const std::string& n) { name = n; }
    void setSurname(const std::string& s) { surname = s; }
    void setEgz(int e) { egz = e; }

    // Get
    const std::string& getName() const { return name; }
    const std::string& getSurname() const { return surname; }
    double getGalVid() const { return galVid; }
    double getGalMed() const { return galMed; }

    // ND valdymas
    void clearND();
    void addND(int x);
    void syncCArrayFromVector();

    // Skaičiavimai
    void skaiciuotiGalutinius();

    // Operatoriai (rankiniam įvedimui, jei prireiks)
    friend std::istream& operator>>(std::istream& in, Studentas& s);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s);
};

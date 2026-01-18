#pragma once
#include <string>
#include <vector>
#include <iostream>

class Studentas {
private:
    std::string name_;
    std::string surname_;

    int* ndC_;
    int ndCountC_;

    std::vector<int> ndV_;

    int egz_;
    double galVid_;
    double galMed_;

    void pushBackC(int x);

public:
    Studentas();
    Studentas(const std::string& n, const std::string& s);

    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    ~Studentas();

    void setName(const std::string& n);
    void setSurname(const std::string& s);
    void setEgz(int e);

    const std::string& getName() const;
    const std::string& getSurname() const;
    double getGalVid() const;
    double getGalMed() const;

    void clearAll();

    void addNDVector(int x);
    void addNDCArray(int x);

    void syncCFromVector();
    void syncVectorFromC();

    void skaiciuotiGalutinius();

    friend std::istream& operator>>(std::istream& in, Studentas& s);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s);
};

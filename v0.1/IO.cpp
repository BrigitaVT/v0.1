#include "IO.h"
#include <fstream>
#include <iomanip>
#include <random>
#include <stdexcept>
#include <iostream>

std::vector<Studentas> nuskaitytiIsFailo(const std::string& f) {
    std::ifstream in(f);
    if (!in) throw std::runtime_error("Nepavyko atidaryti failo: " + f);

    std::string tmp;
    std::getline(in, tmp);

    std::vector<Studentas> v;
    v.reserve(10000);

    std::string vardas, pavarde;
    long long count = 0;

    while (in >> vardas >> pavarde) {
        Studentas s;
        s.setName(vardas);
        s.setSurname(pavarde);

        std::vector<int> paz;
        paz.reserve(32);

        int x;
        while (in >> x) {
            paz.push_back(x);
            if (in.peek() == '\n' || in.peek() == '\r') break;
        }

        if (paz.size() < 2) throw std::runtime_error("Bloga eilute faile: " + vardas + " " + pavarde);

        s.setEgz(paz.back());
        paz.pop_back();

        for (int n : paz) s.addNDVector(n);

        s.syncCFromVector();
        s.skaiciuotiGalutinius();

        v.push_back(s);

        count++;
        if (count % 100000 == 0) {
            std::cout << "Nuskaityta: " << count << " eiluciu\n";
        }
    }

    return v;
}

Studentas generuotiAtsitiktini(const std::string& vrd, const std::string& pvd, int n) {
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution<> d(1, 10);

    Studentas s;
    s.setName(vrd);
    s.setSurname(pvd);

    for (int i = 0; i < n; i++) s.addNDCArray(d(g));
    s.syncVectorFromC();

    s.setEgz(d(g));
    s.skaiciuotiGalutinius();
    return s;
}

void spausdinti(const std::vector<Studentas>& v, bool vid, bool med, int k) {
    std::cout << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas";
    if (vid) std::cout << std::setw(15) << "Gal(Vid)";
    if (med) std::cout << std::setw(15) << "Gal(Med)";
    std::cout << "\n";

    int limit = k;
    if (limit > (int)v.size()) limit = (int)v.size();

    for (int i = 0; i < limit; i++) {
        std::cout << std::setw(15) << v[i].getSurname()
            << std::setw(15) << v[i].getName();
        if (vid) std::cout << std::setw(15) << std::fixed << std::setprecision(2) << v[i].getGalVid();
        if (med) std::cout << std::setw(15) << std::fixed << std::setprecision(2) << v[i].getGalMed();
        std::cout << "\n";
    }

    if ((int)v.size() > limit) {
        std::cout << "... viso: " << v.size() << ", parodyta: " << limit << "\n";
    }
}

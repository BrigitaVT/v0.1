#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include "Studentas.h"

// Nuskaito: Vardas Pavarde ND... Egz (paskutinis skaičius laikomas egz)
static std::vector<Studentas> nuskaitytiIsFailo(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) throw std::runtime_error("Nepavyko atidaryti failo: " + filename);

    std::string header;
    std::getline(fin, header); // praleidziam antrašte

    std::vector<Studentas> v;
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);

        std::string vardas, pavarde;
        iss >> vardas >> pavarde;
        if (!iss) continue;

        std::vector<int> paz;
        int x;
        while (iss >> x) paz.push_back(x);

        if (paz.size() < 2) {
            throw std::runtime_error("Bloga eilute (truksta pazymiu): " + line);
        }

        int egz = paz.back();
        paz.pop_back();

        Studentas s;
        s.setName(vardas);
        s.setSurname(pavarde);

        s.clearND();
        for (int nd : paz) s.addND(nd);
        s.setEgz(egz);

        s.syncCArrayFromVector(); // del reikalavimo (C masyvas)
        s.skaiciuotiGalutinius();

        v.push_back(s);
    }

    return v;
}

static void spausdintiLentele(const std::vector<Studentas>& v, bool showVid, bool showMed, size_t kiekRodyti) {
    std::cout << std::left
        << std::setw(18) << "Pavarde"
        << std::setw(18) << "Vardas";
    if (showVid) std::cout << std::setw(20) << "Galutinis (Vid.)";
    if (showMed) std::cout << std::setw(20) << "Galutinis (Med.)";
    std::cout << "\n";

    std::cout << std::string(18 + 18 + (showVid ? 20 : 0) + (showMed ? 20 : 0), '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);

    size_t limit = std::min(kiekRodyti, v.size());
    for (size_t i = 0; i < limit; i++) {
        const auto& s = v[i];
        std::cout << std::setw(18) << s.getSurname()
            << std::setw(18) << s.getName();
        if (showVid) std::cout << std::setw(20) << s.getGalVid();
        if (showMed) std::cout << std::setw(20) << s.getGalMed();
        std::cout << "\n";
    }

    if (v.size() > limit) {
        std::cout << "\n... (viso studentu: " << v.size()
            << ", parodyta: " << limit << ")\n";
    }
}

int main() {
    try {
        std::cout << "Pasirink faila:\n";
        std::cout << "1 - studentai10000.txt\n";
        std::cout << "2 - studentai100000.txt\n";
        std::cout << "3 - studentai1000000.txt\n";
        std::cout << "Pasirinkimas: ";

        int f;
        std::cin >> f;

        std::string filename;
        if (f == 1) filename = "studentai10000.txt";
        else if (f == 2) filename = "studentai100000.txt";
        else if (f == 3) filename = "studentai1000000.txt";
        else throw std::runtime_error("Neteisingas pasirinkimas.");

        std::cout << "Skaičiuoti pagal:\n1 - Vidurki\n2 - Mediana\n3 - Abu\nPasirink: ";
        int mode;
        std::cin >> mode;

        bool showVid = (mode == 1 || mode == 3);
        bool showMed = (mode == 2 || mode == 3);

        std::vector<Studentas> v = nuskaitytiIsFailo(filename);

        std::sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b) {
            if (a.getSurname() == b.getSurname()) return a.getName() < b.getName();
            return a.getSurname() < b.getSurname();
            });

        std::cout << "\nParodyti kiek eiluciu ekrane? (pvz 20): ";
        size_t kiek;
        std::cin >> kiek;

        std::cout << "\n";
        spausdintiLentele(v, showVid, showMed, kiek);
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

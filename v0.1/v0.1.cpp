#include "IO.h"
#include <algorithm>
#include <iostream>

int main() {
    try {
        std::cout << "========== MENIU ==========\n";
        std::cout << "1 - Ivesti studentus ranka (per klaviatura)\n";
        std::cout << "2 - Generuoti studentus atsitiktinai\n";
        std::cout << "3 - Nuskaityti studentus is failo\n";
        std::cout << "===========================\n";
        std::cout << "Ivesk meniu pasirinkima (1-3): ";

        int m;
        std::cin >> m;

        std::cout << "\nPasirink galutinio balo skaiciavimo buda:\n";
        std::cout << "1 - Pagal VIDURKI\n";
        std::cout << "2 - Pagal MEDIANA\n";
        std::cout << "3 - Rodyti ABI reiksmes\n";
        std::cout << "Ivesk pasirinkima (1-3): ";

        int mode;
        std::cin >> mode;

        bool vid = (mode == 1 || mode == 3);
        bool med = (mode == 2 || mode == 3);

        std::vector<Studentas> v;

        if (m == 1) {
            int k;
            std::cout << "\nKiek studentu ivesi? ";
            std::cin >> k;

            for (int i = 0; i < k; i++) {
                std::cout << "\nStudentas #" << (i + 1) << "\n";
                std::cout << "Formatas: Vardas Pavarde ND ND ... 0 Egz\n";
                std::cout << "Pvz: Jonas Jonaitis 8 9 10 0 9\n";
                std::cout << "Ivedimas: ";

                Studentas s;
                std::cin >> s;
                s.skaiciuotiGalutinius();
                v.push_back(s);
            }
        }
        else if (m == 2) {
            int k, n;
            std::cout << "\nKiek studentu generuoti? ";
            std::cin >> k;
            std::cout << "Kiek ND kiekvienam? ";
            std::cin >> n;

            for (int i = 0; i < k; i++) {
                v.push_back(
                    generuotiAtsitiktini(
                        "Vardas" + std::to_string(i + 1),
                        "Pavarde" + std::to_string(i + 1),
                        n
                    )
                );
            }
        }
        else if (m == 3) {
            std::cout << "\nPasirink faila:\n";
            std::cout << "1 - studentai10000.txt\n";
            std::cout << "2 - studentai100000.txt\n";
            std::cout << "3 - studentai1000000.txt\n";
            std::cout << "Ivesk pasirinkima (1-3): ";

            int f;
            std::cin >> f;

            std::string filename;
            if (f == 1) filename = "studentai10000.txt";
            else if (f == 2) filename = "studentai100000.txt";
            else if (f == 3) filename = "studentai1000000.txt";
            else {
                std::cout << "Neteisingas failo pasirinkimas.\n";
                return 1;
            }

            std::cout << "\nSkaitomas failas: " << filename << "\n";
            v = nuskaitytiIsFailo(filename);
        }
        else {
            std::cout << "Neteisingas meniu pasirinkimas.\n";
            return 1;
        }

        std::sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b) {
            if (a.getSurname() == b.getSurname())
                return a.getName() < b.getName();
            return a.getSurname() < b.getSurname();
            });

        int kiek;
        std::cout << "\nKiek eiluciu rodyti ekrane? (pvz 20): ";
        std::cin >> kiek;

        std::cout << "\n";
        spausdinti(v, vid, med, kiek);
    }
    catch (...) {
        std::cout << "Ivyko klaida vykdant programa.\n";
        return 1;
    }

    return 0;
}

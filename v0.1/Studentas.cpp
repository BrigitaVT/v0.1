#include "Studentas.h"
#include <algorithm>
#include <stdexcept>

static double vidurkis(const std::vector<int>& v) {
    if (v.empty()) throw std::runtime_error("ND sąrašas tuščias (vidurkis).");
    double sum = 0.0;
    for (int x : v) sum += x;
    return sum / v.size();
}

static double mediana(std::vector<int> v) {
    if (v.empty()) throw std::runtime_error("ND sąrašas tuščias (mediana).");
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

Studentas::Studentas()
    : name(""), surname(""), ndC(nullptr), ndCount(0),
    nd(), egz(0), galVid(0.0), galMed(0.0) {
}

Studentas::Studentas(const std::string& n, const std::string& s)
    : name(n), surname(s), ndC(nullptr), ndCount(0),
    nd(), egz(0), galVid(0.0), galMed(0.0) {
}

Studentas::Studentas(const Studentas& other)
    : name(other.name), surname(other.surname),
    ndC(nullptr), ndCount(other.ndCount),
    nd(other.nd), egz(other.egz),
    galVid(other.galVid), galMed(other.galMed) {
    if (ndCount > 0) {
        ndC = new int[ndCount];
        for (int i = 0; i < ndCount; i++) ndC[i] = other.ndC[i];
    }
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this == &other) return *this;

    delete[] ndC;
    ndC = nullptr;
    ndCount = 0;

    name = other.name;
    surname = other.surname;
    nd = other.nd;
    egz = other.egz;
    galVid = other.galVid;
    galMed = other.galMed;

    ndCount = other.ndCount;
    if (ndCount > 0) {
        ndC = new int[ndCount];
        for (int i = 0; i < ndCount; i++) ndC[i] = other.ndC[i];
    }
    return *this;
}

Studentas::~Studentas() {
    delete[] ndC;
}

void Studentas::clearND() {
    nd.clear();
    delete[] ndC;
    ndC = nullptr;
    ndCount = 0;
}

void Studentas::addND(int x) {
    nd.push_back(x);
}

void Studentas::syncCArrayFromVector() {
    delete[] ndC;
    ndC = nullptr;
    ndCount = static_cast<int>(nd.size());
    if (ndCount > 0) {
        ndC = new int[ndCount];
        for (int i = 0; i < ndCount; i++) ndC[i] = nd[i];
    }
}

void Studentas::skaiciuotiGalutinius() {
    if (nd.empty()) throw std::runtime_error("Nėra ND pažymių.");
    if (egz < 1 || egz > 10) throw std::runtime_error("Egzamino pažymys neteisingas.");

    double v = vidurkis(nd);
    double m = mediana(nd);

    galVid = 0.4 * v + 0.6 * egz;
    galMed = 0.4 * m + 0.6 * egz;
}

std::istream& operator>>(std::istream& in, Studentas& s) {
    s.clearND();

    in >> s.name >> s.surname;
    if (!in) return in;

    std::cout << "Vesk ND (1-10), pabaigai 0: ";
    int x;
    while (in >> x) {
        if (x == 0) break;
        if (x < 1 || x > 10) {
            std::cout << "Blogas ND, bandyk dar: ";
            continue;
        }
        s.addND(x);
    }

    std::cout << "Vesk egzamino bala (1-10): ";
    in >> s.egz;

    s.syncCArrayFromVector();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << s.surname << " " << s.name;
    return out;
}

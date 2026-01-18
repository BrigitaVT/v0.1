#include "Studentas.h"
#include "Skaiciavimai.h"
#include <stdexcept>

Studentas::Studentas()
    : ndC_(nullptr), ndCountC_(0), egz_(0), galVid_(0), galMed_(0) {
}

Studentas::Studentas(const std::string& n, const std::string& s)
    : name_(n), surname_(s), ndC_(nullptr), ndCountC_(0),
    egz_(0), galVid_(0), galMed_(0) {
}

Studentas::Studentas(const Studentas& other)
    : name_(other.name_), surname_(other.surname_),
    ndC_(nullptr), ndCountC_(other.ndCountC_),
    ndV_(other.ndV_), egz_(other.egz_),
    galVid_(other.galVid_), galMed_(other.galMed_) {
    if (ndCountC_ > 0) {
        ndC_ = new int[ndCountC_];
        for (int i = 0; i < ndCountC_; i++) ndC_[i] = other.ndC_[i];
    }
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this == &other) return *this;
    delete[] ndC_;
    ndC_ = nullptr;
    ndCountC_ = other.ndCountC_;
    name_ = other.name_;
    surname_ = other.surname_;
    ndV_ = other.ndV_;
    egz_ = other.egz_;
    galVid_ = other.galVid_;
    galMed_ = other.galMed_;
    if (ndCountC_ > 0) {
        ndC_ = new int[ndCountC_];
        for (int i = 0; i < ndCountC_; i++) ndC_[i] = other.ndC_[i];
    }
    return *this;
}

Studentas::~Studentas() {
    delete[] ndC_;
}

void Studentas::setName(const std::string& n) { name_ = n; }
void Studentas::setSurname(const std::string& s) { surname_ = s; }
void Studentas::setEgz(int e) { egz_ = e; }

const std::string& Studentas::getName() const { return name_; }
const std::string& Studentas::getSurname() const { return surname_; }
double Studentas::getGalVid() const { return galVid_; }
double Studentas::getGalMed() const { return galMed_; }

void Studentas::clearAll() {
    ndV_.clear();
    delete[] ndC_;
    ndC_ = nullptr;
    ndCountC_ = 0;
}

void Studentas::addNDVector(int x) {
    ndV_.push_back(x);
}

void Studentas::pushBackC(int x) {
    int* temp = new int[ndCountC_ + 1];
    for (int i = 0; i < ndCountC_; i++) temp[i] = ndC_[i];
    temp[ndCountC_] = x;
    delete[] ndC_;
    ndC_ = temp;
    ndCountC_++;
}

void Studentas::addNDCArray(int x) {
    pushBackC(x);
}

void Studentas::syncCFromVector() {
    delete[] ndC_;
    ndCountC_ = ndV_.size();
    ndC_ = new int[ndCountC_];
    for (int i = 0; i < ndCountC_; i++) ndC_[i] = ndV_[i];
}

void Studentas::syncVectorFromC() {
    ndV_.clear();
    for (int i = 0; i < ndCountC_; i++) ndV_.push_back(ndC_[i]);
}

void Studentas::skaiciuotiGalutinius() {
    galVid_ = 0.4 * vidurkis(ndV_) + 0.6 * egz_;
    galMed_ = 0.4 * mediana(ndV_) + 0.6 * egz_;
}

std::istream& operator>>(std::istream& in, Studentas& s) {
    s.clearAll();
    in >> s.name_ >> s.surname_;
    int x;
    while (in >> x && x != 0) s.addNDVector(x);
    in >> s.egz_;
    s.syncCFromVector();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << s.surname_ << " " << s.name_;
    return out;
}

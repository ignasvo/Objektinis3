#include "studentas.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <algorithm>

// Default konstruktorius
Studentas::Studentas()
    : Zmogus(), nd_(), egzaminas_(0), galutinis_(0.0) {}

// Užpildytas konstruktorius
Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& nd, int egzaminas)
    : Zmogus(vardas, pavarde), nd_(nd), egzaminas_(egzaminas) {
    skaiciuotiGalutini('v');  // default 'vidurkis'
}

// Kopijavimo konstruktorius
Studentas::Studentas(const Studentas& other)
    : Zmogus(other),
      nd_(other.nd_), egzaminas_(other.egzaminas_), galutinis_(other.galutinis_) {}

// Perkėlimo konstruktorius
Studentas::Studentas(Studentas&& other) noexcept
    : Zmogus(std::move(other)),
      nd_(std::move(other.nd_)), egzaminas_(other.egzaminas_), galutinis_(other.galutinis_) {
    other.egzaminas_ = 0;
    other.galutinis_ = 0.0;
}

// Destruktorius
Studentas::~Studentas() {
    nd_.clear();
    egzaminas_ = 0;
    galutinis_ = 0.0;
}

// Copy assignment
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        Zmogus::operator=(other);
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
        galutinis_ = other.galutinis_;
    }
    return *this;
}

// Move assignment
Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        Zmogus::operator=(std::move(other));
        nd_ = std::move(other.nd_);
        egzaminas_ = other.egzaminas_;
        galutinis_ = other.galutinis_;
        other.egzaminas_ = 0;
        other.galutinis_ = 0.0;
    }
    return *this;
}

// Getteriai
double Studentas::galutinis() const { return galutinis_; }
const std::vector<int>& Studentas::nd() const { return nd_;}
int Studentas::egzaminas() const { return egzaminas_;}

// Setteriai
void Studentas::setEgzaminas(int egz) { egzaminas_ = egz; }
void Studentas::pridetiND(int nd) { nd_.push_back(nd); }

void Studentas::generuotiPazymius(int kiek) {
    nd_.clear();
    for (int i = 0; i < kiek; ++i)
        nd_.push_back(rand() % 10 + 1);
    egzaminas_ = rand() % 10 + 1;
}

void Studentas::skaiciuotiGalutini(char metodas) {
    if (nd_.empty()) {
        galutinis_ = 0.4 * 0 + 0.6 * egzaminas_;
        return;
    }

    double ndRezultatas = 0.0;
    if (metodas == 'v'|| metodas == 'V') {
        ndRezultatas = std::accumulate(nd_.begin(), nd_.end(), 0.0) / nd_.size();
    } else if (metodas == 'm'|| metodas == 'M') {
        std::sort(nd_.begin(), nd_.end());
        if (nd_.size() % 2 == 0)
            ndRezultatas = (nd_[nd_.size()/2 - 1] + nd_[nd_.size()/2]) / 2.0;
        else
            ndRezultatas = nd_[nd_.size()/2];
    } else {
        throw std::invalid_argument("Neteisingas metodas");
    }

    galutinis_ = 0.4 * ndRezultatas + 0.6 * egzaminas_;
}

std::ostream& Studentas::spausdinti(std::ostream& os) const {
    os << std::left << std::setw(15) << vardas()
       << std::setw(15) << pavarde()
       << std::fixed << std::setprecision(2)
       << galutinis_;
    return os;
}

// I/O operatoriai
std::istream& Studentas::read(std::istream& is) {
    nd_.clear();
    is >> vardas_ >> pavarde_;
    int pazymys;
    while (is >> pazymys) {
        if (pazymys < 1 || pazymys > 10) break;
        nd_.push_back(pazymys);
    }

    if (!nd_.empty()) {
        egzaminas_ = nd_.back();
        nd_.pop_back();
    } else {
        egzaminas_ = 0;
    }

    skaiciuotiGalutini('v');
    return is;
}

std::istream& operator>>(std::istream& is, Studentas& s) {
    return s.read(is);
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    s.spausdinti(os);
    return os;
}

// Palyginimo funkcijos
bool compareVardas(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}
bool comparePavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}
bool compareGalutinis(const Studentas& a, const Studentas& b) {
    return a.galutinis() < b.galutinis();
}

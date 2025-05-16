#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <ostream>
#include <iostream>
#include <string>
#include "vector.h"
#include <algorithm>
#include <numeric>
#include "zmogus.h"

class Studentas : public Zmogus {
private:
    Vector<int> nd_;
    int egzaminas_;
    double galutinis_;

public:
    Studentas(); // tuščias konstruktorius
    Studentas(const std::string& vardas, const std::string& pavarde, const Vector<int>& nd, int egzaminas);
    Studentas(const Studentas& other);            // Copy constructor
    Studentas(Studentas&& other) noexcept;        // Move constructor
    ~Studentas();                                 // Destruktorius
    Studentas& operator=(const Studentas& other); // Copy assignment
    Studentas& operator=(Studentas&& other) noexcept; // Move assignment

    // Getteriai
    int egzaminas() const;
    double galutinis() const;
    const Vector<int>& nd() const;

    // Setteriai
    void setEgzaminas(int egzaminas);
    void pridetiND(int pazymys);

    // Metodai
    void skaiciuotiGalutini(char metodas);
    void generuotiPazymius(int kiek);
    std::istream& read(std::istream& is);
    std::ostream& spausdinti(std::ostream& os) const override;

    // I/O operatoriai
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);

    // Friend funkcijos palyginimui
    friend bool compareVardas(const Studentas& a, const Studentas& b);
    friend bool comparePavarde(const Studentas& a, const Studentas& b);
    friend bool compareGalutinis(const Studentas& a, const Studentas& b);
};

// Deklaracijos palyginimui
bool compareVardas(const Studentas& a, const Studentas& b);
bool comparePavarde(const Studentas& a, const Studentas& b);
bool compareGalutinis(const Studentas& a, const Studentas& b);
#endif

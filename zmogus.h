#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() = default;
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    virtual ~Zmogus() = default;

    std::string vardas() const { return vardas_; }
    std::string pavarde() const { return pavarde_; }

    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

    virtual std::ostream& spausdinti(std::ostream& os) const = 0;
};

#endif
#include "funkcijos.h"
#include "Studentas.h"
#include "vector.h"

// Tikrinam ar vardas sudarytas tik iš raidžių
bool arTinkamasVardas(const std::string& tekstas) {
    for (char c : tekstas) {
        if (!std::isalpha(c)) return false;
    }
    return true;
}

// Tikrinam ar pažymys yra tinkamas
bool arTinkamasPazymys(int& pazymys) {
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        std::istringstream iss(input);

        if (iss >> pazymys) {
            char leftover;
            if (iss >> leftover)
                std::cout << "Klaida: netinkama ivestis. Bandykite dar karta: ";
            else if ((pazymys >= 1 && pazymys <= 10) || pazymys == -1)
                return true;
            else
                std::cout << "Klaida: skaicius turi buti nuo 1 iki 10. Bandykite dar karta: ";
        } else {
            std::cout << "Klaida: iveskite sveikaji skaiciu. Bandykite dar karta: ";
        }
    }
}

// Skaičiuojam vidurkį
double skaiciuotiVidurki(const Vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    double suma = 0;
    for (int p : pazymiai) suma += p;
    return suma / pazymiai.size();
}

// Skaičiuojam medianą
double skaiciuotiMediana(Vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    std::sort(pazymiai.begin(), pazymiai.end());
    return (pazymiai.size() % 2 == 0) ? (pazymiai[pazymiai.size()/2 - 1] + pazymiai[pazymiai.size()/2]) / 2.0 : pazymiai[pazymiai.size()/2];
}


// Funkcija: skaičiuojam galutinį balą (laisva funkcija, kviečianti klasės metodą)
void skaiciuotiGalutiniBala(Studentas& studentas, char metodas) {
    studentas.skaiciuotiGalutini(metodas);
}

// Funkcija: generuojam pažymius (laisva funkcija, kviečianti klasės metodą)
void generuotiPazymius(Studentas& studentas, int kiek) {
    studentas.generuotiPazymius(kiek);
}

// Funkcija: generuojam keletą studentų
void generuotiStudentus(Vector<Studentas>& studentai, int kiek, int ndSk) {
    Vector<std::string> vardai = {"Jonas", "Petras", "Marius", "Tomas", "Lukas", "Paulius", "Mantas", "Kazys", "Antanas", "Darius"};
    Vector<std::string> pavardes = {"Kazlauskas", "Petraitis", "Jankauskas", "Jonaitis", "Brazinskas", "Stankevicius", "Kavaliauskas", "Zukauskas", "Kavolis"};

    for (int i = 0; i < kiek; ++i) {
        Studentas s;
        s.setVardas(vardai[rand() % vardai.size()]);
        s.setPavarde(pavardes[rand() % pavardes.size()]);
        s.generuotiPazymius(ndSk);
        s.skaiciuotiGalutini('V'); // generuojant naudojam vidurkį
        studentai.push_back(s);
    }
}

void spausdintiRezultatus(const Vector<Studentas>& studentai, std::ostream& out) {
    if (studentai.empty()) {
        out << "Nera studentu duomenu.\n";
        return;
    }

    out << std::fixed << std::setprecision(2);
    out << "--------------------------------------------------\n";
    out << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << "Galutinis balas\n";
    out << "--------------------------------------------------\n";
    for (const auto& studentas : studentai) {
        out << std::left << std::setw(15) << studentas.vardas() << std::setw(15) << studentas.pavarde() << studentas.galutinis() << "\n";
    }
}


// Funkcija: nuskaityti studentus iš failo
void nuskaitytiIsFailo(Vector<Studentas>& studentai, const std::string& failoVardas) {
    std::ifstream failas(failoVardas);
    if (!failas) throw std::runtime_error("Failas nerastas: " + failoVardas);

    std::string eilute;
    getline(failas, eilute); // praleidžiam antraštę

    while (getline(failas, eilute)) {
        std::istringstream iss(eilute);
        Studentas studentas;
        studentas.read(iss);
        studentai.push_back(studentas);
    }
}


// Funkcija: rikiuoti studentus pagal pasirinkimą
void rikiuotiStudentus(Vector<Studentas>& studentai, char kriterijus) {
    switch (std::tolower(kriterijus)) {
        case 'v':
            std::sort(studentai.begin(), studentai.end(), compareVardas);
            break;
        case 'p':
            std::sort(studentai.begin(), studentai.end(), comparePavarde);
            break;
        case 'g':
            std::sort(studentai.begin(), studentai.end(), compareGalutinis);
            break;
        default:
            std::cout << "Neteisingas rikiavimo kriterijus.\n";
    }
}


// Funkcija: generuoti failą su studentais
void generuotiFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndSk, char metodas) {
    Vector<Studentas> studentai;
    generuotiStudentus(studentai, studentuKiekis, ndSk);

    std::ofstream out(failoPavadinimas);
    if (!out) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << "\n";
        return;
    }

    out << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde";
    for (int i = 0; i < ndSk; ++i) {
        out << std::setw(5) << ("ND" + std::to_string(i+1));
    }
    out << std::setw(10) << "Egzaminas\n";

    for (const auto& s : studentai) {
        out << std::left << std::setw(15) << s.vardas()
            << std::setw(15) << s.pavarde();
        for (int paz : s.nd()) {
            out << std::setw(5) << paz;
        }
        out << std::setw(10) << s.egzaminas() << "\n";
    }
    out.close();
}


void padalintiStudentus(const Vector<Studentas>& studentai, Vector<Studentas>& vargsiai, Vector<Studentas>& kietiakai) {
    for (const auto& s : studentai) {
        if (s.galutinis() < 5.0)
            vargsiai.push_back(s);
        else
            kietiakai.push_back(s);
    }
}

// Funkcija: spausdinti studentus į failą
void spausdintiStudentusIFaila(const Vector<Studentas>& studentai, const std::string& failoVardas) {
    std::ofstream out(failoVardas);
    if (!out) {
        std::cerr << "Nepavyko atidaryti failo: " << failoVardas;
        return;
    }
    spausdintiRezultatus(studentai, out);
    out.close();
}

void apdorotiFaila(const std::string& failoVardas, char metodas) {
    Vector<Studentas> studentai;
    try {
        nuskaitytiIsFailo(studentai, failoVardas);
        for (auto& s : studentai) s.skaiciuotiGalutini(metodas);

        Vector<Studentas> vargsiai, kietiakai;
        padalintiStudentus(studentai, vargsiai, kietiakai);

        std::string baseName = failoVardas.substr(0, failoVardas.find_last_of('.'));
        std::string failoVargsiukai = baseName + "_vargsiukai.txt";
        std::string failoKietiakai = baseName + "_kietiakai.txt";

        char kriterijus;
        std::cout << "Pasirinkite rikiavimo kriteriju (V - vardas, P - pavarde, G - galutinis balas): ";
        std::cin >> kriterijus;
        rikiuotiStudentus(vargsiai, kriterijus);
        rikiuotiStudentus(kietiakai, kriterijus);

        spausdintiStudentusIFaila(vargsiai, failoVargsiukai);
        spausdintiStudentusIFaila(kietiakai, failoKietiakai);
        

        std::cout << "Failas " << failoVardas << " buvo apdorotas.\n";
        std::cout << "  - Vargsiu rezultatai: " << failoVargsiukai << "\n";
        std::cout << "  - Kietiu rezultatai: " << failoKietiakai << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
    }
}

void testMemoryReallocations() {
    const size_t N = 100000000;

    Vector<int> myVec;
    for (size_t i = 0; i < N; ++i) {
        myVec.push_back(i);
    }
    std::cout << "Vector perskirstymai: " << myVec.getReallocations() << std::endl;

    std::vector<int> stdVec;
    size_t stdReallocations = 0;
    size_t prevCapacity = 0;
    for (size_t i = 0; i < N; ++i) {
        stdVec.push_back(i);
        if (stdVec.capacity() != prevCapacity) {
            stdReallocations++;
            prevCapacity = stdVec.capacity();
        }
    }
    std::cout << "std::vector perskirstymai: " << stdReallocations << std::endl;
}

void vykdytiPrograma() {
    Vector<Studentas> studentai;
    srand(time(0));

    try {
        char metodas;
        do {
            std::cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
            std::cin >> metodas;
        } while (metodas != 'V' && metodas != 'v' && metodas != 'M' && metodas != 'm');

        bool testi = true;
        while (testi) {
            try {
                std::cout << "\nPasirinkite veiksma:\n";
                std::cout << "1 - Ivesti ranka\n";
                std::cout << "2 - Generuoti pazymius\n";
                std::cout << "3 - Generuoti studentus ir pazymius\n";
                std::cout << "4 - Nuskaityti is failo\n";
                std::cout << "5 - Generuoti failus\n";
                std::cout << "6 - Apdoroti faila\n";
                std::cout << "7 - Testuoti atminties perskirstymus\n";
                std::cout << "8 - Baigti\n";
                std::cout << "Jusu pasirinkimas: ";
                int pasirinkimas;
                if (!(std::cin >> pasirinkimas)) {
                    throw std::runtime_error("Neteisingas pasirinkimas! Iveskite sveikaji skaiciu.");
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (pasirinkimas == 8) {
                    testi = false;
                    break;
                }

                Studentas studentas;
                if (pasirinkimas == 1) {
                    std::string v, p;
                    std::cout << "Iveskite varda ir pavarde: ";
                    std::cin >> v >> p;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (!arTinkamasVardas(v) || !arTinkamasVardas(p)) {
                        std::cout << "Vardas ar pavarde netinkami.\n";
                        continue;
                    }

                    studentas.setVardas(v);
                    studentas.setPavarde(p);

                    int paz;
                    std::cout << "Iveskite pazymius (1-10, -1 baigti):\n";
                    while (true) {
                        std::cout << "Pazymys: ";
                        if (arTinkamasPazymys(paz)) {
                            if (paz == -1) break;
                            studentas.pridetiND(paz);
                        }
                    }

                    std::cout << "Egzamino pazymys: ";
                    arTinkamasPazymys(paz);
                    studentas.setEgzaminas(paz);

                    studentas.skaiciuotiGalutini(metodas);
                    studentai.push_back(studentas);
                }

                else if (pasirinkimas == 2) {
                    std::string v, p;
                    std::cout << "Iveskite varda ir pavarde: ";
                    std::cin >> v >> p;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    studentas.setVardas(v);
                    studentas.setPavarde(p);

                    int kiek;
                    std::cout << "Kiek pazymiu generuoti? ";
                    std::cin >> kiek;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    studentas.generuotiPazymius(kiek);

                    int egz;
                    egz = rand() % 10 + 1;
                    studentas.setEgzaminas(egz);

                    studentas.skaiciuotiGalutini(metodas);
                    studentai.push_back(studentas);
                }

                else if (pasirinkimas == 3) {
                    int kiek, ndSk;
                    std::cout << "Kiek studentu generuoti? ";
                    std::cin >> kiek;
                    std::cout << "Kiek namu darbu? ";
                    std::cin >> ndSk;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    generuotiStudentus(studentai, kiek, ndSk);
                }

                else if (pasirinkimas == 4) {
                    std::string failoVardas;
                    std::cout << "Iveskite failo pavadinima: ";
                    std::cin >> failoVardas;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    nuskaitytiIsFailo(studentai, failoVardas);
                    for (auto& s : studentai) s.skaiciuotiGalutini(metodas);
                }

                else if (pasirinkimas == 5) {
                    int kiek, ndSk;
                    std::string failas;
                    std::cout << "Kiek studentu generuoti? ";
                    std::cin >> kiek;
                    std::cout << "Kiek namu darbu? ";
                    std::cin >> ndSk;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Iveskite failo pavadinima: ";
                    std::cin >> failas;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    generuotiFaila(failas, kiek, ndSk, metodas);
                }

                else if (pasirinkimas == 6) {
                    std::string failas;
                    std::cout << "Iveskite failo pavadinima: ";
                    std::cin >> failas;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    apdorotiFaila(failas, metodas);
                }
                
                else if (pasirinkimas == 7) {
                    testMemoryReallocations();
                }
                else {
                    std::cout << "Neteisingas pasirinkimas.\n";
                }

            } catch (const std::exception& e) {
                std::cout << "Klaida: " << e.what() << "\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        char rikiavimas;
        std::cout << "Pasirinkite rikiavimo kriteriju (V - vardas, P - pavarde, G - galutinis balas): ";
        std::cin >> rikiavimas;
        rikiuotiStudentus(studentai, rikiavimas);

        // Isvedimo budas
        char isvedimas;
        std::cout << "Ar norite spausdinti i faila ar i ekrana? (F - failas, E - ekranas): ";
        std::cin >> isvedimas;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (isvedimas == 'F' || isvedimas == 'f') {
            std::string failas;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failas;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            spausdintiStudentusIFaila(studentai, failas);
        } else {
            spausdintiRezultatus(studentai, std::cout);
        }
    } catch (const std::exception& e) {
        std::cerr << "Kritine klaida: " << e.what() << std::endl;
    }
}

int main() {
    vykdytiPrograma();
    return 0;
}
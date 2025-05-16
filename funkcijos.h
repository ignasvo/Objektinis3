#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Studentas.h"
#include <string>
#include "vector.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <chrono>

// Funkcijos, kurios dirba su studentų sąrašu

bool arTinkamasVardas(const std::string& tekstas);
bool arTinkamasPazymys(int& pazymys);

double skaiciuotiVidurki(const Vector<int>& pazymiai);
double skaiciuotiMediana(Vector<int> pazymiai);

// Dirba su vienu Studentas objektu
void skaiciuotiGalutiniBala(Studentas& studentas, char metodas);
void generuotiPazymius(Studentas& studentas, int kiek);

// Dirba su studentų vektoriumi
void generuotiStudentus(Vector<Studentas>& studentai, int kiek, int ndSk);
void spausdintiRezultatus(const Vector<Studentas>& studentai, std::ostream& out);
void nuskaitytiIsFailo(Vector<Studentas>& studentai, const std::string& failoVardas);
void rikiuotiStudentus(Vector<Studentas>& studentai, char kriterijus);
void generuotiFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndSk, char metodas);
void padalintiStudentus(const Vector<Studentas>& studentai, Vector<Studentas>& vargsiai, Vector<Studentas>& kietiakai);
void spausdintiStudentusIFaila(const Vector<Studentas>& studentai, const std::string& failoVardas);
void apdorotiFaila(const std::string& failoVardas, char metodas);

void vykdytiPrograma(); // Pagrindinė funkcija programos valdymui

#endif

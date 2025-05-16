#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Studentas.h"
#include <string>
#include <vector>
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

double skaiciuotiVidurki(const std::vector<int>& pazymiai);
double skaiciuotiMediana(std::vector<int> pazymiai);

// Dirba su vienu Studentas objektu
void skaiciuotiGalutiniBala(Studentas& studentas, char metodas);
void generuotiPazymius(Studentas& studentas, int kiek);

// Dirba su studentų vektoriumi
void generuotiStudentus(std::vector<Studentas>& studentai, int kiek, int ndSk);
void spausdintiRezultatus(const std::vector<Studentas>& studentai, std::ostream& out);
void nuskaitytiIsFailo(std::vector<Studentas>& studentai, const std::string& failoVardas);
void rikiuotiStudentus(std::vector<Studentas>& studentai, char kriterijus);
void generuotiFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndSk, char metodas);
void padalintiStudentus(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakai);
void spausdintiStudentusIFaila(const std::vector<Studentas>& studentai, const std::string& failoVardas);
void apdorotiFaila(const std::string& failoVardas, char metodas);

void vykdytiPrograma(); // Pagrindinė funkcija programos valdymui

#endif

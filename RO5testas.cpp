#include "studentas.h"
#include <iostream>
#include <sstream>

void testRuleOfFive() {
    std::cout << "Rule of Five testas\n";

    Studentas s1("Testas", "Testavicius", {9, 8, 10}, 10);
    std::cout << "s1 sukurtas: " << s1 << "\n";

    Studentas s2(s1);  // kopijavimo konstruktorius
    std::cout << "s2 (kopija s1): " << s2 << "\n";
    std::cout << "s1 po kopijavimo: " << s1 << "\n"; // Turi likti toks pat

    Studentas s3(std::move(s1));  // perkėlimo konstruktorius
    std::cout << "s3 (perkeltas s1): " << s3 << "\n";
    std::cout << "s1 po perkelimo: " << s1 << "\n"; // Turi būti tuščias/numatytasis

    Studentas s4;
    s4.operator=(s2);
    std::cout << "s4 (priskirtas s2): " << s4 << "\n";
    std::cout << "s2 po priskyrimo: " << s2 << "\n"; // Turi likti toks pat

    Studentas s5;
    s5.operator=(std::move(s3));
    std::cout << "s5 (perkeltas s3): " << s5 << "\n";
    std::cout << "s3 po perkelimo: " << s3 << "\n"; // Turi būti tuščias/numatytasis

    std::cout << "\nGalutines objektu busenos:\n";
    std::cout << "s1: " << s1 << "\n";
    std::cout << "s2: " << s2 << "\n";
    std::cout << "s3: " << s3 << "\n";
    std::cout << "s4: " << s4 << "\n";
    std::cout << "s5: " << s5 << "\n";
}

void testDestruktorius() {
    std::cout << "\nDestruktoriaus testas\n";
    {
        Studentas laikinas("Testas", "Testavicius", {5, 6, 7}, 8);
        std::cout << "Laikinas studentas sukurtas: " << laikinas << "\n";
    }
    std::cout << "Isejome is bloko, destruktorius turejo buti iskvieciamas.\n";
}

void testIO() {
    std::cout << "\nIvesties ir isvesties operatoriu testas";
    std::istringstream iss("Testas Testavicius 10 9 8 7");
    Studentas s;
    iss >> s; 

    std::cout << "\nNuskaitytas studentas:\n";
    std::cout << s << "\n";
}

void testZmogus() {
    /*std::cout << "\nAbstrakcios klases testas" << std::endl;
     Zmogus z;  // Kelia klaida, nes Zmogus yra abstrakti klase
     Zmogus z("Jonas", "Jonaitis");  
     */
}

int main() {
    testRuleOfFive();
    testDestruktorius();
    testIO();

    std::cout << "\nJei viskas isvedama tvarkingai ir programa neuzstrigo, testas sekmingas\n";
    return 0;
}
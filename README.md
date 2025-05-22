# Efektyvumo analizė

Toliau pateikiama palyginamoji `push_back()` operacijos trukmė skirtingiems elementų kiekiams, matuojant vidutinį laiką milisekundėmis:

| Elementų kiekis  | `std::vector` (ms) | `Vector` (ms) |
|------------------|--------------------:|--------------:|
| 10 000           | 0.217               | 0.069         |
| 100 000          | 1.85                | 0.555         |
| 1 000 000        | 18.597              | 4.959         |
| 10 000 000       | 189.844             | 54.176        |
| 100 000 000      | 1745.370            | 462.541       |

**Komentaras:**
- Mūsų `Vector` klasė ženkliai spartesnė nei `std::vector` pagal šiuos bandymus.

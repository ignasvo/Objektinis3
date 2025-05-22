# 2.0 nuosavos Vector klasės testavimas

## Aprašymas

Ši `Vector<T>` klasė yra sukurta siekiant atkartoti `std::vector` elgseną. Ji palaiko didžiąją dalį funkcionalumo, įskaitant dinaminius atminties pokyčius, operatorius, iteratorius ir kt. Testuota naudojant `doctest` ir lyginta su `std::vector`.

## 5 funkcijų pavyzdžiai

### 1. `operator[]`
```cpp
Vector<int> v = {1, 2, 3};
std::cout << v[1]; // Output: 2
```

### 2. `push_back`
```cpp
Vector<std::string> v;
v.push_back("labas");
v.push_back("pasauli");
```

### 3. `at()`
```cpp
Vector<int> v = {10, 20};
try {
    v.at(5);
} catch (const std::out_of_range& e) {
    std::cout << "Klaida: " << e.what();
}
```

### 4. `operator==`
```cpp
Vector<int> a = {1, 2, 3};
Vector<int> b = {1, 2, 3};
std::cout << (a == b); // Output: 1
```

### 5. `emplace_back()`
```cpp
struct Test { int x, y; Test(int a, int b) : x(a), y(b) {} };
Vector<Test> v;
v.emplace_back(1, 2);
```

## Testavimas

Klasė testuota su `doctest`, testuojant:
- Konstruktorius ir priskyrimus
- Elementų prieigą
- Iteracijas ir atminties valdymą
- Modifikatorius (`push_back`, `erase`, `insert`, `resize` ir kt.)
- Operatorius (`==`, `!=`, `<`, `>` ir kt.)

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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.h"
#include <vector>
#include <string>
#include <numeric> // for std::iota

TEST_CASE("Constructor and assignment") {
    Vector<int> v1(5, 7);
    std::vector<int> v2(5, 7);
    CHECK(v1.size() == v2.size());
    for (size_t i = 0; i < v1.size(); ++i) CHECK(v1[i] == v2[i]);

    Vector<int> v3 = {1, 2, 3};
    Vector<int> v4(v3);
    CHECK(v3 == v4);

    Vector<int> v5(std::move(v3));
    CHECK(v5 == v4);

    Vector<int> v6;
    v6 = v4;
    CHECK(v6 == v4);

    Vector<int> v7;
    v7 = std::move(v4);
    CHECK(v7 == v5);
}

TEST_CASE("Element access") {
    Vector<std::string> v = {"a", "b", "c"};
    CHECK(v[0] == "a");
    CHECK(v.at(1) == "b");
    CHECK_THROWS_AS(v.at(5), std::out_of_range);
    CHECK(v.front() == "a");
    CHECK(v.back() == "c");
    CHECK(v.data() != nullptr);
}

TEST_CASE("Iterators") {
    Vector<int> v = {1, 2, 3};
    CHECK(*(v.begin()) == 1);
    CHECK(*(v.end() - 1) == 3);
    CHECK(*(v.rbegin()) == 3);
    CHECK(*(v.rend() - 1) == 1);
}

TEST_CASE("Capacity") {
    Vector<int> v;
    CHECK(v.empty());
    v.push_back(10);
    CHECK(v.size() == 1);
    CHECK(v.capacity() >= 1);
    v.reserve(100);
    CHECK(v.capacity() >= 100);
    v.shrink_to_fit();
    CHECK(v.capacity() >= v.size());
}

TEST_CASE("Modifiers") {
    Vector<int> v = {1, 2, 3};
    v.push_back(4);
    CHECK(v.back() == 4);
    v.pop_back();
    CHECK(v.back() == 3);

    v.emplace_back(99);
    CHECK(v.back() == 99);

    v.insert(v.begin() + 1, 42);
    CHECK(v[1] == 42);

    v.erase(v.begin() + 1);
    CHECK(v[1] == 2);

    v.clear();
    CHECK(v.empty());

    v.resize(5);
    CHECK(v.size() == 5);

    v.resize(10, 8);
    CHECK(v[9] == 8);
}

TEST_CASE("Comparison operators") {
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {1, 2, 3};
    Vector<int> c = {1, 2, 4};
    CHECK(a == b);
    CHECK(a != c);
    CHECK(a < c);
    CHECK(c > b);
    CHECK(a <= b);
    CHECK(c >= b);
}

TEST_CASE("Swap and non-member swap") {
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {4, 5};
    swap(a, b);
    CHECK(a.size() == 2);
    CHECK(b.size() == 3);
}

TEST_CASE("Insert and erase range") {
    Vector<int> v = {1, 2, 3, 4, 5};
    v.erase(v.begin() + 1, v.begin() + 4); // remove 2,3,4
    CHECK(v.size() == 2);
    CHECK(v[0] == 1);
    CHECK(v[1] == 5);

    v.insert(v.begin() + 1, 99);
    CHECK(v[1] == 99);
}

TEST_CASE("emplace") {
    struct Point {
        Point() : x(0), y(0) {} 
        int x, y;
        Point(int a, int b) : x(a), y(b) {}
        bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    };
    Vector<Point> v;
    v.emplace_back(1, 2);
    v.emplace_back(3, 4);
    CHECK(v[0] == Point(1, 2));
    CHECK(v[1] == Point(3, 4));

    v.emplace(v.begin() + 1, 9, 9);
    CHECK(v[1] == Point(9, 9));
}

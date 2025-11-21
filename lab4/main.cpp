#include "Figure.hpp"
#include "Rhombus.hpp"
#include "Pentagon.hpp"
#include "Hexagon.hpp"
#include "Vector.hpp"
#include <memory>


int main(){
    Rhombus<double> rhombus;
    Pentagon<double> pentagon;
    Hexagon<double> hexagon;

    if (true) {
        rhombus = Rhombus<double>({Point<double>(0, 0), Point<double>(0, 1), Point<double>(1, 1), Point<double>(1, 0)});
        pentagon = Pentagon<double>({Point<double>(1, 0), Point<double>(5, 0), Point<double>(6, 2), Point<double>(3, 4), Point<double>(0, 2)});
        hexagon = Hexagon<double>({Point<double>(1, 0), Point<double>(4, 0), Point<double>(5, 2), Point<double>(4, 4), Point<double>(1, 4), Point<double>(0, 2)});
    }
    else {
        rhombus = Rhombus<double>();
        pentagon = Pentagon<double>();
        hexagon = Hexagon<double>();
        std::cin >> rhombus >> pentagon >> hexagon;
    }
    std::cout << pentagon.center() << "bbbbbb\n";
    std::cout << double(pentagon) << "aaaaaabbbbbb\n";
    Vector<double> vector = Vector<double>();
    vector.pushBack(std::make_shared<Rhombus<double>>(rhombus));
    vector.pushBack(std::make_shared<Pentagon<double>>(pentagon));
    vector.pushBack(std::make_shared<Hexagon<double>>(hexagon));
    if (*vector.getF(0) == *vector.getF(2)) {
        std::cout << "Equal\n";
    }
    for (size_t i = 0; i < 3; i++) {
        std::cout << *vector.getF(i) << "\n";
    }
    for (size_t i = 0; i < vector.length(); i++) {
        std::cout << (*vector.getF(i)).center() << "\n";
    }
    std::cout << vector.allArea() << "\n";
    vector.pop(0);\
    std::cout << vector.allArea() << "\n";
}

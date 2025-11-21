#pragma once

#include <initializer_list>
#include <iostream>
#include "concept.hpp"


template<Scalar T>
class Point
{
    private:
        T x, y;

    public:
        Point(T x = 0, T y = 0, Point* next = nullptr) : x(x), y(y) {}

        Point(const std::initializer_list<T> &xy, Point* next = nullptr) : x(0), y(0) {
            auto it = xy.begin();
            if (xy.size() > 0) { this->x = *it++; }
            if (xy.size() > 1) { this->y = *it; }
        }

        T getX() const {
            return this->x;
        }

        T getY() const {
            return this->y;
        }

        friend std::ostream& operator<<(std::ostream& os, const Point& point) {
            os << "Point(" << point.x << "," << point.y << ")";
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Point& point) {
            is >> point.x >> point.y;
            return is;
        }
};

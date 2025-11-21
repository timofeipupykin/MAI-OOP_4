#pragma once

#include "Point.hpp"
#include "concept.hpp"

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>


template <Scalar T>
class Figure {
    protected:
        std::unique_ptr<Point<T>[]> data;
        size_t size;

        virtual void validate() {};

        T absoluteArea() const {
            if (this->size < 3) { return T(0); }

            T area;
            for (size_t i = 0; i < this->size; i++) {
                area += this->data[i].getX() * this->data[(i + 1) % this->size].getY() - this->data[(i + 1) % this->size].getX() * this->data[i].getY();
            }
            return area / 2;
        }

    public:
        Figure() : data(nullptr), size(0) {}

        Figure(Point<T>* points, const size_t size = 0) : size(size) {
            this->data = std::make_unique<Point<T>[]>(this->size);
            for (size_t i = 0; i < this->size; i++) {
                this->data[i] = points[i];
            }
            validate();
        }

        Figure(const std::initializer_list<Point<T>>& points) : size(points.size()) {
            if (size > 0) {
                this->data = std::make_unique<Point<T>[]>(this->size);
                size_t i = 0;
                for (const auto& point : points) {
                    this->data[i++] = point;
                }
                validate();
            }
        }

        Figure(const Figure& other) : size(other.size) {
            this->data = std::make_unique<Point<T>[]>(this->size);
            for (size_t i = 0; i < this->size; i++) {
                this->data[i] = other.data[i];
            }
        }

        Figure(Figure&& other) noexcept : size(other.size), data(std::move(other.data)) {
            other.size = 0;
        }

        virtual ~Figure() = default;

        virtual Figure& operator=(const Figure& other) {
            this->size = other.size;
            this->data = std::make_unique<Point<T>[]>(this->size);
            if (size > 0) {
                for (size_t i = 0; i < this->size; ++i) {
                    this->data[i] = other.data[i];
                }
            }
            else {
                data.reset();
            }
            return *this;
        }
        virtual Figure& operator=(Figure&& other) noexcept {
            this->data = std::move(other.data);
            this->size = other.size;
            other.size = 0;
            return *this;
        }

        virtual Point<T> center() const {
            if (this->size == 0) return Point<T>(0, 0);
            T area = absoluteArea();
            T Cx = T(0);
            T Cy = T(0);
            for (size_t i = 0; i < this->size; ++i) {
                Cx += (this->data[i].getX() + this->data[(i + 1) % this->size].getX()) * (this->data[i].getX() * this->data[(i + 1) % this->size].getY() - this->data[(i + 1) % this->size].getX() * this->data[i].getY());
                Cy += (this->data[i].getY() + this->data[(i + 1) % this->size].getY()) * (this->data[i].getX() * this->data[(i + 1) % this->size].getY() - this->data[(i + 1) % this->size].getX() * this->data[i].getY());
            }
            Cx /= (6 * area);
            Cy /= (6 * area);
            return Point<T>(Cx, Cy);
        }

        virtual operator double() const {
            return static_cast<double>(std::abs(absoluteArea()));
        }

        virtual bool equal(const Figure& other) const {
            double f1 = double(*this);
            double f2 = double(other);    

            return std::abs(f1 - f2) < 1e-9;
        }
        friend bool operator==(const Figure& f1, const Figure& f2) {
            return f1.equal(f2);
        }

        friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
            if (figure.size == 0) { return os; }
            os << "Figure: ";
            for (size_t i = 0; i < figure.size; i++) {
                os << figure.data[i] << " ";
            }
            return os;
        }
        friend std::istream& operator>>(std::istream& is, Figure& figure) {
            size_t size;
            std::cout << "Enter new size: ";
            is >> size;
            if (size == 0) {
                figure.size = 0;
                figure.data.reset();
                return is;
            }

            figure.size = size;
            figure.data = std::make_unique<Point<T>[]>(figure.size);

            for (size_t i = 0; i < figure.size; i++) {
                std::cout << "Point_" << i + 1 << " write: \"x y\": ";
                is >> figure.data[i];
                std::cout << "\n";
            }
            figure.validate();
            return is;
        }  
};

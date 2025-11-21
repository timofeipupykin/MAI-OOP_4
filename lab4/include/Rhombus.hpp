#pragma once

#include "Figure.hpp"
#include <cmath>

template <Scalar T>
class Rhombus : public Figure<T> {
    private:
        void validate() override {
            if (this->size != 4) {
                throw std::runtime_error("Rhombus must have exactly 4 points");
            }
            Point<T> vectors[4];
            for (size_t i = 0; i < 4; i++) {
                vectors[i] = Point<T>(this->data[(i + 1) % 4].getX() - this->data[i].getX(), this->data[(i + 1) % 4].getY() - this->data[i].getY());
            }
            T vector_length = sqrt(pow(vectors[0].getX(), 2) + pow(vectors[0].getY(), 2));
            for (size_t i = 0; i < 4; i++) {
                T dot_product = vectors[i].getX() * vectors[(i + 1) % 4].getX() + vectors[i].getY() * vectors[(i + 1) % 4].getY();
                T other_vector_length = sqrt(pow(vectors[i].getX(), 2) + pow(vectors[i].getY(), 2));
                if (other_vector_length != vector_length) {
                    throw std::runtime_error("Rhombus must have equal sides");
                }
            }
        }
        
    public:
        Rhombus() = default;
        Rhombus(Point<T>* points, size_t size = 4) : Figure<T>(points, size) { validate(); }
        Rhombus(const std::initializer_list<Point<T>>& points) : Figure<T>(points) { validate(); }

        Rhombus(const Rhombus& other) : Figure<T>(other) {validate(); }
        Rhombus(Rhombus&& other) noexcept : Figure<T>(std::move(other)) { validate(); }

        ~Rhombus() noexcept = default;

        Rhombus& operator=(const Rhombus& other) {
            Figure<T>::operator=(other);
            validate();
            return *this;
        }

        Rhombus& operator=(Rhombus&& other) noexcept {
            Figure<T>::operator=(std::move(other));
            validate();
            return *this;
        }
};
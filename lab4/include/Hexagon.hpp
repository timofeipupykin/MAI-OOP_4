#pragma once

#include "Figure.hpp"

template <Scalar T>
class Hexagon : public Figure<T> {
    private:
        void validate() override {
            if (this->size != 6) {
                throw std::runtime_error("Hexagon must have exactly 4 points");
            }
        }
        
    public:
        Hexagon() = default;
        Hexagon(Point<T>* points, size_t size = 4) : Figure<T>(points, size) { validate(); }
        Hexagon(const std::initializer_list<Point<T>>& points) : Figure<T>(points) { validate(); }

        Hexagon(const Hexagon& other) : Figure<T>(other) {validate(); }
        Hexagon(Hexagon&& other) noexcept : Figure<T>(std::move(other)) { validate(); }

        ~Hexagon() noexcept = default;

        Hexagon& operator=(const Hexagon& other) {
            Figure<T>::operator=(other);
            validate();
            return *this;
        }

        Hexagon& operator=(Hexagon&& other) noexcept {
            Figure<T>::operator=(std::move(other));
            validate();
            return *this;
        }
};
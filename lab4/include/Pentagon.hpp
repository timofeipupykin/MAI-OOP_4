#pragma once

#include "Figure.hpp"

template <Scalar T>
class Pentagon : public Figure<T> {
    private:
        void validate() override {
            if (this->size != 5) {
                throw std::runtime_error("Pentagon must have exactly 4 points");
            }
        }
        
    public:
        Pentagon() = default;
        Pentagon(Point<T>* points, size_t size = 4) : Figure<T>(points, size) { validate(); }
        Pentagon(const std::initializer_list<Point<T>>& points) : Figure<T>(points) { validate(); }

        Pentagon(const Pentagon& other) : Figure<T>(other) {validate(); }
        Pentagon(Pentagon&& other) noexcept : Figure<T>(std::move(other)) { validate(); }

        ~Pentagon() noexcept = default;

        Pentagon& operator=(const Pentagon& other) {
            Figure<T>::operator=(other);
            validate();
            return *this;
        }

        Pentagon& operator=(Pentagon&& other) noexcept {
            Figure<T>::operator=(std::move(other));
            validate();
            return *this;
        }
};
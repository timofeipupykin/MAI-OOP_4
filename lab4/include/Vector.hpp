#pragma once

#include "Figure.hpp"
#include <cstddef>
#include <memory>

template <Scalar T>
class Vector {
    private:
        std::shared_ptr<std::shared_ptr<Figure<T>>[]> data;
        size_t size;
        size_t capacity;

        void reallocate(size_t new_capacity) {
            auto newData = std::make_shared<std::shared_ptr<Figure<T>>[]>(new_capacity);
            for (size_t i = 0; i < this->size; i++) {
                newData[i] = this->data[i];
            }
            this->data = newData;
            this->capacity = new_capacity;
        }
    
    public:
        Vector() = default;

        Vector(Figure<T> value, size_t size = 0) : size(size), capacity(size), data(std::make_shared<Figure<T>>(size)) {
            for (size_t i = 0; i < size; i++) {
            this->data[i] = value;
            }
        }

        virtual ~Vector() noexcept = default;

        void pushBack(std::shared_ptr<Figure<T>> value) {
            if (this->size < this->capacity) {
                this->data[this->size++] = value;
            }
            else {
                if (this->capacity == 0) {
                    reallocate(1);
                }
                else {
                    reallocate(this->capacity * 2);
                }
                pushBack(value);
            }
        };

        void pop(int idx = 0) {
            if (idx > this->size) { return; }
            this->data[idx] = nullptr;
            
            for (size_t i = idx; i < this->size; i++) {
                this->data[i] = this->data[i + 1];
            }
            this->size--;
        }

        T allArea() {
            double area = 0.0;
            for (size_t i = 0; i < size; i++) {
                double temp = *this->data[i];
                area += temp;
            }
            return T(area);
        }
        std::shared_ptr<Figure<T>> getF(int idx = 0) const {
            return this->data[idx];
        }
        size_t length() const {
            return this->size;
        }
};

#pragma once

#include <iostream>
#include <cmath>

class DynamicArray {
private:
    double* array;
    int length{1};

public:
    DynamicArray() {
        array = new double[length];
    }

    explicit DynamicArray(int length) {
        this->length = length;
        array = new double[length];
        for (int i = 0; i < length; i++) {
            array[i] = 0;
        }
    }

    DynamicArray(const DynamicArray &externalArr) {
        array = new double[externalArr.length];
        length = externalArr.getLength();
        for (int i = 0; i < externalArr.length; i++) {
            array[i] = externalArr.array[i];
        }
    }

    [[nodiscard]] int getLength() const {
        return length;
    }

    void setItemByIndex(int ind, double val) {
        array[ind] = val;
    }

    double getItemByIndex(int ind) {
        return array[ind];
    }

    double getMinItem() {
        int minInd = 0;
        for (int i = 1; i < length; i++) {
            if (array[i] < array[minInd]) {
                minInd = i;
            }
        }
        return array[minInd];
    }

    bool isOrdered() {
        bool ascCond = true;
        bool descCond = true;
        for (int i = 0; i < length - 1; i++) {
            if (array[i] > array[i + 1]) {
                ascCond = false;
            }
        }
        for (int i = 0; i < length - 1; i++) {
            if (array[i] < array[i + 1]) {
                descCond = false;
            }
        }
        return ascCond || descCond;
    }

    [[nodiscard]] DynamicArray subarrayWithOddIndices() const {
        int oddLength = ceil((double)length / 2);
        DynamicArray oddArray(oddLength);
        for (int i = 0, j = 1; j < length; i++, j += 2) {
            oddArray.setItemByIndex(i, array[j]);
        }
        return oddArray;
    }

    void printArray() {
        std::cout << "[";
        for (int i = 0; i < length; i++) {
            if (i != length - 1) {
                std::cout << array[i] << ", ";
            } else {
                std::cout << array[i];
            }
        }
        std::cout << "]";
    }

    ~DynamicArray() {
        if (array != nullptr) {
            delete[] array;
            array = nullptr;
        }
    }
};
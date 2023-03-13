#include "dynamic_array.h"

int main(int argc, char* argv[]) {
    std::cout << "Creating an object of class DynamicArray" << std::endl;
    DynamicArray dynamicArray{6};
    std::cout << "Current length: " << dynamicArray.getLength() << std::endl;

    std::cout << "\nElement at position 2: " << dynamicArray.getItemByIndex(2) << std::endl;
    std::cout << "Let's change it" << std::endl;

    dynamicArray.setItemByIndex(2, 12.6);
    std::cout << "Now the element at position 2 is: " << dynamicArray.getItemByIndex(2) << "\n" << std::endl;

    std::cout << "Let's set values to other elements..." << std::endl;
    dynamicArray.setItemByIndex(0, 2.56);
    dynamicArray.setItemByIndex(1, 123.4);
    dynamicArray.setItemByIndex(3, 15);
    dynamicArray.setItemByIndex(4, 63.345);
    dynamicArray.setItemByIndex(5, 91.2);

    std::cout << "Our array is now: ";
    dynamicArray.printArray();

    bool isOrdered = dynamicArray.isOrdered();
    if (isOrdered) {
        std::cout << "\nIt's sorted" << std::endl;
    } else {
        std::cout << "\nIt isn't sorted" << std::endl;
    }

    std::cout << "Subarray with odd indices: ";
    DynamicArray oddArray = dynamicArray.subarrayWithOddIndices();
    oddArray.printArray();

    std::cout << '\n';
    system("pause");
    return EXIT_SUCCESS;
}
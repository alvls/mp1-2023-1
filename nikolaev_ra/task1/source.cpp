#include "length_converter.h"

int main() {
    std::cout << "Creating an object of class LengthConverter" << std::endl;
    LengthConverter lc{};
    std::cout << "Current length in meters: " << lc.get_length() << std::endl;  // 0 by default

    std::cout << "\nSetting value: 123.5 meters" << std::endl;
    lc.set_length(123.5);
    std::cout << "Current length in feet: " << lc.GetLengthInFeet() << std::endl;
    std::cout << "Current length in arshins: " << lc.GetLengthInArshins() << std::endl;

    // Now let's give you the option to enter a length value
    int length_value;
    std::cout << "\nEnter a length value in meters (if incorrect data is entered, the value 0 will be assigned): " << std::endl;
    std::cin >> length_value;

    lc.set_length(length_value);
    std::cout << "Current length in yards: " << lc.GetLengthInYards() << std::endl;
    std::cout << "Current length in fathoms: " << lc.GetLengthInFathoms() << std::endl;
    lc.PrintInformation();
    system("pause");
    return 0;
}
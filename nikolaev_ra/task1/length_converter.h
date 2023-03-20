#include <iostream>

class LengthConverter
{
private:
    double length_{};

public:
    const double foot_factor   = 3.28084;
    const double yard_factor   = 1.09361;
    const double arshin_factor = 1.40607;
    const double fathom_factor = 0.54680;

public:
    LengthConverter() = default;

    explicit LengthConverter(double length_value)
    {
        (length_value >= 0) ? length_ = length_value : length_ = 0;
    }

    [[nodiscard]] double get_length() const
    {
        return length_;
    }

    void set_length(double length_value)
    {
        (length_value >= 0) ? length_ = length_value : length_ = 0;
    }

    [[nodiscard]] double get_length_in_feet() const
    {
        return length_ * foot_factor;
    }

    [[nodiscard]] double get_length_in_yards() const
    {
        return length_ * yard_factor;
    }

    [[nodiscard]] double get_length_in_arshins() const
    {
        return length_ * arshin_factor;
    }

    [[nodiscard]] double get_length_in_fathoms() const
    {
        return length_ * fathom_factor;
    }

    void print_information() const
    {
        std::cout << "LengthConverter{meters: " << length_ << ", feet: " << get_length_in_feet() << ", yards: " 
                  << get_length_in_yards() << ", arshins: " << get_length_in_arshins() << ", fathoms: " 
                  << get_length_in_fathoms() << "}" << std::endl;
    }
};

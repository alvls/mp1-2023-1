#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const int DAY_HOURS = 24;
const int MONTH_DAYS = 31;
const int DAY_START = 6;
const int DAY_END = 18;
const int NIGHT_START = 19;
const int MIDNIGHT = 0;
const int HOUR_TO_MIDNIGHT = 23;
const int NIGHT_END = 5;

struct Observation {
    int day;
    int month;
    int year;
    int hour;
    double temperature;
};

class Thermometer {
private:
    std::vector<Observation> observations;
    int startDay;
    int startMonth;
    int startYear;
    int startHour;
public:
    Thermometer() {
        startDay = 1;
        startMonth = 1;
        startYear = 2023;
        startHour = 0;
    }

    void SetStartDate(int day, int month, int year, int hour) {
        startDay = day;
        startMonth = month;
        startYear = year;
        startHour = hour;
    }

    [[nodiscard]] std::string GetStartDate() const {
        return std::to_string(startDay) + "." + std::to_string(startMonth) + "." + std::to_string(startYear) +
                " " + std::to_string(startHour) + ":00";
    }

    void SetObservation(int day, int month, int year, int hour, double temperature) {
        bool found = false;
        for (auto & observation : observations) {
            if (observation.day == day && observation.month == month && observation.year == year && observation.hour == hour) {
                observation.temperature = temperature;
                found = true;
                break;
            }
        }
        if (!found) {
            Observation obs{};
            obs.day = day;
            obs.month = month;
            obs.year = year;
            obs.hour = hour;
            obs.temperature = temperature;
            observations.push_back(obs);
        }
    }

    double GetTemperature(int day, int month, int year, int hour) {
        for (auto & observation : observations) {
            if (observation.day == day && observation.month == month && observation.year == year && observation.hour == hour) {
                return observation.temperature;
            }
        }
        return -1;
    }

    void SetObservationsForDate(int day, int month, int year, double temperature) {
        for (int i = 0; i < DAY_HOURS; i++) {
            SetObservation(day, month, year, i, temperature);
        }
    }

    double GetAverageTemperatureForDate(int day, int month, int year) {
        double sum = 0;
        int count = 0;
        for (int i = 0; i < DAY_HOURS; i++) {
            double temp = GetTemperature(day, month, year, i);
            if (temp != -1) {
                sum += temp;
                count++;
            }
        }
        if (count > 0) {
            return sum / count;
        }
        return -1;
    }

    double GetAverageTemperatureForMonth(int month) {
        double sum = 0;
        int count = 0;
        for (int i = 1; i <= MONTH_DAYS; i++) {
            double temp = GetAverageTemperatureForDate(i, month, startYear);
            if (temp != -1) {
                sum += temp;
                count++;
            }
        }
        if (count > 0) {
            return sum / count;
        }
        return -1;
    }

    double GetAverageDayTemperatureForMonth(int month) {
        double sum = 0;
        int count = 0;
        for (int i = 1; i <= MONTH_DAYS; i++) {
            for (int j = DAY_START; j <= DAY_END; j++) {
                double temp = GetTemperature(i, month, startYear, j);
                if (temp != -1) {
                    sum += temp;
                    count++;
                }
            }
        }
        if (count > 0) {
            return sum / count;
        }
        return -1;
    }

    double GetAverageNightTemperatureForMonth(int month) {
        double sum = 0;
        int count = 0;
        for (int i = 1; i <= MONTH_DAYS; i++) {
            for (int j = NIGHT_START; j <= HOUR_TO_MIDNIGHT; j++) {
                double temp = GetTemperature(i, month, startYear, j);
                if (temp != -1) {
                    sum += temp;
                    count++;
                }
            }
            for (int j = MIDNIGHT; j <= NIGHT_END; j++) {
                double temp = GetTemperature(i, month, startYear, j);
                if (temp != -1) {
                    sum += temp;
                    count++;
                }
            }
        }
        if (count > 0) {
            return sum / count;
        }
        return -1;
    }

    void SaveToFile(const std::string& filename) {
        std::ofstream outfile(filename);
        for (auto & observation : observations) {
            outfile << observation.day << " " << observation.month << " " << observation.year << " " <<
                observation.hour << " " << observation.temperature << std::endl;
        }
        outfile.close();
    }

    void ReadFromFile(const std::string& filename) {
        observations.clear();
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            throw std::runtime_error("File not found!");
        }
        while (!infile.eof()) {
            Observation obs{};
            infile >> obs.day >> obs.month >> obs.year >> obs.hour >> obs.temperature;
            observations.push_back(obs);
        }
        infile.close();
    }
};

int main(int argc, char* argv[]) {
    std::cout << "Let's create an instance of the Thermometer class" << std::endl;
    Thermometer t;

    std::cout << "Making some observations for 1.1.2023..." << std::endl;
    t.SetObservation(1, 1, 2023, 0, -5.0);
    t.SetObservation(1, 1, 2023, 6, -4.5);
    t.SetObservation(1, 1, 2023, 12, -3.0);
    t.SetObservation(1, 1, 2023, 18, -3.5);

    std::cout << "Temperature 1.1.2023 12:00: " << t.GetTemperature(1, 1, 2023, 12) << std::endl;

    std::cout << "Let's make a series of observations for 2.1.2023 and 3.1.2023..." << std::endl;
    t.SetObservationsForDate(2, 1, 2023, -2.5);
    t.SetObservationsForDate(3, 1, 2023, 1.0);

    std::cout << "Average temperature 2.1.2023: " << t.GetAverageTemperatureForDate(2, 1, 2023) << std::endl;
    std::cout << "Average monthly temperature 1.2023: " << t.GetAverageTemperatureForMonth(1) << std::endl;
    std::cout << "Average monthly daily temperature 1.2023: " << t.GetAverageDayTemperatureForMonth(1) << std::endl;
    std::cout << "Average monthly night temperature 1.2023: " << t.GetAverageNightTemperatureForMonth(1) << std::endl;

    std::string path;
    std::cout << "\nEnter the path to save observations:\n";
    std::getline(std::cin, path);
    t.SaveToFile(path);

    system("pause");
    return EXIT_SUCCESS;
}
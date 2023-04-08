#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <fstream>
#include <iterator>
using namespace std;

class StepCounter {
private:
    struct StepRecord {
        int day;
        int month;
        int year;
        int startHour;
        int startMinute;
        int endHour;
        int endMinute;
        int countOfSteps;
    };

    vector<StepRecord> records;

public:
    StepCounter() {}
    void setStartDate(int day, int month, int year) {
        records.clear();
        StepRecord startDate = { day, month, year, 0, 0, 0, 0, 0};
        records.push_back(startDate);
    }
    array<int,3> getStartDate() {
        array<int, 3> startDate = {records[0].day, records[0].month, records[0].year};
        return startDate;
    }
    void addRecord(int day, int month, int year, int startHour, int startMinute, int endHour, int endMinute, int count) {
        StepRecord record = { day, month, year, startHour, startMinute, endHour, endMinute, count };
        records.push_back(record);

    }
    array<int,8> getRecord(int index) {
        array<int, 8> recordInfo = { records[index].day, records[index].month, records[index].year, records[index].startHour, records[index].startMinute, records[index].endHour, records[index].endMinute, records[index].countOfSteps };
        return recordInfo;
    }
    double getAverageStepsMonth(int month = 0) { // if the month is zero, then the average number of steps for the all time is counting
        int totalSteps = 0;
        int countMonths = 0;
        for (int i = 1; i < records.size(); i++) {
            if (month == 0 || records[i].month == month) {
                totalSteps += records[i].countOfSteps;
                countMonths++;
            }
        }
        if (countMonths == 0) {
            return 0;
        }

        double averageSteps = (double)totalSteps / (double)countMonths;
        return averageSteps;
    }
    double getAverageStepsDayOfWeek(int day) {
        int totalSteps = 0;
        int countWeek = 0;
        for (int i = 1; i < records.size(); i++) {
            int dayOfWeek = getDayOfWeek(records[i].day, records[i].month, records[i].year);
            if (dayOfWeek == day) {
                totalSteps += records[i].countOfSteps;
                countWeek++;
            }
        }
        if (countWeek == 0) {
            return 0;
        }
        double averageSteps = (double)totalSteps / (double)countWeek;
        return averageSteps;
    }
    int getDayOfWeek(int day, int month, int year) { // Sakamoto's algorithm to determine the day of the week from a date
        int mass[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        year -= month < 3;
        return (year + year / 4 - year / 100 + year / 400 + mass[month - 1] + day) % 7;
    }
    array<int,4> getMaxStepsMonth(int month = 0) {
        int maxSteps = 0;
        int maxStepsIndex = -1;
        for (int i = 1; i < records.size(); i++) {
            if (month == 0 || records[i].month == month) {
                if (records[i].countOfSteps > maxSteps) {
                    maxSteps = records[i].countOfSteps;
                    maxStepsIndex = i;
                }
            }
        }
        if (maxStepsIndex == -1) {
            return { 0,0,0,0 };
        }
        array<int, 4> maxStepsInfo = { maxSteps,records[maxStepsIndex].day, records[maxStepsIndex].month, records[maxStepsIndex].year };
        return maxStepsInfo;
    }
    void saveRecords(string filename) {
        ofstream fout(filename);
        for (int i = 0; i < records.size(); i++) {
            fout << records[i].day << records[i].month << records[i].year << records[i].startHour << records[i].startMinute << 
                records[i].endHour << records[i].endMinute << records[i].countOfSteps << endl;
        }
        fout.close();
    }
    void readFromFile(string filename) {
        records.clear();
        ifstream fin(filename);
        int count;
        fin >> count;
        for (int i = 0; i < count; i++) {
            StepRecord StepRecord;
            fin >> StepRecord.day >> StepRecord.month >> StepRecord.year >> StepRecord.startHour >> StepRecord.startMinute >>
                StepRecord.endHour >> StepRecord.endMinute >> StepRecord.countOfSteps;
            records.push_back(StepRecord);
        }
        fin.close();
    }

    ~StepCounter() {}
};


int main() {
    StepCounter stepCounter;
    stepCounter.setStartDate(11, 4, 2022);
    array<int, 3> startDate = stepCounter.getStartDate();
    cout << to_string(startDate[0]) + " " + to_string(startDate[1]) + " " + to_string(startDate[2]) << endl;
    stepCounter.addRecord(10,5,2022,14,10,15,20,3000);
    stepCounter.addRecord(29,3,2023,15,40,16,10,1500);
    stepCounter.addRecord(9,3,2023,9,15,10,40,4100);
    array<int, 8> record = stepCounter.getRecord(2);
    cout << record[2] << endl;
    cout << stepCounter.getAverageStepsMonth(0) << endl;
    cout << stepCounter.getAverageStepsMonth(3) << endl;
    cout << stepCounter.getAverageStepsDayOfWeek(3) << endl;
    array<int, 4> maxStepsMonth = stepCounter.getMaxStepsMonth(0);
    cout << to_string(maxStepsMonth[0]) + " " + to_string(maxStepsMonth[1]) + " " + to_string(maxStepsMonth[2]) + " " + to_string(maxStepsMonth[3]) << endl;
    maxStepsMonth = stepCounter.getMaxStepsMonth(3);
    cout << to_string(maxStepsMonth[0]) + " " + to_string(maxStepsMonth[1]) + " " + to_string(maxStepsMonth[2]) + " " + to_string(maxStepsMonth[3]) << endl;
    stepCounter.saveRecords("res.txt");
    stepCounter.readFromFile("res.txt");
    stepCounter.saveRecords("res.txt");
    system("PAUSE");


    return 0;
}
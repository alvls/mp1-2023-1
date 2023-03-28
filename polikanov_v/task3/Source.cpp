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

class Tabulator {
private:
	double leftDot, rightDot = 0;
	int dotAmount = 0;
	double (*function)(double);
	vector<double> result;

public:
	Tabulator(double leftDot, double rightDot, int dotAmount, double(*function)(double)) {
		this->leftDot = leftDot;
		this->rightDot = rightDot;
		this->dotAmount = dotAmount;
		this->function = function;
	}

	void setFunction(double(*function)(double)) {
		this->function = function;
	}
	
	void setDotAmount(int dotAmount) {
		this->dotAmount = dotAmount;
	}

	int getDotAmount() {
		return dotAmount;
	}
	
	void setTabSegment(double leftDot, double rightDot) {
		this->leftDot = leftDot;
		this->rightDot = rightDot;
	}

	array<double,2> getTabSegment() {
		return { leftDot, rightDot };
	}

	void tabulate() {
		double nowDot = leftDot;
		result.clear();
		for (int i = 0; i < dotAmount; i++) {
			result.push_back(nowDot);
			result.push_back(function(nowDot));
			nowDot += (rightDot - leftDot) / (dotAmount - 1);
		}

	}
	
	void printResults() {
		for (int i = 0; i < result.size(); i = i + 2) {
			cout << result[i] << " " << result[i + 1] << endl;
		}
	}
	
	void saveResults(string path) {
		ofstream fout(path);
		for (int i = 0; i < result.size(); i = i + 2) {
			fout << "x: " << result[i] << "   y: " << result[i + 1] << endl;
		}
		fout.close();
	}

	~Tabulator() {
		result.clear();
	}

};

double function1(double x) {
	return 3 * x * x + 10;
}

double function2(double x) {
	return -(x * x * x) + x * x + 1.4;
}

double function3(double x) {
	return sin(x);
}

int main() {
	Tabulator tabulator(1,10,2,function3);
	tabulator.setDotAmount(5);
	tabulator.setTabSegment(1,5);
	tabulator.setFunction(function2);
	tabulator.tabulate();
	tabulator.printResults();
	tabulator.saveResults("res.txt");
	return 0;
}


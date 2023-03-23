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
	double left_dot, right_dot = 0;
	int dot_amount = 0;
	double (*function)(double);
	vector<double> result;

public:
	Tabulator(double left_dot, double right_dot, int dot_amount, double(*function)(double)) {
		this->left_dot = left_dot;
		this->right_dot = right_dot;
		this->dot_amount = dot_amount;
		this->function = function;
	}

	void setFunction(double(*function)(double)) {
		this->function = function;
	}
	
	void setDotAmount(int dot_amount) {
		this->dot_amount = dot_amount;
	}

	int getDotAmount() {
		return dot_amount;
	}
	
	void setTabSegment(double left_dot, double right_dot) {
		this->left_dot = left_dot;
		this->right_dot = right_dot;
	}

	array<double,2> getTabSegment() {
		return { left_dot, right_dot };
	}

	void tabulate() {
		double nowDot = left_dot;
		result.clear();
		for (int i = 0; i < dot_amount; i++) {
			result.push_back(nowDot);
			result.push_back(function(nowDot));
			nowDot += (right_dot - left_dot) / (dot_amount - 1);
		}

	}
	
	void printResults() {
		for (int i = 0; i < result.size(); i = i + 2) {
			cout << result[i] << " " << result[i + 1] << endl;
		}
	}
	
	void saveResults() {
		ofstream fout("res.txt");
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
	tabulator.saveResults();
	return 0;
}


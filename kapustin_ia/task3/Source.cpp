#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Functions_tabulator
{
private:
	double left_point, right_point;
	int amount_point;
	vector<double> results;
	double (*m_func)(double);
public:
	Functions_tabulator() : left_point(0), right_point(1), amount_point(2), m_func(nullptr) {}
	Functions_tabulator(double left, double right, int amount, double (*fuct)(double)) : left_point(left), right_point(right), amount_point(amount), m_func(fuct) {}
	void set_function(double (*fun)(double))
	{
		m_func = fun;
	}
	void set_amount(int amount)
	{
		amount_point = amount;
		results.resize(amount);
	}
	int get_amount_points() const
	{
		return amount_point;
	}
	void set_poins(double left, double right)
	{
		left_point = left;
		right_point = right;
	}
	pair<double, double> get_points() const
	{
		return{ left_point, right_point };
	}
	void tabulation_process()
	{
		double step = (right_point - left_point) / (amount_point - 1);
		double current_point = left_point;
		for (int i = 0; i < amount_point; i++)
		{
			results[i] = m_func(current_point);
			current_point += step;
		}
	}
	void print_res()
	{
		for (int i = 0; i < amount_point; i++)
		{
			cout << results[i] << endl;
		}
	}
	void save_res(string filename) const
	{
		ofstream file(filename);
		double step = (right_point - left_point) / (amount_point - 1);
		double current_point = left_point;
		for (int i = 0; i < amount_point; i++)
		{
			double y = m_func(current_point);
			file << "x = " << current_point << " y = " << y << "\n";
			current_point += step;
		}
		file.close();
	}
};
double function(double x)
{
	return x * x;
}

int main()
{
	Functions_tabulator t;
	t.set_function(function);
	t.set_amount(25);
	t.set_poins(-25.0, 100.0);
	t.tabulation_process();
	t.print_res();
	t.save_res("res.txt");
	return 0;
}

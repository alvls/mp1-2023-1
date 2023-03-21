#include <iostream>
#include "TextEditor.h"

using namespace std;

int main() {

	TextEditor line1("Name: ", 47, 5, 15);
	TextEditor line2("Surname: ", 50, 5, 20);

	cout << line1 << line2 << endl;

	cout << line1.get_label() << "'" << line1.Read() << "'" << endl;
	cout << line2.get_label() << "'" << line2.Read() << "'" << endl;

	return EXIT_SUCCESS;
}

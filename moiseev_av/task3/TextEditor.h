#pragma once

using namespace std;

class TextEditor {

public:
	TextEditor(string label, int x, int y, int length);

	int get_length() const;

	pair<int, int> get_xy() const;

	string get_label() const;

	string Read();

	friend ostream& operator <<(ostream& stream, const TextEditor& source);

private:
	string label;
	int x, y, length;

	void verify_value();
};
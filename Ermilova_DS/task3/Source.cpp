#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <Windows.h>

using namespace std;

class Dictionary {

	map<string, string>Translition;
	string path;

public:

	Dictionary() = default;

	void SetWord(string word, string translation)
	{
		Translition[word] = translation;
	}

	void ChangeTranslation(string word, string translation)
	{
		Translition[word] = translation;
	}

	string GetTranslation(string word)
	{
		return Translition[word];
	}

	void FindWord(string word) {

		auto it = Translition.find(word);

		if (it != Translition.end())
		{
			cout << "The element is in the dictionary\n" << endl;
		}
		else
		{
			cout << "Element not found\n";
		}
	}

	int GetSize() {

		return Translition.size();
	}

	void SaveDictionary(string path) {

		ofstream fout;
		fout.open(path);

		if (!fout.is_open())
		{
			cout << "Error!\n" << endl;
		}
		else
		{
			for (map<string, string>::iterator i = Translition.begin(); i != Translition.end(); ++i)
			{
				fout << i->first << " " << i->second << "\n";
			}
		}

		fout.close();
	}

	void GetDictionary(string path) {

		ifstream fin;
		fin.open(path);

		if (!fin.is_open())
		{
			cout << "Error!\n" << endl;
		}
		else
		{
			string Word, Translit;
			while (fin >> Word >> Translit) {
				Translition[Word] = Translit;
				cout << Translition[Word];
			}
		}

		fin.close();
	}
};

void main()
{

	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Dictionary a;
	string path, word, translation;
	int choice = 9999;

	while (choice != 0) {
		cout << "Press 1 to write down a new word and its translation\nPress 2 to change the translation of the specified word\nPress 3 to find out the translation of the selected word\nPress 4 to check if the word is in the dictionary\nPress 5 to find out the number of words in the dictionary\nPress 6 to save dictionary to file\nPress 7 to read dictionary from file\nPress 0 to exit\n" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Enter a word\n";
			cin >> word;
			cout << "Enter a translation\n";
			cin >> translation;
			a.SetWord(word, translation);
			break;
		}

		case 2:
		{
			cout << "Enter a word\n";
			cin >> word;
			cout << "Enter a translation\n";
			cin >> translation;
			a.ChangeTranslation(word, translation);
			break;
		}
		case 3:
		{
			cout << "Enter a word\n";
			cin >> word;
			cout << a.GetTranslation(word) << "\n";
			break;
		}
		case 4:
		{
			cout << "Enter a word\n";
			cin >> word;
			a.FindWord(word);
			break;
		}
		case 5:
		{
			cout << a.GetSize() << "\n";
			break;
		}
		case 6:
		{
			cout << "Enter the path to the file\n" << endl;
			cin >> path;
			a.SaveDictionary(path);
			break;
		}
		case 7:
		{
			cout << "Enter the path to the file\n" << endl;
			cin >> path;
			a.GetDictionary(path);
			break;
		}
		}
	}
}

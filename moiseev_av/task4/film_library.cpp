#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>

#include "film_library.h"

using namespace std;

film_library::film_library(string path) : path(path) {

    struct_cnt = 0;

    ifstream in;
    in.open(path);

    if (!in.is_open()) throw runtime_error("Invalid path");

    in >> *this;
    in.close();
}

film_library::film_library() { struct_cnt = 0; }

int film_library::get_quantity() { return films_library.size(); }

void film_library::add_film(string name,
    string director,
    string screenwriter,
    string composer,
    int day,
    int month,
    int year,
    long long int fees) {

    film_t fs_add;

    fs_add.name = name;
    fs_add.director = director;
    fs_add.screenwriter = screenwriter;
    fs_add.composer = composer;
    fs_add.day = day;
    fs_add.month = month;
    fs_add.year = year;
    fs_add.fees = fees;

    films_library.push_back(fs_add);
    struct_cnt++;

    sorting();
}

void film_library::delete_film(film_t& film) {

    for (int i = 0; i < films_library.size(); i++)
    {
        if (film == films_library[i])
        {
            films_library.erase(films_library.begin() + i);
            struct_cnt--;
            break;
        }
    }
}

void film_library::save_to_file(string path) {

    ofstream out;
    out.open(path);

    if (!out.is_open()) throw runtime_error("Invalid path");

    for (auto& a : films_library)
    {
        out << a.name << endl;
        out << a.director << endl;
        out << a.screenwriter << endl;
        out << a.composer << endl;
        out << a.day << endl;
        out << a.month << endl;
        out << a.year << endl;
        out << a.fees << endl;
    }
    out.close();
}

int film_library::get_film_index(string name, int year) {

    for (int i = 0; i < films_library.size(); i++)
    {
        if (films_library[i].name == name && films_library[i].year == year) return i;
    }
}

film_library::film_t* film_library::get_film(string name, int year) {

    for (auto& a : films_library)
    {
        if (a.name == name && a.year == year) return &a;
    }
    return nullptr;
}

vector<film_library::film_t> film_library::films_with_year(int year) {

    vector<film_t> films;

    for (auto& a : films_library)
    {
        if (year == a.year) films.push_back(a);
    }

    return films;
}

vector<film_library::film_t> film_library::films_with_director(string director) {

    vector<film_t> films;

    for (auto& a : films_library)
    {
        if (director == a.director) films.push_back(a);
    }

    return films;
}

vector<film_library::film_t> film_library::largest_fees_in_year(int films_quantity, int year) {

    sort_to_fees(films_quantity);
    vector<film_t> films;

    int cnt = 0;
    for (int i = 0; i < films_library.size(); i++)
    {
        if (films_library[i].year == year)
        {
            films.push_back(films_library[i]);
            cnt++;

            if (cnt == 3) break;
        }
    }
    return films;
}

vector<film_library::film_t> film_library::largest_fees(int films_quantity) {

    sort_to_fees(films_quantity);
    vector<film_t> films;

    for (int i = 0; i < films_quantity; i++) films.push_back(films_library[i]);

    return films;
}

film_library::film_t& film_library::operator [](int i) {

    if (i >= struct_cnt || i < 0) throw invalid_argument("Invalid values");

    return films_library[i];
}

film_library::film_library(const film_library& film) { copying(film); }

film_library film_library::operator =(const film_library& film) { copying(film); return *this; }

film_library& film_library::operator +=(const film_library& film) {

    films_library.insert(films_library.end(), film.films_library.begin(), film.films_library.end());
    return *this;
}

film_library film_library::operator +(const film_library& film) {

    film_library new_film;
    new_film.films_library.insert(new_film.films_library.begin(), film.films_library.begin(), film.films_library.end());
    new_film.films_library.insert(new_film.films_library.end(), films_library.begin(), films_library.end());
    return new_film;
}

bool operator ==(const film_library::film_t& left, const film_library::film_t& right) {

    return left.name == right.name &&
        left.director == right.director &&
        left.screenwriter == right.screenwriter &&
        left.composer == right.composer &&
        left.day == right.day &&
        left.month == right.month
        && left.year == right.year
        && left.fees == right.fees;
}

ifstream& operator >>(ifstream& in, film_library& source) {

    source.struct_cnt = (count(istreambuf_iterator<char>(in), istreambuf_iterator<char>(), '\n') + 1) / 8;
    source.films_library.resize(source.struct_cnt);
    in.seekg(0, ios::beg);

    string line;
    int int_line;
    long long int long_int_line;

    for (int i = 0; i < source.struct_cnt; i++)
    {
        film_library::film_t film;

        getline(in, line);
        source.films_library[i].name = line;

        getline(in, line);
        source.films_library[i].director = line;

        getline(in, line);
        source.films_library[i].screenwriter = line;

        getline(in, line);
        source.films_library[i].composer = line;

        getline(in, line);
        int_line = stoi(line);
        source.films_library[i].day = int_line;

        getline(in, line);
        int_line = stoi(line);
        source.films_library[i].month = int_line;

        getline(in, line);
        int_line = stoi(line);
        source.films_library[i].year = int_line;

        getline(in, line);
        long_int_line = stoll(line);
        source.films_library[i].fees = long_int_line;
    }
    return in;
}

ostream& operator <<(ostream& stream, const film_library& source) {

    for (auto& a : source.films_library) stream << a;
    return stream;
}

ostream& operator <<(ostream& stream, const vector<film_library::film_t>& source) {

    for (auto& a : source) stream << a;
    return stream;
}

ostream& operator <<(ostream& stream, const film_library::film_t& source) {

    stream << "Название: '" << source.name << "'" << endl << "режиссер: " << source.director << endl;
    stream << "сценарист: " << source.screenwriter << endl << "композитор: " << source.composer << endl;
    stream << "дата: " << source.day << '.' << source.month << '.' << source.year << endl;
    stream << "сборы (в рублях): " << source.fees << endl << endl;

    return stream;
}

void film_library::copying(const film_library& film) {

    films_library = film.films_library;
    struct_cnt = film.struct_cnt;
    path = film.path;

    for (int i = 0; i < film.films_library.size(); i++)
    {
        films_library[i] = film.films_library[i];
    }
}

void film_library::sort_to_fees(int N) {

    if (N > struct_cnt || N < 1) throw invalid_argument("Invalid values");

    sort(films_library.begin(), films_library.end(),
        [](const film_t& x, const film_t& y) {

            return x.fees > y.fees; });
}

void film_library::sorting() {

    sort(films_library.begin(), films_library.end(),
        [](const film_t& x, const film_t& y) {

            if (x.name < y.name) return true;

            if (y.name < x.name) return false;

            return x.year < y.year; });
}

#pragma once

#include <vector>

using namespace std;

class film_library {

public:
    struct film_t {

        string name;
        string director;
        string screenwriter;
        string composer;
        int day = 0;
        int month = 0;
        int year = 0;
        long long int fees = 0;
    };

	film_library(string path);

    film_library();

	int get_quantity();

    void add_film(string name,
        string director,
        string screenwriter,
        string composer,
        int day,
        int month,
        int year,
        long long int fees);

    void delete_film(film_t& film);

    void save_to_file(string path);

    int get_film_index(string name, int year);

    film_t* get_film(string name, int year);

    vector<film_t*> films_with_year(int year);

    vector<film_t*> films_with_director(string director);

    vector<film_t*> largest_fees_in_year(int films_quantity, int year);

    vector<film_t*> largest_fees(int films_quantity);

    film_t& operator [](int i);

    film_library(const film_library& film);

    film_library operator =(const film_library& film);

    film_library& operator +=(const film_library& film);

    film_library film_library::operator +(const film_library& film);

    friend bool operator ==(const film_t& left, const film_t& right);

    friend ifstream& operator >>(ifstream& in, film_library& source);

    friend ostream& operator <<(ostream& stream, const film_library& source);

    friend ostream& operator <<(ostream& stream, const vector<film_t>& source);

    friend ostream& operator <<(ostream& stream, const film_t& source);

private:
    int struct_cnt;
    vector<film_t> films_library;
    string path;

    void copying(const film_library& film);

    void sort_to_fees(int N);

    void sorting();
};
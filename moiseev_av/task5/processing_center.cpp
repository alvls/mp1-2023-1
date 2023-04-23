#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "processing_center.h"

processing_center::processing_center() : client_cnt(-1) {

        ifstream in;
        in.open(path);

        if (!in.is_open()) throw runtime_error("Invalid path");

        in >> *this;
        in.close();
}

void processing_center::save_data() {

    ofstream out;
    out.open(path);

    if (!out.is_open()) throw runtime_error("Invalid path");

    for (auto& a : data)
    {
        out << a.id << endl;
        out << a.card_number << endl;
        out << a.name << endl;
        out << a.amount << endl;
        out << a.pin << endl;
        out << a.lock << endl;
    }
    out.close();
}

ifstream& operator >>(ifstream& in, processing_center& source) {

    source.client_cnt = (count(istreambuf_iterator<char>(in), istreambuf_iterator<char>(), '\n') + 1) / 6;
    source.data.resize(source.client_cnt);
    in.seekg(0, ios::beg);

    string line;
    int int_line;

    for (int i = 0; i < source.client_cnt; i++)
    {
        getline(in, line);
        int_line = stoi(line);
        source.data[i].id = int_line;

        getline(in, line);
        int_line = stoi(line);
        source.data[i].card_number = int_line;

        getline(in, line);
        source.data[i].name = line;

        getline(in, line);
        int_line = stoi(line);
        source.data[i].amount = int_line;

        getline(in, line);
        int_line = stoi(line);
        source.data[i].pin = int_line;

        getline(in, line);
        int_line = stoi(line);
        source.data[i].lock = int_line;
    }
    return in;
}

ostream& operator <<(ostream& stream, const processing_center& source) {

    for (auto& a : source.data) stream << a;
    return stream;
}

ostream& operator <<(ostream& stream, const vector<processing_center::client>& source) {

    for (auto& a : source) stream << a;
    return stream;
}

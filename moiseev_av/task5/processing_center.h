#pragma once
#include <vector>

using namespace std;


class processing_center {

public:
    struct client
    {
        int id = -1;
        int card_number = -1;
        string name;
        int amount = -1;
        int pin = -1;
        int lock = -1;
    };

    struct encoded_client
    {
        string id = "****";
        int card_number = -1;
        string name;
        string amount = "****";
        string pin = "****";
        int lock = -1;
    };

    vector<client> data;

    processing_center();

    void save_data();

private:
    int client_cnt;
    string path = "data.txt";

    friend ifstream& operator >>(ifstream& in, processing_center& source);

    friend ostream& operator <<(ostream& stream, const processing_center& source);

    friend ostream& operator <<(ostream& stream, const vector<client>& source);

    template <class T>
    friend ostream& operator <<(ostream& stream, const T& source) {
        //constexpr bool is_int_or_double_v =
        //    is_same<T, client>::value || is_same<T, encoded_client>::value;

        stream << "Клиент № " << source.id << endl << "Номер карты: " << source.card_number << endl;
        stream << "ФИО: " << source.name << endl << "Баланс: " << source.amount << endl;
        stream << "PIN-код: " << source.pin << endl;
        source.lock == 0 ? (stream << "Карта разблокирована" << endl) : (stream << "Карта заблокирована" << endl);

        return stream;
    }
};
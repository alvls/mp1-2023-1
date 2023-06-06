#include <iostream>
#include <fstream>
#include <string>

#include "atm.h"

using namespace std;

atm::atm(processing_center center, string logs_path) : center(), logs_path(logs_path),
    attempt(0), client_id(-1), card_in(false), verification(false) {

    GetLocalTime(&st);
    if (sum_of_cas() < (bill_max * cassettes.size() * 0.3)) set_logs("WARNING! Сassettes are lower 30%");
    if (sum_of_cas() > (bill_max * cassettes.size() * 0.9)) set_logs("WARNING! Сassettes are over 90%");
};

processing_center::encoded_client atm::get_client(int card_number) {

    for (int i = 0; i < center.data.size(); i++)
    {
        if (center.data[i].card_number == card_number)
        {
            processing_center::encoded_client en_client;
            en_client.card_number = center.data[i].card_number;
            en_client.name = center.data[i].name;
            en_client.lock = center.data[i].lock;

            return en_client;
        }
    }
    throw exception("Not a bank client");
}

bool atm::take_card(int card_number) {

    if (card_in) throw exception("Сard is already taken");

    for (int i = 0; i < center.data.size(); i++)
    {
        if (center.data[i].card_number == card_number)
        {
            client_id = i;
            card_in = true;
            set_logs("Card №" + to_string(center.data[i].card_number) + " is in");
            return true;
        }
    }

    throw exception("Not a bank client");
}

bool atm::check_pin(int pin) {

    check_card();
    if (verification) throw exception("Verification is already done");
    if (center.data[client_id].pin == pin) { attempt = 0;  verification = true; return true; }

    else
    {
        attempt++;

        if (attempt == 3)
        {
            center.data[client_id].lock = 1;
            set_logs("Card №" + to_string(center.data[client_id].card_number) + " is locked");
        }
        center.save_data();
        return false;
    }
}

int atm::get_amount() {

    check_card();
    if (!verification) throw exception("Enter pin");
    return center.data[client_id].amount;
}

int atm::get_money(int quantity) {

    check_card();
    if (!verification) throw exception("Enter pin");
    if ((quantity % 100 != 0) ||
        (quantity > center.data[client_id].amount)) throw exception("Incorrect value");

    distribution(quantity);

    center.data[client_id].amount -= quantity;
    center.save_data();

    set_logs("Get " + to_string(quantity) + " rub from card №" +
        to_string(center.data[client_id].card_number));

    if (sum_of_cas() < (bill_max * cassettes.size() * 0.3)) set_logs("WARNING! Сassettes are lower 30%");

    return quantity;
}

void atm::take_money(int quantity, int _100, int _200, int _500,
    int _1000, int _2000, int _5000) {                         
                                                            // Так как мы не знаем, какого номанила купюры поступят 
    check_card();                                          // от пользователя, то подразумевается, что банкомат считывает  
                                                          // купюры и затем вызывает данный метод уже с
    if (!verification) throw exception("Enter pin");     // распознаным количеством купюр различного номинала
    if ((_100 + _200 + _500 + _1000
        + _2000 + _5000) > 40) throw exception("Quantity of banknotes over 40");

    vector<int> banknotes{ _100, _200, _500, _1000, _2000, _5000 };

    for (int i = 0; i < cassettes.size(); i++)
    {
        if ((cassettes[i] + banknotes[i]) > bill_max) throw exception("Cassette is full");
    }

    for (int i = 0; i < cassettes.size(); i++) cassettes[i] += banknotes[i];

    center.data[client_id].amount += quantity;
    center.save_data();

    if (sum_of_cas() > (bill_max * cassettes.size() * 0.9)) set_logs("WARNING! Сassettes are over 90%");

    set_logs("Take " + to_string(quantity) + " rub to card №" + to_string(center.data[client_id].card_number));
}

void atm::get_card() {

    if (!card_in) throw exception("No card");

    set_logs("Card №" + to_string(center.data[client_id].card_number) + " is out");
    client_id = -1;
    card_in = false;
}

void atm::check_card() {

    if (!card_in) throw exception("No card");
    if (center.data[client_id].lock == 1) throw exception("Card is locked");
}

void atm::distribution(int quantity) {

    int cnt = 0;
    vector<int> clone = cassettes;
    vector<int> denomination{ 100, 200, 500, 1000, 2000, 5000 };

    for (int i = denomination.size() - 1; i >= 0; i--)
    {
        if (cnt > 40) throw exception("Banknotes over 40");

        if (clone[i] > 0)
        {
            if (quantity % denomination[i] == 0)
            {
                cnt += quantity / denomination[i];
                if (cnt > 40) throw exception("Banknotes over 40");

                clone[i] -= quantity / denomination[i];
                for (int j = 0; j < cassettes.size(); j++) cassettes[j] = clone[j];

                return;
            }

            if (denomination[i] <= quantity)
            {
                while (((quantity - denomination[i]) >= 0) && (clone[i] > 0))
                {
                    quantity -= denomination[i];
                    clone[i]--;
                    cnt++;
                }
            }
            else continue;
        }
        else continue;
    }

    throw exception("Cassettes are empty");
}

void atm::set_logs(string line) {

    ofstream out;
    out.open(logs_path, ios::app);

    if (!out.is_open()) throw runtime_error("Invalid path");

    out << line << ", at: " << st.wYear << '.' << st.wMonth << '.' << st.wDay
        << ' ' << st.wHour << ':' << st.wMinute << ':' << st.wSecond << endl;

    out.close();
}

int atm::sum_of_cas() {

    int cnt = 0;
    for (int i = 0; i < cassettes.size(); i++) cnt += cassettes[i];
    return cnt;
}

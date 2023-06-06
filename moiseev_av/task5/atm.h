#pragma once
#include <windows.h>

#include "processing_center.h"

using namespace std;


class atm {

public:
    atm(processing_center center, string logs_path);

    processing_center::encoded_client get_client(int card_number);

    bool take_card(int card_number);

    bool check_pin(int pin);

    int get_amount();

    int get_money(int quantity);

    void take_money(int quantity, int _100, int _200, int _500,
        int _1000, int _2000, int _5000);

    void get_card();
    
private:
    int attempt;
    int client_id;
    bool card_in;
    bool verification;
    string logs_path;

    SYSTEMTIME st;
    processing_center center;

    int bill_max = 2000;
    int cassette_100 = 1600;
    int cassette_200 = 1600;
    int cassette_500 = 1600;
    int cassette_1000 = 1600;
    int cassette_2000 = 1600;
    int cassette_5000 = 1600;

    vector<int> cassettes{ cassette_100, cassette_200, cassette_500,
    cassette_1000, cassette_2000, cassette_5000 };

    void check_card();

    void distribution(int quantity);

    void set_logs(string line);

    int sum_of_cas();
};
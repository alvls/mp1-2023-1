#pragma once

#include <iostream>
#include <stdexcept>
#include <map>

#include "processing_center.h"
#include "client.h"

class ProcessingCenter;
class Client;

const int FIRST_MONEY_BORDER   = 100000;
const int SECOND_MONEY_BORDER  = 500000;
const int THIRD_MONEY_BORDER   = 1000000;

// available terms (in months)
enum Terms {
    threeMonths = 3,
    sixMonths = 6,
    oneYear = 12,
    twoYears = 24,
    threeYears = 36
};

// available interest
static std::map <Terms, double> interestRates = { {threeMonths, 5.8},
                                                  {sixMonths, 6.0},
                                                  {oneYear, 6.6},
                                                  {twoYears, 8.2},
                                                  {threeYears, 10.0} };

class Deposit {
public:
    static bool IsAuthorized(const ProcessingCenter& processingCenter, const Client& client);

    static void Authorize(ProcessingCenter& processingCenter, const Client& client);

    static void ShowAvailableDepositsInfo(const Client& client);

    static bool IsOpened(const Client& client);

    static void Open(Client& client, int initialTerm, int currentTerm, int initialDepositAmount);

    static void ShowInfo(const Client& client);

    static void WithdrawMoneyFromInterest(Client& client, int amount);

    static void Close(Client& client);
};

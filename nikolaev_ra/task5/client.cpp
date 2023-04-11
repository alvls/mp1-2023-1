#include "deposit.h"
#include "client.h"

Client::Client(const std::string &id, const std::string &fullName, int salaryAmount, const std::string &password) {
    SetId(id);
    SetFullName(fullName);
    SetSalaryAmount(salaryAmount);
    SetPassword(password);
}

const std::string &Client::GetId() const {
    return id;
}

void Client::SetId(const std::string &id) {
    if (id.length() != 4) {
        throw std::invalid_argument("Incorrect salary account ID value!");
    }
    for (char i : id) {
        if (i < '0' || i > '9') {
            throw std::invalid_argument("Incorrect salary account ID value!");
        }
    }
    Client::id = id;
}

const std::string &Client::GetFullName() const {
    return fullName;
}

void Client::SetFullName(const std::string &fullName) {
    Client::fullName = fullName;
}

int Client::GetSalaryAmount() const {
    return salaryAmount;
}

void Client::SetSalaryAmount(int salaryAmount) {
    if (salaryAmount < 0) {
        throw std::invalid_argument("Incorrect salary amount value!");
    }
    Client::salaryAmount = salaryAmount;
}

const Client::DepositInfo &Client::GetDepositInfo() const {
    return depositInfo;
}

const std::string &Client::GetPassword() const {
    return password;
}

void Client::SetPassword(const std::string &password) {
    if (password.length() < MIN_PASSWORD_LENGTH) {
        throw std::invalid_argument("The entered password is too short! (minimum 4 characters)");
    }
    Client::password = password;
}

void Client::SetDepositInfo(int initialTerm, int currentTerm, int initialDepositAmount) {
    if (initialTerm == 0 && currentTerm == 0 && initialDepositAmount == 0) {
        return;
    }
    if (initialTerm == 0 || initialDepositAmount == 0) {
        throw std::invalid_argument("Incorrect deposit data!");
    }
    if (initialTerm != threeMonths && initialTerm != sixMonths &&
        initialTerm != oneYear && initialTerm != twoYears && initialTerm != threeYears) {
        throw std::invalid_argument("Incorrect initial deposit term!");
    }
    Client::depositInfo.initialTerm = initialTerm;
    if (currentTerm < 0 || currentTerm > initialTerm) {
        throw std::invalid_argument("Incorrect current deposit term!");
    }
    Client::depositInfo.currentTerm = currentTerm;

    if (initialDepositAmount < FIRST_MONEY_BORDER) {
        Client::depositInfo.initialAmountRange = 1;
    } else if (initialDepositAmount < SECOND_MONEY_BORDER) {
        Client::depositInfo.initialAmountRange = 2;
    } else if (initialDepositAmount < THIRD_MONEY_BORDER) {
        Client::depositInfo.initialAmountRange = 3;
    } else {
        Client::depositInfo.initialAmountRange = 4;
    }

    if (initialDepositAmount < 0) {
        throw std::invalid_argument("Incorrect initial deposit amount!");
    }
    Client::depositInfo.initialDepositAmount = initialDepositAmount;
    for (auto &intRate : interestRates) {
        if (intRate.first == initialTerm) {
            Client::depositInfo.interestRate = intRate.second;
        }
    }
    if (Client::depositInfo.interestRate == 0) { throw std::runtime_error("Incorrect interest rate!"); }
    Client::depositInfo.isOpened = true;

    // To simplify, we use integers (as indicated in the assignment)
    Client::depositInfo.interestAmount = (int)(initialDepositAmount *
            0.01*Client::depositInfo.interestRate * currentTerm / 12);
}

void Client::SetInterestAmount(int interestAmount) {
    depositInfo.interestAmount = interestAmount;
}

void Client::SetIsOpened(bool isOpened) {
    depositInfo.isOpened = isOpened;
}



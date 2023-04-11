#include "deposit.h"

bool Deposit::IsAuthorized(const ProcessingCenter& processingCenter, const Client& client) {
    std::pair<std::string, std::string> clientData = std::make_pair(client.GetId(), client.GetPassword());
    for (auto& user : processingCenter.GetClients()) {
        if (user.GetId() == clientData.first && user.GetPassword() != clientData.second) {
            throw std::runtime_error("A user with such a salary account exists, but the passwords do not match!");
        }
        if (user.GetId() == clientData.first && user.GetPassword() == clientData.second) {
            return true;
        }
    }
    return false;
}

void Deposit::Authorize(ProcessingCenter& processingCenter, const Client& client) {
    if (IsAuthorized(processingCenter, client)) {
        throw std::runtime_error("The user with the specified salary account is already authorized!");
    }
    processingCenter.AddClient(client);
}

void Deposit::ShowAvailableDepositsInfo(const Client& client) {
    if (client.GetSalaryAmount() == 0) {
        std::cout << "You do not have funds to make a deposit." << std::endl;
        return;
    }
    std::cout << "Available terms for the formation of the deposit:" << std::endl;
    std::cout << threeMonths << " months." << std::endl;
    std::cout << sixMonths << " months." << std::endl;
    std::cout << oneYear << " months." << std::endl;
    std::cout << twoYears << " months." << std::endl;
    std::cout << threeYears << " months." << std::endl;

    std::cout << "\nAvailable categories for initial amounts:" << std::endl;
    std::cout << "1. Up to " << FIRST_MONEY_BORDER << " rubbles" << std::endl;
    if (client.GetSalaryAmount() > FIRST_MONEY_BORDER) {
        std::cout << "2. From " << FIRST_MONEY_BORDER << " to " << SECOND_MONEY_BORDER << " rubbles" << std::endl;
    }
    if (client.GetSalaryAmount() > SECOND_MONEY_BORDER) {
        std::cout << "3. From " << SECOND_MONEY_BORDER << " to " << THIRD_MONEY_BORDER << " rubbles" << std::endl;
    }
    if (client.GetSalaryAmount() > THIRD_MONEY_BORDER) {
        std::cout << "4. Over " << THIRD_MONEY_BORDER << " rubbles" << std::endl;
    }
}

bool Deposit::IsOpened(const Client& client) {
    return client.GetDepositInfo().isOpened;
}

void Deposit::Open(Client& client, int initialTerm, int currentTerm, int initialDepositAmount) {
    if (IsOpened(client)) {
        throw std::runtime_error("The deposit has already been opened!");
    }
    if (client.GetSalaryAmount() < initialDepositAmount) {
        throw std::invalid_argument("The amount of the deposit is greater than the amount on the salary account!");
    }
    client.SetSalaryAmount(client.GetSalaryAmount() - initialDepositAmount);
    client.SetDepositInfo(initialTerm, currentTerm, initialDepositAmount);
}

void Deposit::ShowInfo(const Client& client) {
    auto clientDepositInfo = client.GetDepositInfo();
    std::cout << "Deposit status: ";
    if (!clientDepositInfo.isOpened) {
        std::cout << "not opened." << std::endl;
        return;
    } else {
        std::cout << "opened." << std::endl;
    }
    std::cout << "Initial term: " << clientDepositInfo.initialTerm << " months." << std::endl;
    std::cout << "Current term: " << clientDepositInfo.currentTerm << " months." << std::endl;
    std::cout << "Initial deposit amount: " << clientDepositInfo.initialDepositAmount << " rubbles." << std::endl;
    std::cout << "Interest amount: " << clientDepositInfo.interestAmount << " rubbles." << std::endl;
    std::cout << "Interest rate: " << clientDepositInfo.interestRate << "%." << std::endl;
}

void Deposit::WithdrawMoneyFromInterest(Client& client, int amount) {
    if (amount > client.GetDepositInfo().interestAmount) {
        throw std::invalid_argument("Insufficient funds to withdraw!");
    }
    client.SetInterestAmount(client.GetDepositInfo().interestAmount - amount);
    client.SetSalaryAmount(client.GetSalaryAmount() + amount);
}

void Deposit::Close(Client& client) {
    if (client.GetDepositInfo().initialTerm != client.GetDepositInfo().currentTerm) {
        throw std::invalid_argument("Unable to close the deposit before its expiration date!");
    }
    else {
        client.SetSalaryAmount(client.GetSalaryAmount() + client.GetDepositInfo().initialDepositAmount + client.GetDepositInfo().interestAmount);
        client.SetDepositInfo(0, 0, 0);
        client.SetIsOpened(false);
        client.SetInterestAmount(0);
    }
}
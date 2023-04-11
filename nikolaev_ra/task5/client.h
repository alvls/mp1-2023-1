#pragma once

#include <string>
#include <stdexcept>

const int MIN_PASSWORD_LENGTH = 4;

class Client {
private:
    std::string id{};
    std::string fullName{};
    int salaryAmount{};
    std::string password{};

    struct DepositInfo {
        bool isOpened{};
        int initialTerm{};
        int currentTerm{};
        int initialAmountRange{};
        int initialDepositAmount{};
        int interestAmount{};
        double interestRate{};
    } depositInfo;

public:
    Client(const std::string &id, const std::string& fullName, int salaryAmount, const std::string& password);

    [[nodiscard]] const std::string &GetId() const;

    void SetId(const std::string &id);

    [[nodiscard]] const std::string &GetFullName() const;

    void SetFullName(const std::string &fullName);

    [[nodiscard]] int GetSalaryAmount() const;

    void SetSalaryAmount(int salaryAmount);

    [[nodiscard]] const std::string &GetPassword() const;

    void SetPassword(const std::string &password);

    [[nodiscard]] const DepositInfo &GetDepositInfo() const;

    void SetDepositInfo(int initialTerm, int currentTerm, int initialDepositAmount);

    void SetInterestAmount(int interestAmount);

    void SetIsOpened(bool isOpened);
};

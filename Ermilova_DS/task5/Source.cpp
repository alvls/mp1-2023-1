#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

class Client
{
    bool authorized;
    string AccountNumbers{};
    string Name{};
    int SalaryAmount{};
    string Password{};

    struct DepositInformation
    {
        bool DepositOpen{};
        int DepositTerm{};
        int CurrentTerm{};
        int initialDepositAmount{};
        int InterestAmount{};
        double InterestRate{};
    } depositInformation;

public:

    Client()
    {

    }

    void SetAuthorization(bool value)
    {
        authorized = value;
    }

    bool IsAuthorized() const
    {
        return authorized;
    }

    void SetAccountNumbers(const string& account)
    {
        if (account.length() != 4)
        {
            throw invalid_argument("Wrong account number!");
        }
        if (account[0] < '0' || account[0] > '9')
        {
            throw invalid_argument("Wrong account number!");
        }
        if (account[1] < '0' || account[1] > '9')
        {
            throw invalid_argument("Wrong account number!");
        }
        if (account[2] < '0' || account[2] > '9')
        {
            throw invalid_argument("Wrong account number!");
        }
        if (account[3] < '0' || account[3] > '9')
        {
            throw invalid_argument("Wrong account number!");
        }
        if (account == "0000")
        {
            throw invalid_argument("Wrong account number!");
        }
        AccountNumbers = account;
    }

    const string& GetAccountNumbers() const
    {
        return AccountNumbers;
    }

    void SetName(const string& name)
    {
        Name = name;
    }

    const string& GetName() const
    {
        return Name;
    }

    void SetSalaryAmount(int salaryAmount)
    {
        if (salaryAmount < 0)
        {
            throw invalid_argument("Incorrect amount on the salary account!");
        }
        SalaryAmount = salaryAmount;
    }

    int GetSalaryAmount() const
    {
        return SalaryAmount;
    }

    void SetPassword(const string& password)
    {
        if (password.length() < 4)
        {
            throw invalid_argument("The password is too short! Minimum 4 characters required!");
        }
        Password = password;
    }

    const string& GetPassword() const
    {
        return Password;
    }

    void SetDepositInformation(int depositTerm, int currentTerm, int initialDepositAmount)
    {
        if (depositTerm != 3 && depositTerm != 6 && depositTerm != 12 && depositTerm != 24 && depositTerm != 36)
        {
            throw invalid_argument("Incorrect date!");
        }
        depositInformation.DepositTerm = depositTerm;

        if (depositTerm != 3 && depositTerm != 6 && depositTerm != 12 && depositTerm != 24 && depositTerm != 36)
        {
            throw invalid_argument("Incorrect date!");
        }
        depositInformation.DepositTerm = depositTerm;

        if (initialDepositAmount < 0)
        {
            throw invalid_argument("Incorrect initial deposit amount!");
        }
        if (currentTerm < 0 || currentTerm > depositTerm)
        {
            throw invalid_argument("Incorrect current date!");
        }
        depositInformation.CurrentTerm = currentTerm;

        double IR;
        if (initialDepositAmount < 100000)
        {
            IR = 1.0;
        }
        if (100000 < initialDepositAmount <= 500000)
        {
            IR = 1.3;
        }
        if (500000 < initialDepositAmount <= 1000000)
        {
            IR = 1.5;
        }
        else
        {
            IR = 1.8;
        }

        double ir;
        switch (depositInformation.DepositTerm)
        {
        case 3:
            ir = 5.5;
            break;
        case 6:
            ir = 6.0;
            break;
        case 12:
            ir = 6.6;
            break;
        case 24:
            ir = 7.4;
            break;
        default:
            ir = 8.0;
        }
        depositInformation.DepositOpen = true;
        depositInformation.initialDepositAmount = initialDepositAmount;
        depositInformation.InterestRate = ir * IR;
        depositInformation.InterestAmount = int(initialDepositAmount * depositInformation.InterestRate * currentTerm / 12 / 100);
    }

    const DepositInformation& GetDepositInformation() const
    {
        return depositInformation;
    }

    void SetInterestAmount(int interestAmount)
    {
        depositInformation.InterestAmount = interestAmount;
    }

    void SetDepositOpen(bool depositOpen)
    {
        depositInformation.DepositOpen = depositOpen;
    }
};

class ProcessingCenter
{
    vector<Client> clients{};

public:
    void AddClient(const Client& client)
    {
        clients.push_back(client);
    }

    const vector<Client>& GetClients() const
    {
        return clients;
    }
};

class Deposit
{
public:

    static void Authorization(const ProcessingCenter& processingCenter, const string accountNumbers, const string password, Client& currClient)
    {
        pair<string, string> clientAuto = make_pair(accountNumbers, password);
        for (auto& current— : processingCenter.GetClients())
        {
            if (current—.GetAccountNumbers() == clientAuto.first && current—.GetPassword() != clientAuto.second)
            {
                throw runtime_error("Incorrect password!");
            }
            if (current—.GetAccountNumbers() == clientAuto.first && current—.GetPassword() == clientAuto.second)
            {
                currClient = current—;
                currClient.SetAuthorization(true);
                if (currClient.IsAuthorized())
                {
                    cout << "Successful authorization!" << endl;
                    return;
                }
            }
        }
        throw runtime_error("Such account number doesn't exist");
    }

    static void NewClient(ProcessingCenter& processingCenter, const Client& client)
    {
        string temp = client.GetAccountNumbers();
        for (auto& user : processingCenter.GetClients())
            if (user.GetAccountNumbers() == temp)
                throw runtime_error("A user with such account number already exists");
        processingCenter.AddClient(client);
    }

    static void ShowDepositsInformation(const Client& client)
    {
        if (client.GetSalaryAmount() == 0)
        {
            throw runtime_error("Not enough funds to open a deposit!");
        }
        cout << "Amounts of available deposits:\n";
        cout << "From 100000 rubbles rate from 5.5%\n";
        if (client.GetSalaryAmount() > 100000)
        {
            cout << "From 100000 to 500000 rubbles rate from 7.15%\n";
        }
        if (client.GetSalaryAmount() > 500000)
        {
            cout << "From 500000 to 1000000 rubbles rate from 8.25%\n";
        }
        if (client.GetSalaryAmount() > 1000000)
        {
            cout << "Over 1000000 rubbles rate from 9.9%\n";
        }
    }

    static bool IsOpen(const Client& client)
    {
        return client.GetDepositInformation().DepositOpen;
    }

    static void OpenDeposit(Client& client, int depositTerm, int currentTerm, int initialDepositAmount)
    {
        if (IsOpen(client) == true)
        {
            throw runtime_error("The deposit is already open! You cannot open more than one deposit!");
        }
        if (client.GetSalaryAmount() < initialDepositAmount)
        {
            throw runtime_error("Not enough funds to open a deposit!");
        }
        client.SetDepositInformation(depositTerm, currentTerm, initialDepositAmount);
        client.SetSalaryAmount(client.GetSalaryAmount() - initialDepositAmount);

    }

    static void ShowInformationYourDeposit(const Client& client)
    {
        auto clientDepositInfo = client.GetDepositInformation();
        cout << "Deposit status:\n";
        if (clientDepositInfo.DepositOpen == false)
        {
            cout << "No open deposits!\n";
            return;
        }
        else
        {
            cout << "Deposit Term: " << clientDepositInfo.DepositTerm << " months.\n" << "Current Term: " << clientDepositInfo.CurrentTerm << " months.\n" << "Initial deposit amount: " << clientDepositInfo.initialDepositAmount << " rubbles.\n" << "Interest amount: " << clientDepositInfo.InterestAmount << " rubbles.\n" << "Interest rate: " << clientDepositInfo.InterestRate << "%.\n";
        }
    }

    static void WithdrawInterest(Client& client, int amount)
    {
        if (amount > client.GetDepositInformation().InterestAmount)
        {
            throw runtime_error("Insufficient funds to withdraw!");
        }
        else
        {
            client.SetInterestAmount(client.GetDepositInformation().InterestAmount - amount);
            client.SetSalaryAmount(client.GetSalaryAmount() + amount);
        }
    }

    static void Close(Client& client)
    {
        if (client.GetDepositInformation().CurrentTerm != client.GetDepositInformation().DepositTerm)
        {
            throw runtime_error("You cannot close the deposit until the expiration date!\n");
        }
        else
        {
            client.SetDepositOpen(false);
            client.SetSalaryAmount(client.GetSalaryAmount() + client.GetDepositInformation().initialDepositAmount + client.GetDepositInformation().InterestAmount);
            client.SetInterestAmount(0);
            client.SetDepositInformation(0, 0, 0);
        }
    }
};


int main() {

    ProcessingCenter p;
    Deposit d;
    int choice = 9999;
    int money, withdraw, dTerm, currTerm, depSum;
    string accountNumbers, name, password;
    Client currClient;
    while (choice != 0) {
        cout << "\nPress 1 if you are not registered in the system yet\nPress 2 to login\nPress 3 show information about available deposits based on the amount in the salary account\nPress 4 to check if there is an open deposit\nPress 5 to open a deposit\nPress 6 to show deposit status\nPress 7 to withdraw interest\nPress 8 to close the deposit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter account numbers" << endl;
            cin >> accountNumbers;
            cout << "Enter a full name" << endl;
            cin >> name;
            cout << "Enter the amount of money in your salary account" << endl;
            cin >> money;
            cout << "Enter the password" << endl;
            cin >> password;
            currClient.SetAccountNumbers(accountNumbers);
            currClient.SetName(name);
            currClient.SetSalaryAmount(money);
            currClient.SetPassword(password);
            d.NewClient(p, currClient);;
            break;
        case 2:
            cout << "Enter account number" << endl;
            cin >> accountNumbers;
            cout << "Enter the password" << endl;
            cin >> password;
            d.Authorization(p, accountNumbers, password, currClient);
            break;
        case 3:
            try
            {
                d.ShowDepositsInformation(currClient);
            }
            catch (const char* ex)
            {
                cout << ex << endl;
            }
        case 4:
            try
            {
                if (!d.IsOpen(currClient))
                {
                    cout << "Deposit not opened!\n";
                }
                else
                {
                    cout << "Deposit is open!\n";
                }
            }
            catch (const char* ex)
            {
                cout << ex << endl;
            }
            break;
        case 5:
            cout << "Enter the deposit term (3 months, 6 months, 12 months, 24 months, 36 months)" << endl;
            cin >> dTerm;
            cout << "Enter the current term" << endl;
            cin >> currTerm;
            cout << "Enter the deposit amount" << endl;
            cin >> depSum;
            try
            {
                d.OpenDeposit(currClient, dTerm, currTerm, depSum);
            }
            catch (const char* ex)
            {
                cout << ex << endl;
            }
            break;
        case 6:
            try
            {
                d.ShowInformationYourDeposit(currClient);
            }
            catch (const char* ex)
            {
                cout << ex << endl;
            }
            break;
        case 7:
            cout << "How much money to withdraw?" << endl;
            cin >> withdraw;
            try
            {
                d.WithdrawInterest(currClient, withdraw);
            }
            catch (const char* ex)
            {
                cout << ex << endl;
            }
            break;
        case 8:
            try
            {
                d.Close(currClient);
            }
            catch (const char* ex)
            {
                cout << ex << endl;
            }
            break;
        default:
            break;
        }
    }
    system("pause");
}
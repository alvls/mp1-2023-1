#include "client.h"
#include "deposit.h"

int main(int argc, char* argv[]) {
    std::cout << "Welcome to the demo!" << std::endl;
    std::cout << "Since the examples are large, you will have to scroll through the console a little, I hope this will not cause you much inconvenience :)" << std::endl;

    system("pause");
    system("cls");

    std::cout << "Creating a processing center." << std::endl;
    ProcessingCenter processingCenter;

    std::cout << "Let's create some clients." << std::endl;
    Client firstClient{"0009", "Ivanov Petr Sergeevich", 250000, "qwerty123"};
    Client secondClient{"1451", "Sidorov Alexander Vasilevich", 1600000, "yTE4oI8"};
    Client thirdClient{"3078", "Tsvetkov Igor Vyacheslavovich", 87000, "123456"};
    Client fourthClient{"7554", "Ruchkin Ivan Petrovich", 770500, "veryStrongPassword"};
    Client fifthClient{"9912", "Ignatiev Andrey Romanovich", 580320, "f3ghK3G2"};

    std::cout << "Let's authorize them." << std::endl;
    Deposit::Authorize(processingCenter, firstClient);
    Deposit::Authorize(processingCenter, secondClient);
    Deposit::Authorize(processingCenter, thirdClient);
    Deposit::Authorize(processingCenter, fourthClient);
    Deposit::Authorize(processingCenter, fifthClient);

    std::cout << "\nNow let's fill in the information about deposits.\n" << std::endl;
    firstClient.SetDepositInfo(24, 6, 150000);
    secondClient.SetDepositInfo(0, 0, 0);
    thirdClient.SetDepositInfo(3, 3, 20000);
    fourthClient.SetDepositInfo(12, 8, 600000);
    fifthClient.SetDepositInfo(0, 0, 0);

    std::cout << "Displaying information about the deposits of some clients: " << std::endl;
    std::cout << "Client 1 -> ";
    Deposit::ShowInfo(firstClient);
    std::cout << "\nClient 2 -> ";
    Deposit::ShowInfo(secondClient);
    std::cout << "\nClient 5 -> ";
    Deposit::ShowInfo(fifthClient);

    std::cout << "\nClients 2 and 5 have no deposits. Let's see what options they have: " << std::endl;
    std::cout << "Client 2 -> ";
    Deposit::ShowAvailableDepositsInfo(secondClient);
    std::cout << "\nClient 5 -> ";
    Deposit::ShowAvailableDepositsInfo(fifthClient);

    std::cout << "\nNow let's open deposits for them." << std::endl;
    Deposit::Open(secondClient, 36, 0, 400000);
    Deposit::Open(fifthClient, 6, 0, 320000);

    std::cout << "\nDisplaying information client's (for example, 2) deposit again: " << std::endl;
    std::cout << "Client 2 -> ";
    Deposit::ShowInfo(secondClient);

    std::cout << "\nLet's take a look at their salary amounts:" << std::endl;
    std::cout << "Client 2: " << secondClient.GetSalaryAmount() << " rubbles." << std::endl;
    std::cout << "Client 5: " << fifthClient.GetSalaryAmount() << " rubbles." << std::endl;
    std::cout << "And as we can see, obviously the values have changed since the money went to the deposit." << std::endl;

    std::cout << "\nSuppose client 1 wanted to withdraw some of the interest (3520 rubbles)." << std::endl;
    Deposit::WithdrawMoneyFromInterest(firstClient, 3520);
    std::cout << "And now his salary amount looks more impressive than it originally was :) : "
        << firstClient.GetSalaryAmount() << " rubbles." << std::endl;

    std::cout << "\nAnd client 3 waited out the entire term of the deposit and is going to close the deposit." << std::endl;
    Deposit::Close(thirdClient);

    std::cout << "Let's check his deposit details now: " << std::endl;
    std::cout << "Client 3 -> ";
    Deposit::ShowInfo(thirdClient);
    std::cout << "And his salary amount is now: " << thirdClient.GetSalaryAmount() << " rubbles." << std::endl;
    std::cout << "(why was it necessary to open a deposit, he earned a penny...)" << std::endl;

    system("pause");
    return EXIT_SUCCESS;
}
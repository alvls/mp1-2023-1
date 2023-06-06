#pragma once

#include <vector>

class Client;

class ProcessingCenter {
private:
    std::vector<Client> clients{};
    int clientsCount{};

public:
    void AddClient(const Client& client);

    [[nodiscard]] const std::vector<Client>& GetClients() const;
};

#include "processing_center.h"
#include "client.h"

void ProcessingCenter::AddClient(const Client& client) {
    ProcessingCenter::clients.push_back(client);
    ProcessingCenter::clientsCount++;
}

const std::vector<Client>& ProcessingCenter::GetClients() const {
    return clients;
}





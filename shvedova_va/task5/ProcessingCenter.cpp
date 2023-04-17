#include "ProcessingCenter.h"
ProcessingCenter::ProcessingCenter() {}
void ProcessingCenter::AddClient(Client c)
{
	ProcessingCenter::clients.push_back(c);
}
Client& ProcessingCenter::operator[](int ind) { return clients[ind]; }
ProcessingCenter::~ProcessingCenter() {}
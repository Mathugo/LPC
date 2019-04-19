#pragma once
#include <iostream>
#include <istream>
#include "Client.h"
class Client;
class Transfer
{
public:
	static bool uploadToClient(Client* client, std::string filename);
	static void screenshot(Client* client);
	static int getSize(std::string filename);
	static void Copy(std::string file_out, std::string file_in);
};
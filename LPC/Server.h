#pragma once
#pragma warning(disable:4996) 
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string.h>
#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "Socket_.h"

struct st_Client
{
	SOCKET sock;
	sockaddr_in addr;
	unsigned int number;
};

class Server : public Socket_
{
private:
	bool exit = 0;
	st_Client default_client;
	int port;
	std::vector<st_Client> clients;

public:
	
	Server(const int pPort);
	~Server();
	void compare(char* pbuffer);
	std::vector<st_Client> getClients();
	bool getExit();
	bool acceptClient();
	bool send_c();
	bool send_b(const char* pbuffer);
	bool recv_b();
};

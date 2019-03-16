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
};

class Server : public Socket_
{
private:
	SOCKET default_sock;
	int port;
	std::vector<st_Client> clients;

public:
	
	Server(const int pPort);
	~Server();
	bool acceptClient();
	bool send_b(const char* buffer);
};

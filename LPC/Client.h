#pragma once
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
#include "Scripts_all.h"
#include "Factory_Client.h"

class Client : public Socket_
{
private:
	std::string Ip;
public:

	void setIp(const std::string& pIp);
	std::string getIp() const;

	bool recv_b();
	bool send_b(const char* buffer);
	bool init();
	Client(const char* addr, const unsigned short &port);
	~Client();
	
};


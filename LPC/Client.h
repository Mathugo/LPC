#pragma once
#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif
#ifdef unix
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <iostream>
#include <string.h>
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
	bool mute = 0;
public:

	void setIp(const std::string& pIp);
	std::string getIp() const;
	void setMute(const bool& pmute);
	bool getMute() const;
	bool recv_b();
	bool send_b(const char* buffer);
	bool init();
	Client(const char* addr, const unsigned short &port);
	~Client();
	
};


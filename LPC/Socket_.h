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
#define SIZE_BUFFER 256

class Socket_
{
private:
	WSAData wsaData;
	SOCKET sock;
	bool error = 0;
	char buffer[SIZE_BUFFER] = { 0 };

public:

	virtual bool send_b(const char* pbuffer)= 0;
	bool recv_b();
	char* getBuffer();
	bool getError();
	SOCKET getSock();
	void setSock(SOCKET psock);
	void setError(const bool perror);
	Socket_();
	~Socket_();
};


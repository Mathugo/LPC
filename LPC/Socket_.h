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

	char type_[256] = { 0 };
	WSAData wsaData;
	SOCKET sock;
	SOCKET* sock_ = &sock;
	bool error = 0;
	char buffer[SIZE_BUFFER] = { 0 };

public:

	char* getBuffer();
	SOCKET* getSock() const;
	char* getType();
	bool getError() const;

	void setBuffer(const char* pbuffer);
	void setSock(const SOCKET& psock);
	void setError(const bool &perror);
	void setType(const char* type);
	void print_buffer();

	Socket_();
	~Socket_();
};


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
	bool error = 0;
	char buffer[SIZE_BUFFER] = { 0 };

public:
	char* getBuffer();
	void setBuffer(const char* pbuffer);
	bool getError();
	void print_buffer();
	SOCKET getSock();
	void setSock(SOCKET psock);
	void setError(const bool perror);
	char* getType();
	void setType(const char* type);
	Socket_();
	~Socket_();
};


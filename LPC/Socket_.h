#pragma once
#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif
#ifdef linux
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#include <iostream>
#include <string.h>
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


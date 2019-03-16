#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 
#pragma warning(disable:4996) 
#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "connection.h"
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 


int main()
{
	const char* addr = "192.168.0.44";
	const unsigned short port = 9999;

	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Erreur initialisation WinSock : " << WSAGetLastError();
		return -1;
	}
	SOCKET sock;
	sock = connection_client(port,addr);

	closesocket(sock);
	WSACleanup();
	return 0;
}


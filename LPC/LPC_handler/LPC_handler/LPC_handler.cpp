#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "D:\ESIREM\C++\LPC\LPC\LPC\connection.h"
#include "D:\ESIREM\C++\LPC\LPC\LPC\Server.h"
#pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <thread>
#include <Windows.h>

int main()
{
	const unsigned short port = 9998;
	Server serv1(port);
	serv1.acceptClient();

	/*
	// socket Windows
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Erreur initialisation WinSock : " << WSAGetLastError();
		return -1;
	}

	// Var
	const unsigned short port = 9998;
	SOCKET server = connection_server(port);
	std::vector<Client> clients(25);
	char buffer[] = "Hola";
	bool exit = 0;

	// STARTS OF THREADS 
	std::thread t1_recv(t_recv, server);
	std::thread t1_send(t_send,clients[0].sock,&exit);

	// Main Loop
	while (!exit)
	{
		Client newClient;

		if ((connection_server_accept(server, port, newClient)) == 1)
		{
			clients.push_back(newClient);
		}
		Sleep(0.2);

	}

	//  ------------------EXIT

	std::cout << "[*] Cleanning up ..." << std::endl;
	closesocket(server);
	for (int i = 0; i < clients.size(); i++)	
	{
		closesocket(clients[i].sock);
	}
	WSACleanup();
	std::cout << "[*] Done";

	// Threads exit
	t1_recv.join();
	t1_send.join();
	*/
}

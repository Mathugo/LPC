#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "D:\ESIREM\C++\LPC\LPC\LPC\Server.h"
#pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <thread>
#include <Windows.h>

void recv_t(Server serv1)	
{
	if (!serv1.getExit())
	{
		char buffer[256]{ 0 };
		std::vector<st_Client> clients = serv1.getClients();
		for (int i = 0; i < clients.size(); i++)
		{
			recv(clients[i].sock, buffer, sizeof(buffer), 0);
			std::cout << "[*] Client " << clients[i].number << " : " << std::endl;

		}
		Sleep(200);
	}
}
void accept_t(Server serv1)
{
	while (serv1.getExit() != 1)
	{
		serv1.acceptClient();
	}
}

int main()
{
	const unsigned short port = 9997;
	Server serv1(port);
	serv1.acceptClient();
	std::cout << "[*] Starting thread ..." << std::endl;
	std::thread t_accept(accept_t, serv1);
	std::thread t_recv(recv_t,serv1);
	std::cout << "[*] Done" << std::endl;
	bool val = 1;
	while (val)
	{
		val = serv1.send_c();
	}
	std::cout << "[*] Closing thread ..." << std::endl;
	t_accept.join();
	t_recv.join();
	std::cout << "[*] Done" << std::endl;
}

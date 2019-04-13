#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "D:\ESIREM\C++\LPC\LPC\LPC\Server.h"
#pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <thread>
#include <Windows.h>

void recv_t(Server* serv1)	
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

	std::cout << "Dans thread" << std::endl;
	while ( strcmp(buffer,"exit") != 0)
	{
		std::vector<st_Client> clients = serv1->getClients();
		if (recv(clients[nb].sock, buffer, sizeof(buffer), 0) > 0)
			std::cout << "[*] Zombie " << nb << " : " << buffer << std::endl;
		else
			break;
		Sleep(300);

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
		val = serv1->send_c();
	}
}
int main()
{
	const unsigned short port = 9997;
	std::vector<std::thread> thread_list;
	//int nb = 0;
	Server* serv1 = new Server(port);
	//Server serv1(port);
	serv1->acceptClient();
	std::cout << "[*] Starting thread ..." << std::endl;
	//thread_list.push_back(std::thread(listen_client,serv1,nb));
	//nb++;
	//std::thread t_send(send_t, serv1);
	

	std::thread t_accept(accept_t, serv1);
	std::thread t_recv(recv_t,serv1);
	std::cout << "[*] Done" << std::endl;
	bool val = 1;
	
	while (val)
	{
		val = serv1->send_c();
	}
	bool test = 1;
	/*
	bool test = 0;
	while (serv1.getError() != 1)
	{
		test = serv1.acceptClient();
		//std::thread t_listen(listen_client,serv1,nb);
		if (test)
		{
			thread_list.push_back(std::thread(listen_client, serv1, nb));
			nb++;
		}
	}

	*/
	std::cout << "[*] Closing thread ..." << std::endl;
	//t_send.join();
	
	
	t_accept.join();
	/*for (int i = 0; i < thread_list.size(); i++)
	{
		thread_list[i].join();
	}
	*/
	t_recv.join();
	delete serv1;
	std::cout << "[*] Done" << std::endl;
}

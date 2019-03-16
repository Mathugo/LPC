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

int main()
{
	const unsigned short port = 9997;
	Server serv1(port);
	serv1.acceptClient();
	serv1.send_b("COUCOU");

	std::thread t_recv(recv_t,serv1);
	bool val = 1;
	while (val)
	{
		val = serv1.send_c();
	}

//	std::thread t1_recv(t_recv, server);
//	std::thread t1_send(t_send,clients[0].sock,&exit);

	
	t_recv.join();
	//t_send.join();

}

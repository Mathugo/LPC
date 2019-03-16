#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include "connection.h"
#include <string>

SOCKET connection_handler(const unsigned short port,std::string addr)
{
	SOCKET sock;
	SOCKADDR_IN sin;
	char buffer[255];
	sock = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "[*] Binding port ..." << std::endl;
	sin.sin_addr.s_addr = inet_addr(addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	connect(sock, (SOCKADDR *)&sin, sizeof(sin));
	std::cout << "[*] Connection done ! ") << std::endl;
	recv(sock, buffer, sizeof(buffer), 0);
	std::cout << "Server :  " << buffer << std::endl;
	return sock;
}

SOCKET connection_server(const unsigned short port)
{
	SOCKET sock;
	SOCKET csock;
	SOCKADDR_IN sin;
	SOCKADDR_IN csin;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "[*] Binding port ..." << std::endl;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	bind(sock, (SOCKADDR *)&sin, sizeof(sin));
	listen(sock, 0);
	std::cout << "[*] Done" << std::endl;
	return sock;
}
SOCKET connection_server_accept(SOCKET sock)
{
	std::cout << "[*] En attente d'un client .." << std::endl;
	csock = accept(sock, (SOCKADDR *)&csin, &sinsize));
	std::cout << "[*] Nouveau client !" << std::endl;
	return csock;
}

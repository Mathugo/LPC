#include "pch.h"
#include "Socket_.h"
#pragma warning(disable:4996) 


Socket_::Socket_()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Erreur initialisation WinSock : " << WSAGetLastError();
		error = 1;
	}
}


Socket_::~Socket_()
{
	std::cout << "Cleanning up ..." << std::endl;
	WSACleanup();
	std::cout << "Closing sockets .." << std::endl;
	closesocket(sock);
	std::cout << "[*] DONE" << std::endl;
}

void Socket_::setSock(SOCKET psock) { sock = psock; }
SOCKET Socket_::getSock() { return sock; }
bool Socket_::getError() { return error; }
char* Socket_::getBuffer() { return buffer; }

void Socket_::setError(const bool perror) { error = perror; }

void Socket_::print_buffer() { std::cout << buffer << std::endl; }

bool Socket_::recv_b()
{
	char b[256] = { 0 };
	if (!recv(sock, b, sizeof(b), 0))
	{
		std::cout << b << std::endl;
		Sleep(300);
		return 1;
	}
	else 
		return 0;
}
bool Socket_::send_b(const char* pbuffer)
{
	return 0;
}
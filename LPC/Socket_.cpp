#include "pch.h"
#include "Socket_.h"
#pragma warning(disable:4996) 
#define SIZE_BUFFER 256

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
void Socket_::setError(const bool perror) { error = perror; }
char* Socket_::getBuffer() { return buffer; }
void Socket_::setBuffer(const char* pbuffer)
{
	for (int i = 0; i < SIZE_BUFFER; i++)
	{
		buffer[i] = pbuffer[i];
	}
}
void Socket_::print_buffer() { std::cout << buffer << std::endl; }
char* Socket_::getType() { return type_; }
void Socket_::setType(const char* ptype_) { strcpy(type_,ptype_); }




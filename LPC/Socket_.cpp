#include "Socket_.h"
#pragma warning(disable:4996) 
#define SIZE_BUFFER 256

Socket_::Socket_()
{
#ifdef _WIN32

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Erreur initialisation WinSock : " << WSAGetLastError();
		error = 1;
	}
#endif
}

Socket_::~Socket_()
{
	std::cout << "Cleanning up ..." << std::endl;
#ifdef _WIN32
	WSACleanup();
#endif
	std::cout << "Closing sockets .." << std::endl;
	closesocket(sock);
	std::cout << "[*] DONE" << std::endl;
}

void Socket_::setSock(const SOCKET& psock) { sock = psock; }
SOCKET* Socket_::getSock() const { return sock_; }
bool Socket_::getError() const{ return error; }
void Socket_::setError(const bool &perror) { error = perror; }
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




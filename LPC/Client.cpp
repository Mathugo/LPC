#include "pch.h"
#include "Client.h"
#pragma warning(disable:4996) 


Client::Client(const char* addr,const unsigned short port) : Socket_()
{
	SOCKADDR_IN sin;
	int val;
	this->setSock(socket(AF_INET, SOCK_STREAM, 0));
	sin.sin_addr.s_addr = inet_addr(addr);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	std::cout << "[*] Connection to " << addr << ":" << port << std::endl;
	val = connect(this->getSock(), (SOCKADDR *)&sin, sizeof(sin));

	while (val != 0)
	{

		Sleep(1000);
		if (val == INVALID_SOCKET)
		{
			this->setError(1);
			std::cout << "Can't reach : " << addr<<":" << port << std::endl;
		}
		else
		{
			std::cout << "[*] Done" << std::endl;
		}
	}
}

Client::~Client()
{}

bool Client::send_b(const char* pbuffer)
{
	if (send(this->getSock(), pbuffer, sizeof(pbuffer), 0) == 0)
		return 1;
	else
		return 0;
}

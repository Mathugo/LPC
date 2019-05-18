#pragma once
#pragma warning(disable:4996) 
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include "Client.h"
#include "Factory_Client.h"

void restart(const char* filename);

int main(int argc, char *argv[])
{
	// ----------- MAIL SETTING
	const std::string smtp = "smtp.gmail.com:587";
	const std::string sender_mail = "LPCEmailZ@gmail.com";
	const std::string sender_name = "LPC";
	const std::string password = "lpc12345";
	const std::string rcpt_name = "Hugo";
	const std::string mail_rcpt = "hugo.mathh@gmail.com";
	// -----------------------

	const char addr[] = "127.0.0.1"; //"91.167.128.194"; // -----'------------ IP PORT
	const unsigned short port = 9997; 
	
	Client client1(addr, port);
	client1.init(smtp,sender_mail,sender_name,password,mail_rcpt,rcpt_name);

	/*
	while (strcmp(client1.getBuffer(), "exit") != 0)
	{
		client1.recv_b();
		if (std::string(client1.getBuffer()) == "exit")
		{
			restart(argv[0]);
			return 0;
		}
		client1.print_buffer();		
	}
	*/
}

void restart(const char* filename)
{
	std::string cmd = "start " + std::string(filename);
	system(cmd.c_str());
}

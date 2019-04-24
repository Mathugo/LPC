#pragma once
#pragma warning(disable:4996) 
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include "Client.h"
#include "Factory_Client.h"

void restart(const char* filename);

int main(int argc, char *argv[])
{
	const char addr[] = "127.0.0.1"; // -----'------------ IP PORT
	const unsigned short port = 32769; // 32769
	
	Client client1(addr, port);

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

}

void restart(const char* filename)
{
	std::string cmd = "start " + std::string(filename);
	system(cmd.c_str());
}

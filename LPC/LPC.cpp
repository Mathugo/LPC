#pragma once
#pragma warning(disable:4996) 
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include "Client.h"

int main()
{
	const char addr[] = "127.0.0.1"; // -----'------------ IP PORT
	const unsigned short port = 9997;
	
	Client client1(addr, port);

	while (strcmp(client1.getBuffer(), "exit") != 0)
	{
		client1.recv_b();
		client1.print_buffer();		
	}

}




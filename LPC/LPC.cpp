#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 
#pragma warning(disable:4996) 
#include "pch.h"
#include "Server.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 
#include <Windows.h>
#include <stdio.h>
#include "Client.h"

int main()
{
	const char addr[] = "127.0.0.1"; // -----'------------ IP PORT
	const unsigned short port = 9997;
	Client client1(addr, port);

	while (client1.getBuffer() != "exit" || client1.getBuffer() != "EXIT")
	{
		client1.recv_b();
		client1.print_buffer();
	}

}




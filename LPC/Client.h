#pragma once
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string.h>
#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "Socket_.h"

class Client : Socket_
{
public:
	bool send_b(const char* buffer);
	Client(const char* addr, const unsigned short port);
	~Client();
};


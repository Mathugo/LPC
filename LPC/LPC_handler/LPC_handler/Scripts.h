#pragma once
#include <Windows.h>
#include <iostream>

void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
	/*
		1: Blue
		2: Green
		3 : Cyan
		4 : Red
		5 : Purple
		6 : Yellow(Dark)
		7 : Default white
		8 : Gray / Grey
		9 : Bright blue
		10 : Brigth green
		11 : Bright cyan
		12 : Bright red
		13 : Pink / Magenta
		14 : Yellow
		15 : Bright white
		- Numbers after 15 are background colors -
		*/
}


void print_help()
{
	SetColor(2);
	std::cout << "				------------ List of Commands ------------" << std::endl;
	SetColor(6);
	std::cout << "help					     : list all commands" << std::endl;
	std::cout << "geo				         : Give the localization of the current session" << std::endl;
	std::cout << "set_session			     : Switch to an another session" << std::endl;
	std::cout << "list					     : list all actives sessions" << std::endl;
	std::cout << "exit					     : exit the program" << std::endl;
	std::cout << "pwd                        : print the trojan emplacement " << std::endl;
	std::cout << "cd \"\directory\..\"       : change directory" << std::endl;
	std::cout << "ls					     : see all files at the current directory" << std::endl;
	std::cout << "upload \"filename\"	     : upload a file in the current directory" << std::endl;
	std::cout << "upload_exe \"filename\"    : upload and exe a file in the current directory" << std::endl;
	std::cout << "download \"filename\"		 : download the file's target wanted  " << std::endl;
	std::cout << "download_dir \"filename\"  : download the target directory " << std::endl;
	SetColor(7);
}

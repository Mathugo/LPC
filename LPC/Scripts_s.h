#pragma once
#include <iostream>
#include "Server.h"
#include "Client.h"
#include "Scripts_all.h"
#include <sstream>
#include <Lmcons.h>

class Info

{	public:

	static void list_scripts();
	static void print_help();
	static bool set_session(Server* server);
	static void list(Server* server);
	static void getsysinfo(Server* server);

};
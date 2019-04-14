# LPC
Trojan written in C++ based on socket connection.

2 Executables : The handler and the payload. 
When the payload is executed on the computer's victim, it will try to connect at a special IP:PORT toward the handler.
If it's succesfull you can run several scripts --> (upload file, download file, screenshot, run shell command, enum web password, 
put persistence, get external IP, geolocalyze the victim etc...)

Goal of this is to :
- perform stable worked and undetectable scripts
- have a botnet of multiple client
- executable must be light

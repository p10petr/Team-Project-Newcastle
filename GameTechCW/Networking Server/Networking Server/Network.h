#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wsock32.lib")
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>


#define HIGHVERSION 2
#define LOWVERSION 2
//#define HOST "127.0.0.1" //ipconfig in cmd and copy the IPV4 command here, YULONG: 10.66.67.181
#define PORT "4376"
#define FAMILY AF_UNSPEC
#define TYPE SOCK_STREAM
#define FLAGS AI_PASSIVE
#define PROTOCOL IPPROTO_TCP
#define BACKLOG 10
#define BUFFSIZE 1200	//A bit more than the size of the message for 9 objects and the delimiters



struct gameObjectData {
	std::string objName;
	//Vector3 position;	//Calculated data
	//Quaternion  orientation;	//Calculated data
	//Vector3 inpForce;	//Before-calculation data
	//Quaternion inpOrientation; //Before-calculation data
};

struct clientInfo {
	PCSTR ip;
	boolean ready = false;
	std::vector<gameObjectData> gameObjects;
};


class Network {
public:
	Network();
	~Network();
	char * stringToCharStar(std::string str);
	int init();
	int addressing();
	void _stdcall createSocket();
	virtual void _stdcall freeaddr();
	virtual void _stdcall setMessage(char *msg);
	virtual char * getMessage();
	virtual std::vector<std::string>* getMessageQueue();
	virtual void _stdcall sendMessage(SOCKET sock);
	virtual void _stdcall receiveMessage(SOCKET sock);

protected:
	WSAData wsaData;
	struct addrinfo *addr;
	SOCKET listening_sock = NULL;
	char *message;
	std::vector<std::string> *messageQueue;
	int bytesreceived;
	char buff[BUFFSIZE];
	PCSTR HOST = "10.66.67.185"; //pointer to constant string
	std::vector<PCSTR> *clientList;
	std::vector<clientInfo> *clients;
	char *last_client;	//Server knows the last client's IP
};
/***************************
4099056008 陳昱全 期末Project 6/18
4099056030 黃湋縜 期末Project 6/18
***************************/
#include "stdafx.h"

#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <string> 
#include <iostream>


using namespace std;



class SocketServer{
public:
	int r;
	WSAData wsaData;
	WORD DLLVSERION;
	char message[200];
	char temp[200];
	float x;
	float y;
	float playerId;
	float length;
	int character;
	string ip;
	int port;
	float health;
	int death;

	//宣告 socket 位址資訊(不同的通訊,有不同的位址資訊,所以會有不同的資料結構存放這些位址資訊)
	SOCKADDR_IN addr;
	int addrlen ;

	//建立 socket
	SOCKET sListen; //listening for an incoming connection
	SOCKET sConnect; //operating if a connection was found

	//等待連線
	SOCKADDR_IN clinetAddr;

public:
	SocketServer ::SocketServer(){
		DLLVSERION = MAKEWORD(2,1);//Winsocket-DLL 版本

		//用 WSAStartup 開始 Winsocket-DLL
		r = WSAStartup(DLLVSERION, &wsaData);

		addrlen = sizeof(addr);

		//AF_INET：表示建立的 socket 屬於 internet family
		//SOCK_STREAM：表示建立的 socket 是 connection-oriented socket 
		sConnect = socket(AF_INET, SOCK_STREAM, NULL);



		//設定位址資訊的資料
		addr.sin_addr.s_addr = inet_addr("140.120.14.144");
		addr.sin_family = AF_INET;
		addr.sin_port = htons(5678);


		//設定 Listen
		sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);//SOMAXCONN: listening without any limit

		int sock;

		if ( (sock = socket(PF_INET, SOCK_STREAM, 0)) == -1 ) {

			perror("socket failed");

		}





	}

	void SocketServer ::wait(){
	//	struct sockaddr_in clientAddr;
	//	int clientAddrLen = sizeof(clientAddr);
		
			sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen);
			printf("server: got connection from %s", inet_ntoa(clinetAddr.sin_addr)); 
		

	}

	//傳送訊息給 client 端
	void SocketServer ::sendCoordinate(int totalPlayer,float playerID,float x,int y,float length,float death){

		string s=to_string(totalPlayer)+','+to_string(playerID)+','+to_string(x)+','+to_string(y)
			+','+to_string(length)+','+to_string(death);
		char *sendbuf = new char[s.length() + 1];
		strcpy(sendbuf, s.c_str());
		//cout<<sendbuf<<endl;
		send(sConnect, sendbuf, (int)strlen(sendbuf), 0);	
	}



	//接收 client 端的訊息
	void SocketServer::receiveCoordinate(){

		ZeroMemory(message, 200);
		r = recv(sConnect, message, sizeof(message), 0);
		//cout << message << endl;

		char *pch;
		pch=strtok(message,",");

		playerId=atof(pch);
		pch=strtok(NULL,",");
		x=atof(pch);
		pch=strtok(NULL,",");
		y=atof(pch);
		pch=strtok(NULL,",");
		length=atoi(pch);
		pch=strtok(NULL,",");
		death=atof(pch);

	//	cout<<playerId<<" "<<x<<" "<<y<<" "<<" "<<length<<" "<<death<<endl;
	}

	void SocketServer ::sendCharacter(int character){

		string s=to_string(character);
		char *sendbuf = new char[s.length() + 1];
		strcpy(sendbuf, s.c_str());
		send(sConnect, sendbuf, (int)strlen(sendbuf), 0);	

	}

	void SocketServer::receiveCharacter(){

		ZeroMemory(temp, 200);
		r = recv(sConnect, temp, sizeof(temp), 0);
		character=atoi(temp);
		std::cout << character << std::endl;

	}

	void SocketServer::getReady(){

		char *sendbuf = "1";
		while(send(sConnect, sendbuf, (int)strlen(sendbuf), 0) !=1 || recv(sConnect, temp, sizeof(temp), 0) !=1){
			;
		}
	}

	void SocketServer::close(){
		closesocket(sListen);
		closesocket(sConnect);
		WSACleanup();
	}

};
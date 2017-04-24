/***************************
4099056008 ���R�� ����Project 6/18
4099056030 ������ ����Project 6/18
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

	//�ŧi socket ��}��T(���P���q�T,�����P����}��T,�ҥH�|�����P����Ƶ��c�s��o�Ǧ�}��T)
	SOCKADDR_IN addr;
	int addrlen ;

	//�إ� socket
	SOCKET sListen; //listening for an incoming connection
	SOCKET sConnect; //operating if a connection was found

	//���ݳs�u
	SOCKADDR_IN clinetAddr;

public:
	SocketServer ::SocketServer(){
		DLLVSERION = MAKEWORD(2,1);//Winsocket-DLL ����

		//�� WSAStartup �}�l Winsocket-DLL
		r = WSAStartup(DLLVSERION, &wsaData);

		addrlen = sizeof(addr);

		//AF_INET�G��ܫإߪ� socket �ݩ� internet family
		//SOCK_STREAM�G��ܫإߪ� socket �O connection-oriented socket 
		sConnect = socket(AF_INET, SOCK_STREAM, NULL);



		//�]�w��}��T�����
		addr.sin_addr.s_addr = inet_addr("140.120.14.144");
		addr.sin_family = AF_INET;
		addr.sin_port = htons(5678);


		//�]�w Listen
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

	//�ǰe�T���� client ��
	void SocketServer ::sendCoordinate(int totalPlayer,float playerID,float x,int y,float length,float death){

		string s=to_string(totalPlayer)+','+to_string(playerID)+','+to_string(x)+','+to_string(y)
			+','+to_string(length)+','+to_string(death);
		char *sendbuf = new char[s.length() + 1];
		strcpy(sendbuf, s.c_str());
		//cout<<sendbuf<<endl;
		send(sConnect, sendbuf, (int)strlen(sendbuf), 0);	
	}



	//���� client �ݪ��T��
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
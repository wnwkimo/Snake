#pragma once
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "sLinkList.h"
#include "playerData.h"
#include "SocketServer.h"

class SnakeCVServer
{
public:
	SnakeCVServer(void);
	~SnakeCVServer(void);
private:
	cv::Mat Envirment;


private:
	void Initial();
	void GenerateEnvirment(int width = 1000, int height = 1000);	
	void showView();
	void drawSnake();
	void receiveData();
	void sendData();

	int x,y;
	int totalPlayer;
	playerData Player[10];
	SocketServer Server;
	int playerId;

public:
	void Play();
	
};



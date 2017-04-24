#pragma once
#include "sLinkList.h"
#include <opencv\cv.h>
#include <opencv\highgui.h>


class playerData
{
public:
	playerData(void);
	~playerData(void);

	void mouseLocate(cv::Point pt);
	sLinkList playerSnake;

public:
	int playerIdx;
	bool alive;
	int length;
private:
	
	

	float xVector,yVector;
	cv::Point PlayerHeadLoc;
};


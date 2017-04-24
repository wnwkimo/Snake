#include "stdafx.h"
#include "playerData.h"


playerData::playerData(void)
{
	length = 20;
	for(int i = 0; i < length;i++)
	{
		playerSnake.addNode(cv::Point(10,0));
	}

	PlayerHeadLoc = cv::Point(0,0);
	xVector = 1.0f;
	yVector = 0.0f;

}


playerData::~playerData(void)
{
}

void playerData::mouseLocate(cv::Point pt)
{
	cv::Point newPoint;

	xVector = (pt.x - PlayerHeadLoc.x)*0.1f;
	yVector = (pt.y - PlayerHeadLoc.y)*0.1f;

	newPoint.x = PlayerHeadLoc.x + xVector;
	newPoint.y = PlayerHeadLoc.y + yVector;

	PlayerHeadLoc = newPoint;
	playerSnake.addNode(newPoint);
	playerSnake.killHeadNode();
}
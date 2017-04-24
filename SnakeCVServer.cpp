#include "stdafx.h"
#include "SnakeCVServer.h"
#include <thread>

SnakeCVServer::SnakeCVServer(void):x(40),y(30)
{
	playerId = 0;
	totalPlayer =2;
}


SnakeCVServer::~SnakeCVServer(void)
{
	Server.close();
}

void SnakeCVServer::Play()
{
	this->Initial();
	while(1)
	{
	this->receiveData();
	
	this->sendData();
	
	this->GenerateEnvirment();
	this->drawSnake();
	this->showView();
	}
}


cv::Point mouseLocate(500,500);
void onMouse(int Event,int x,int y,int flags,void* param){
	if(Event==CV_EVENT_MOUSEMOVE){
        mouseLocate.x = x;
        mouseLocate.y = y;
    }  
}
void SnakeCVServer::receiveData()
{
	Server.receiveCoordinate();
	cv::Point receiveLoc;
	receiveLoc.x = Server.x;
	receiveLoc.y = Server.y;
	Player[(int)Server.playerId].mouseLocate(receiveLoc);

}

void SnakeCVServer::sendData()
{
	Player[playerId].mouseLocate(mouseLocate);
	Server.sendCoordinate(totalPlayer,playerId,mouseLocate.x,mouseLocate.y,Player[playerId].length,Player[playerId].alive);


}

void SnakeCVServer::Initial()
{
	cv::namedWindow("Snake");
	 cv::setMouseCallback("Snake",onMouse,NULL);

	 
	 Server.wait();
}

void SnakeCVServer::GenerateEnvirment(int width, int height)
{
	Envirment = cv::Mat::zeros(cv::Size(width,height),CV_8UC3);

}




void SnakeCVServer::drawSnake()
{
//	std::cout<<"t"<<std::endl;
for(int i = 0;i < totalPlayer;i++)
	{
		sNode<cv::Point> *ptr= Player[i].playerSnake.head; 
	while(ptr->next/*->data*/ !=NULL/*cv::Point(0,0)*/)
	{
		//std::cout<<ptr->data<<std::endl;
		//std::cout<<ptr->next->data<<std::endl;
		cv::line(Envirment,ptr->data,ptr->next->data,cv::Scalar(255,0,0),3);
		cv::line(Envirment,ptr->data,ptr->data,cv::Scalar(0,255,0),3);
		cv::line(Envirment,ptr->next->data,ptr->next->data,cv::Scalar(0,255,0),3);
			ptr=ptr->next;

	}
}
	
}

void SnakeCVServer::showView()
{
	imshow("Snake",Envirment);
	cv::waitKey(100);

}
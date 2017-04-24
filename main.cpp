// Snake.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "SnakeCVServer.h"

#include <thread>


int _tmain(int argc, _TCHAR* argv[])
{
//	SocketServer testttt;
//	testttt.wait();
//	testttt.receiveCharacter();
//	testttt.sendCharacter(500);
//	cv::waitKey(100);
//		testttt.sendCharacter(100);
//		testttt.receiveCharacter();

//	thread aa();

	SnakeCVServer test;
	test.Play();
	return 0;
}


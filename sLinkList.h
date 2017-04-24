#pragma once
#include <opencv\cv.h>
#include <opencv\highgui.h>


template<class _TP>
class sNode
{
public:
  _TP data;
  sNode *next;
  sNode(_TP a)
  {
	  this->next = NULL;
	  this->data = a; 
  };
  sNode(){};
};


class sLinkList
{
public:
	sNode<cv::Point> *mynode;
	sNode<cv::Point> *head;

public:
	sLinkList()
	{
		mynode = new sNode<cv::Point>;
		head = mynode;
		
		mynode->next = NULL;
	};
	~sLinkList()
	{
		delete mynode;
	
	};

	void addNode(cv::Point pt){
	
		sNode<cv::Point> *NewNode = new sNode<cv::Point>(pt);
		mynode->data = pt;
		mynode->next = NewNode;
		mynode = NewNode;	
	
    };

	void killHeadNode(){
		sNode<cv::Point> *tmp = head;
		head = head ->next;
		delete tmp;	
    };

};


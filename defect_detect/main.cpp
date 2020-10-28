// An highlighted block
//#include "head.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


int main() {
	Mat img = imread("alphabet.png");
	//assert(im.data);
	if (!img.data) { printf("error! \n"); return -1; }
	Mat img_gray; Mat img2;
	cvtColor(img,img_gray, COLOR_BGR2GRAY);
	//二值化
	threshold(img_gray, img2,100, 255, THRESH_BINARY_INV);
	
	//形态学处理 闭操作  先膨胀后腐蚀
	Mat element = getStructuringElement(MORPH_RECT,Size(17, 17));
	morphologyEx(img2, img2, MORPH_CLOSE, element);
	
	//腐蚀
	Mat element1 = getStructuringElement(MORPH_RECT, Size(3, 1));
	morphologyEx(img2, img2, MORPH_ERODE, element1);

	vector<vector<Point> > contours;
	findContours(img2, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, Scalar(0, 255, 0), 1, 8);
		
	vector<vector<Point> > contours1;
	
	for (int i=0; i <= contours.size() - 1; i++) {
		float area = contourArea(contours[i]);
		
		if ((area < 5500&&area>5000)||area>25000) {
			contours1.push_back(contours[i]);
			
		}

	}
		
	string str[2] = { "D","S" };
		
	drawContours(img, contours1, -1, Scalar(0, 0, 255), 1, 8);
	
	
	for (int i = 0; i <= contours1.size() - 1; i++) 
	{
		Rect rect = boundingRect(contours1[i]);
		
		rectangle(img, rect, Scalar(0, 0, 255), 1, 8);
	
		putText(img,str[i],Point(rect.x - 20 + rect.width / 2, rect.y - 30),1,1,Scalar(255,255,255));
		
	}
	  	cout<<"******"<<endl;
	namedWindow("1");
	imshow("1", img);
	namedWindow("2");
	imshow("2", img_gray);
	namedWindow("3");
	imshow("3", img2);
	waitKey(0);
	return 0;
    
}    
// ————————————————
// 版权声明：本文为CSDN博主「乖乖的做」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/hechaoqi09/article/details/84862938
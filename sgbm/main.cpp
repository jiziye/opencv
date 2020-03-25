#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//int _tmain(int argc, _TCHAR* argv[])
int main(int argc,char** argv)
{
	Mat left = imread("img_l.jpg", IMREAD_GRAYSCALE);
	Mat right = imread("img_r.jpg", IMREAD_GRAYSCALE);
	Mat disp;
	int mindisparity = 0;
	int ndisparities = 64;  
	int SADWindowSize = 11; 
	//SGBM
	cv::Ptr<cv::StereoSGBM> sgbm ;
	sgbm.create(mindisparity, ndisparities, SADWindowSize);
	

	int P1 = 8 * left.channels() * SADWindowSize* SADWindowSize;
	int P2 = 32 * left.channels() * SADWindowSize* SADWindowSize;
	sgbm->setP1(P1);
	sgbm->setP2(P2);
	sgbm->setPreFilterCap(15);
	sgbm->setUniquenessRatio(10);
	sgbm->setSpeckleRange(2);
	sgbm->setSpeckleWindowSize(100);
	sgbm->setDisp12MaxDiff(1);
	//sgbm->setMode(cv::StereoSGBM::MODE_HH);
	sgbm->compute(left, right, disp);
	disp.convertTo(disp, CV_32F, 1.0 / 16);                //除以16得到真实视差值
	Mat disp8U = Mat(disp.rows, disp.cols, CV_8UC1);       //显示
	normalize(disp, disp8U, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("results/sgbm",disp8U);
	imwrite("results/SGBM.jpg", disp8U);
	return 0;
}

// ————————————————
// 版权声明：本文为CSDN博主「自由的迷鹿」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/cxgincsu/article/details/74451940
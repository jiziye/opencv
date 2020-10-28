#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>

#include<iostream>
 
using namespace std;
using namespace cv;
 
int main()
{
	Mat srcImg = imread("./../../panda.jpg");
	if (!srcImg.data)
	{
		//printf("could not load image....\n");
		cerr<<"load image error"<<endl;
		return -1;
	}
	imshow("input image", srcImg);
 
	Scalar colorTab[] = {	
		Scalar(0,0,255),
		Scalar(0,255,0),
		Scalar(255,0,0),
		Scalar(255,255,0),
		Scalar(255,0,255),
	};
 
	int width = srcImg.cols;
	int height = srcImg.rows;
	int dims = srcImg.channels();
 
	//初始化定义
	int sampleCount = width * height;
	int clusterCount = 3;
	Mat points(sampleCount, dims, CV_32FC1, Scalar(10));
	Mat labels;
	Mat center(clusterCount, 1, points.type());//为什么是1列和3维？
    //目前的理解是每列中的每个通道存取对应通道的中心值
    //还是不太理解center三通道里的值的含义
 
	int index = 0;
	for (int row = 0; row < srcImg.rows; row++)
	{
		for (int col = 0; col < srcImg.cols; col++)
		{
			index = row * width + col;        //转到一维
			Vec3b bgr = srcImg.at<Vec3b>(row, col);
			points.at<float>(index, 0) = static_cast<int>(bgr[0]);
			points.at<float>(index, 1) = static_cast<int>(bgr[1]);
			points.at<float>(index, 2) = static_cast<int>(bgr[2]);
		}
	}
 
	kmeans(points, clusterCount, labels,
		TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1),
		3, KMEANS_PP_CENTERS, center);
    //center可不写
 
	Mat result = Mat::zeros(srcImg.size(), srcImg.type());//老是忘记初始化，哼！
	index = 0;
	for (int row = 0; row < srcImg.rows; row++)
	{
		for (int col = 0; col < srcImg.cols; col++)
		{		
			index = row * width + col;
            int label = labels.at<int>(index);
 
	//		Vec3b bgr = result.at<Vec3b>(row, col);  
	//		bgr[0] = colorTab[label][0];
	//		bgr[1] = colorTab[label][1];
	//		bgr[2] = colorTab[label][2];
    //还在疑惑为什么用上面这段代码替代下面的会得到一张黑图，地址不对？？？？		
			result.at<Vec3b>(row, col)[0] = colorTab[label][0];
			result.at<Vec3b>(row, col)[1] = colorTab[label][1];
			result.at<Vec3b>(row, col)[2] = colorTab[label][2];
		}
	}
 
	imshow("KMeans Image", result);
	waitKey(0);
	return 0;
}

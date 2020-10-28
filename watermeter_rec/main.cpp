#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main()
{
    // VideoCapture cap(0);
    // while(char(waitKey(1))!='q')
    // {
    //     // //获取视频图像
    //     // Mat src;
    //     // cap>>src;
    //     // imshow("src",src);
    // }
        //读取图片
        Mat src = imread("test.jpg");
        if(src.empty())
        cerr << " read image error"<< endl;
        imshow("src",src);
        //图像处理
        Mat gray;
        cvtColor(src,gray,COLOR_RGB2GRAY);//转灰度
        imshow("gray",gray);
        Mat thre;
        threshold(gray,thre,150,255,0);//二值化
        imshow("thre",thre);

        //膨胀
        // Mat dila;
        // Mat element = getStructuringElement(MORPH_RECT,Size(3,3));
        // dilate(thre,dila,element);
        // imshow("dilate",dila);

        //腐蚀(白底黑字)
        Mat ero;
        Mat element = getStructuringElement(MORPH_RECT,Size(3,3));
        erode(thre,ero,element);
        imshow("ero",ero);

        //获取轮廓
        Mat thre_1;
        threshold(gray,thre_1,100,255,CV_THRESH_BINARY_INV);//白底黑字
        imshow("thre_1",thre_1);


        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(thre,contours,hierarchy,CV_RETR_CCOMP,CHAIN_APPROX_SIMPLE);

        Mat cont = Mat::zeros(gray.rows, gray.cols, CV_8UC3);

        int index = 0;
        for(int index = 0; index < contours.size(); index = hierarchy[index][0])
        {
            Scalar color(rand()&255, rand()&255, rand()&255);
            drawContours(cont, contours, index, color, FILLED, 8, hierarchy);
        }
        imshow("contours", cont);

         waitKey(0);

    return 0;
}
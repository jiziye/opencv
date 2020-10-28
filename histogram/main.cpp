#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src,hsv;
    src=imread("color.jpg");
    cvtColor(src,hsv,COLOR_BGR2HSV);

    //number
    int hueBinNum=30;
    int saturationBinNum=32;
    int histSize[]={hueBinNum,saturationBinNum};

    //range
    float hueRanges[]={0,180};
    float saturationRanges[]={0,256};
    const float* ranges[]={hueRanges,saturationRanges};


    MatND dstHist;
    int channels[]={0,1};

    //calcHist(&hsv,1,channels,Mat(),dstHist,2,histSize,ranges,true,false);
    calcHist(&hsv,1,channels,Mat(),dstHist,2,histSize,ranges,true,false);
    
    double maxValue=0;
    minMaxLoc(dstHist,0,&maxValue,0,0);

    int scale=10;
    Mat histImg=Mat::zeros(saturationBinNum*scale,hueBinNum*10,CV_8UC3);


    for(int hue=0;hue<hueBinNum;hue++)
        for(int sat=0;sat<saturationBinNum;sat++)
        {
            float binvalue=dstHist.at<float>(hue,sat);
            int intensity=cvRound(binvalue*255/maxValue);

            rectangle(histImg,Point(hue*scale,sat*scale),Point((hue+1)*scale-1,(sat+1)*scale-1),Scalar::all(intensity),CV_FILLED);

        }
    

    imshow("src",src);    
    imshow("result",histImg);
    waitKey(0);
}


    

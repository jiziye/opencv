#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define window1 "src"

Mat src,hsv,hue;
int bins=30;

void on_binchange(int,void*);

int main()
{
    src=imread("panda.jpg");
    if(!src.data){printf("read image error. \n");return false;}

    cvtColor(src,hsv,CV_BGR2HSV);
    cout<<hsv.depth()<<" "<<hsv.type();

    hue.create(hsv.size(),hsv.depth());
    int ch[]={0,0};
    mixChannels(&hsv,1,&hue,1,ch,1);

    namedWindow(window1,WINDOW_AUTOSIZE);
    
    createTrackbar("bin",window1,&bins,180,on_binchange);
    on_binchange(0,0);

    imshow(window1,src);
    waitKey();
    return 0;

}


void on_binchange(int,void*)
{
    MatND hist;
    int histsize=MAX(bins,2);
    float hue_range[]={0,180};
    const float* ranges={hue_range};

    calcHist(&hue,1,0,Mat(),hist,1,&histsize,&ranges,true,false);
    normalize(hist,hist,0,255,NORM_MINMAX,-1,Mat());

    MatND backproj;
    calcBackProject(&hue,1,0,hist,backproj,&ranges,1,true);

    imshow("back_projection",backproj);

    int w=400;
    int h=400;
    int bin_w=cvRound((double)w / histsize);
    Mat histimg=Mat::zeros(w,h,CV_8UC3);

    for(int i=0;i<bins;i++)
    {
        rectangle(histimg,Point(i*bin_w,h),Point((i+1)*bin_w,h-cvRound(hist.at<float>(i)*h/255.0)),Scalar(100,123,255),-1);    
    }    

    imshow("histimg",histimg);
}


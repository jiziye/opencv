#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image,image_3c;
    image.create(Size(256,400),CV_8UC1);
    image_3c.create(Size(256,256),CV_8UC3);
    
    image.setTo(0);
    image_3c.setTo(0);

    image.at<uchar>(300,100)=255;
    Point point(100,100);
    image.at<uchar>(point)=250;

    image_3c.at<uchar>(10,300)=255;
    image_3c.at<uchar>(10,302)=254;
    //image_3c.at<uchar>(100,300)=255;

    Point point_3c(20,200);
    image_3c.at<uchar>(point_3c)=250;

    double maxValue=0;
    Point maxLoc;
    minMaxLoc(image,NULL,&maxValue,NULL,&maxLoc);
    cout<<"C1 MAX: "<<maxValue<<" POSITION: "<<maxLoc<<endl;

    double min_3c,max_3c;
    minMaxLoc(image_3c,&min_3c,&max_3c,NULL,NULL);
    cout<<"C3 MAX: "<<max_3c<<" MIN: "<<min_3c<<endl;


    imshow("image",image);
    imshow("image_3c",image_3c);

    waitKey(0);
    return 0;
   
}
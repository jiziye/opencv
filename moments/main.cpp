#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "SRC"
#define WINDOW_NAME2 "CONTOUR"

Mat src;
Mat gray;
Mat cannyout;
int threshold_value=100;
int MaxThreshold=255;
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
RNG &rng=theRNG();

void Thresholdchange(int,void*);

int main(int argc, char** argv)
{
    src=imread("panda.jpg",1);
    cvtColor(src,gray,COLOR_BGR2GRAY);
    blur(gray,gray,Size(3,3));

    
    namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME1,gray);
    
    createTrackbar("threshold",WINDOW_NAME1,&threshold_value,MaxThreshold,Thresholdchange);

    Thresholdchange(0,0);
    waitKey(0);
    return(0);
}

void Thresholdchange(int,void *)
{
    Canny(gray,cannyout,threshold_value,threshold_value*2,3);
    cout<<cannyout<<endl;
    imshow("canny",cannyout);
    
    findContours(cannyout,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
    
    vector<Moments> mu(contours.size());
    for(unsigned int i=0;i<contours.size();i++)
    {
        mu[i]=moments(contours[i],false);
    }
     
    vector<Point2f> mc(contours.size());
    for(unsigned int i=0;i<contours.size();i++)
    {
        mc[i]=Point2f(static_cast<float>(mu[i].m10/mu[i].m00), static_cast<float>(mu[i].m01/mu[i].m00));

    }
    
    Mat drawing=Mat::zeros(cannyout.size(),CV_8UC3);
    for(unsigned int i=0;i<contours.size();i++)
    {
        Scalar color=Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(drawing,contours,i,color,2,8,hierarchy,0,Point());
        circle(drawing,mc[i],4,color,-1,8,0);
        
    }    

    namedWindow(WINDOW_NAME2,WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME2,drawing);

    printf("\t area and contour length \n ");
    for(unsigned int i=0;i<contours.size();i++)
    {
        printf("contour %d area:%.2f \n opencv function area:%.2f, length:%.2f \n\n",i,mu[i].m00,
                contourArea(contours[i]),arcLength(contours[i],true));

        Scalar color=Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(drawing,contours,i,color,2,8,hierarchy,0,Point());
        circle(drawing,mc[i],4,color,-1,8,0);
    }

}
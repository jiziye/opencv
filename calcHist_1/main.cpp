#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;



int main()
{
    Mat src=imread("color.jpg");
    imshow("src",src);
    if(!src.data){printf("read image error. \n");}

    MatND dstHist;
    int dims=1;
    int size=256;
    float hranges[]={0,255};
    const float *ranges[]={hranges};
    int channels=0;

    calcHist(&src,1,&channels,Mat(),dstHist,dims,&size,ranges);

    int scale = 1;

    Mat dstimage(size*scale,size,CV_8U,Scalar(0));
    double minvalue=0;
    double maxvalue=0;

    minMaxLoc(dstHist,&minvalue,&maxvalue,0,0);

    int hpt=saturate_cast<int>(0.9*size);
    for(int i=0;i<256;i++)
    {
        float binvalue=dstHist.at<float>(i);
        int realvalue=saturate_cast<int>(binvalue*hpt/maxvalue);
        rectangle(dstimage,Point(i*scale,size-1),Point((i+1)*scale-1,size-realvalue),Scalar(255));

    }

    imshow("one dimension hist",dstimage);
    waitKey();
    return 0;   
}
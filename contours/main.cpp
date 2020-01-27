#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src,dst;
    src=imread("earth.jpg",0);
    if(!src.data){printf("read image error. \n");return false;}
    //cvtColor(src,src,COLOR_BGR2GRAY);
    imshow("src",src);
    
    dst=Mat::zeros(src.rows,src.cols,CV_8UC3);

    src=src>100;
    imshow("src",src);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    //find contours
    findContours(src,contours,hierarchy,RETR_CCOMP,CHAIN_APPROX_SIMPLE);

    int index=0;
    for(; index>=0;index=hierarchy[index][0])
{
    Scalar color(rand()&255,rand()&255,rand()&255);
    drawContours(dst,contours,index,color,FILLED,8,hierarchy);
}
    imshow("contours",dst);


    waitKey(0);
    
    return 0;

}

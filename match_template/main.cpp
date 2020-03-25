#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using  namespace std;
using  namespace cv;

#define window1 "src"
#define window2 "result"

Mat src;Mat temp;Mat result;
int matchMethod;
int maxtrackbarnum=5;

void on_matching(int,void* );

int main()
{
    src=imread("panda.jpg",1);
    temp=imread("panda_1.jpg",1);

    namedWindow(window1,CV_WINDOW_AUTOSIZE);
    namedWindow(window2,CV_WINDOW_AUTOSIZE);

    createTrackbar("method",window1,&matchMethod,maxtrackbarnum,on_matching);
    on_matching(0,0);
    waitKey(0);
    return 0;

}

void on_matching(int,void*)
{
    Mat srcimage;
    src.copyTo(srcimage);

    int result_rows=srcimage.rows-temp.rows+1;
    int result_cols=srcimage.cols-temp.cols+1;

    result.create(result_rows,result_cols,CV_32FC1);

    matchTemplate(srcimage,temp,result,matchMethod);
    normalize(result,result,0,1,NORM_MINMAX,-1,Mat());

    double minValue; double maxValue; Point minLocation; Point maxLocation;

    Point matchLocation;
    minMaxLoc(result,&minValue,&maxValue,&minLocation,&maxLocation,Mat());

    if(matchMethod == TM_SQDIFF || matchMethod == TM_SQDIFF_NORMED)
    {
        matchLocation=minLocation;
    }
    else
    {
        matchLocation=maxLocation;       
    }

    rectangle(srcimage,matchLocation,Point(matchLocation.x+temp.cols,matchLocation.y+temp.rows),Scalar(0,0,255),2,8,0);

    rectangle(result,matchLocation,Point(matchLocation.x+temp.cols,matchLocation.y+temp.rows),Scalar(0,0,255),2,8,0);

    imshow(window1,srcimage);
    imshow(window2,result);

}
    


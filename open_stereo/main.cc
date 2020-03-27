#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "camera.hpp"

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    int index = 0;
    Camera cam(index);
    
    cv::Mat left,right;
    cam.Capture()
    {

    }

    cv::imshow("left",left);
    cv::imshow("right",right);
    VideoCapture cap(0);
    
    //ostringstream
    ostringstream ostr1;
    ostr1 << "test"<<endl;
    cout<<ostr1.str();
    
    return 0;

}
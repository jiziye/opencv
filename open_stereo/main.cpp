#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

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
    
  
    return 0;

}
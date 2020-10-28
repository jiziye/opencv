#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/gpu/gpu.hpp>
#include <opencv2/core/cuda.hpp>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    Mat img;
    std::vector<Rect> found;
     img = imread(argv[1]);
    if(argc != 2 || !img.data)
    {
        printf("没有图片\n");
        return -1;
    }
    
    HOGDescriptor defaultHog;
    defaultHog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    //进行检测
    defaultHog.detectMultiScale(img, found);
    //画长方形，框出行人
    for(int i = 0; i < found.size(); i++)
            {
        Rect r = found[i];
        rectangle(img, r.tl(), r.br(), Scalar(0, 0, 255), 3);
    }
    namedWindow("检测行人", CV_WINDOW_AUTOSIZE);
    imshow("检测行人", img);
    waitKey(0);
 
    return 0;
}
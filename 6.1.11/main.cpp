#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main() {
    Mat image=imread("panda.jpg");
    if(!image.data)
    {
        printf("no image \n");
    return false;
     }
    namedWindow("src");
    namedWindow("boxfilter_result");
    namedWindow("blur_result");
    namedWindow("gaussian_result");

    imshow("src",image);

    Mat boxfilter_out;
    Mat blur_out;
    Mat gaussian_out;

    boxFilter(image,boxfilter_out,-1,Size(3,3),Point(-1,-1),false);
    blur(image,blur_out,Size(5,5));
    GaussianBlur(image,gaussian_out,Size(3,3),0,0);

    imshow("boxfilter_result",boxfilter_out);
    imshow("blur_result",blur_out);
    imshow("gaussian_result",gaussian_out);


    waitKey(0);

    return 0;
}
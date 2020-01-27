#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

int main() {

    Mat grad_x,grad_y;
    Mat abs_grad_x,abs_grad_y;

    Mat src;
    src=imread("panda.jpg");
    imshow("panda_src",src);



    Scharr(src,grad_x,CV_16S,1,0,1,0,BORDER_DEFAULT);
    convertScaleAbs(grad_x,abs_grad_x);
    imshow("scharr_x",abs_grad_x);

    Scharr(src,grad_y,CV_16S,0,1,1,0,BORDER_DEFAULT);
    convertScaleAbs(grad_y,abs_grad_y);
    imshow("scharr_y",abs_grad_y);

    Mat dst;
    addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst);
    imshow("scharr_result",dst);

    waitKey(0);

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
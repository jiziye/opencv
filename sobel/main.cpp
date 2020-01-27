#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


int main() {
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Mat src = imread("ubuntu.png");

    imshow("src", src);

    //x direction sobel
    Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    imshow("x sobel", abs_grad_x);

    //y direction sobel
    Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);\
    convertScaleAbs(grad_y, abs_grad_y);
    imshow("y sobel", abs_grad_y);

    Mat dst;
    //merge
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
    imshow("result", dst);

    waitKey(0);
    return 0;
}



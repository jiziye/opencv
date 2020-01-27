#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat src=imread("panda.jpg");
    Mat tmp,dst1,dst2;
    tmp=src;

    imshow("src",src);

    //pyrup
    pyrUp(tmp,dst1,Size(tmp.cols*2,tmp.rows*2));
    imshow("dst1",dst1);

    pyrDown(tmp,dst2,Size(tmp.cols/2,tmp.rows/2));
    imshow("dst2",dst2);


    waitKey(0);

    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

#define WINDOW_NAME "program window"

Mat src,dst,tmp;


int main() {
    src = imread("panda.jpg");
    if (!src.data) {
        printf("read image error \n");
        return false;
    }

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME, src);

    tmp = src;
    dst = tmp;

    int key = 0;

    while (1) {
        key = waitKey(0);

        switch (key) {
            //quit program;
            // use return 0;
            // or return false;
            case 27: //esc
                return 0;
                break;

            case 'q':
                return false;
                break;


                //resize pyrup
            case '1':
                resize(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
                break;
            case '2':
                resize(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
                break;
            case '3':
                pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
                break;
            case '4':
                pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
                break;
        }
        imshow("dst", dst);
        tmp = dst;


    }

}

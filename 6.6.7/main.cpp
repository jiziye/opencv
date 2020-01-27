#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME "[program window]"

Mat src, dst,tmp;

int main() {
    src = imread("panda.jpg");
    if (!src.data) {
        printf("read image error. \n");
        return false;
    }
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME, src);

    tmp = src;
    dst = tmp;

    int key = 0;
    while (1) {
        key = waitKey(9);
        switch (key) {
            case 27://esc
                break;

            case 'q'://q
                break;

            case 'a':
                pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
                printf("zoom out \n");
                break;

            case 'w':
                resize(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
                printf("resize \n");
                break;

            case 'd':
                pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
                printf("pyrdown \n");
                break;

            case 's':
                resize(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
                printf("resize \n");
                break;

            case '1':
                resize(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
                printf("resize \n");
                break;

            case '2':
                resize(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
                printf("resize \n");
                break;

            case '3':
                pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
                printf("pyrup \n");
                break;

            case '4':
                pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
                printf("pyrdown \n");
                break;

        }

        imshow(WINDOW_NAME, dst);
        tmp = dst;

    }

    return 0;
}
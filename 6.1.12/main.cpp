#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat src,boxfilter_out,blur_out,gaussian_out;
int g_boxfiltervalue=3;
int g_meanblurvalue=3;
int g_gaussianvalue=3;

static void on_BoxFilter(int,void *);
static void on_MeanFilter(int,void *);
static void on_GaussianBlur(int,void *);

int main() {

    system("color5E");
    src = imread("panda.jpg");

    if (!src.data) {
        printf("no image \n");
        return false;
    }

    boxfilter_out = src.clone();
    blur_out = src.clone();
    gaussian_out = src.clone();

    namedWindow("src", 1);
    imshow("src", src);

    //fangkuanglvbo
    namedWindow("boxfilter_result");
    createTrackbar("size value", "boxfilter_result", &g_boxfiltervalue, 40, on_BoxFilter);
    on_BoxFilter(g_boxfiltervalue, 0);

    //junzhilvbo
    namedWindow("blur_result", 1);
    createTrackbar("size value:", "blur_result", &g_meanblurvalue, 40, on_MeanFilter);
    on_MeanFilter(g_meanblurvalue, 0);

    //gaosilvbo
    namedWindow("gaussian_result", 1);
    createTrackbar("size value:", "gaussian_result", &g_gaussianvalue, 40, on_GaussianBlur);
    on_GaussianBlur(g_gaussianvalue, 0);

    cout << endl << "\t,please change the trackbar\n\n" << "\t enter 'q' to quit \n";

    while (char(waitKey(1)) != 'q') {}

    return 0;

}

static void on_BoxFilter(int,void *) {
    boxFilter(src, boxfilter_out, -1, Size(g_boxfiltervalue + 1, g_boxfiltervalue + 1));
    imshow("boxfilter_result", boxfilter_out);
}

static void on_MeanFilter(int,void *) {
    blur(src, blur_out, Size(g_meanblurvalue + 1, g_meanblurvalue + 1), Point(-1, -1));
    imshow("blur_result", blur_out);
}

static  void on_GaussianBlur(int,void *) {
    GaussianBlur(src, gaussian_out, Size(g_gaussianvalue * 2 + 1, g_gaussianvalue * 2 + 1), 0, 0);
    imshow("gaussian_result", gaussian_out);
}





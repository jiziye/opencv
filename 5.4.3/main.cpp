#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

static void on_ContrastAndBright(int,void *);
static void ShowHelpText();

int g_nConstrastValue;
int g_nBrightValue;

Mat g_srcImage,g_dstImage;


int main() {
    g_srcImage = imread("./../scene.jpg");
    cout << "g_srcImage.data: " << (long*)g_srcImage.data << endl;

    if (g_srcImage.empty()) {
        printf("error");
        return -1;
    }
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

    g_nBrightValue = 80;
    g_nConstrastValue = 80;

    namedWindow("result", 1);

    createTrackbar("constrast:", "result", &g_nConstrastValue, 300, on_ContrastAndBright);
    createTrackbar("brightness:", "result", &g_nBrightValue, 200, on_ContrastAndBright);

    on_ContrastAndBright(g_nConstrastValue, 0);
    on_ContrastAndBright(g_nBrightValue, 0);

    while (char(waitKey(1)) != 'q') {}
    return 0;
}

static void on_ContrastAndBright(int,void *) {
//    namedWindow("SRC", 1);
    for (int y = 0; y < g_srcImage.rows; y++) {
        for (int x = 0; x < g_srcImage.cols; x++) {
            for (int c = 0; c < 3; c++) {
                g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(
                        (g_nConstrastValue * 0.01) * (g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);

            }
        }
    }

    imshow("src", g_srcImage);
    imshow("result", g_dstImage);

}



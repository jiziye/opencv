#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("ball.jpeg");
    imshow("src", src);

    Mat mid, dst;
    cvtColor(src, mid, COLOR_BGR2GRAY);
    GaussianBlur(mid, mid, Size(9, 9), 2, 2);

    vector<Vec3f> circles;
    HoughCircles(mid, circles, HOUGH_GRADIENT, 1.5, 100, 200, 100, 0, 0);
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);

        circle(src, center, radius, Scalar(155, 50, 255), 3, 8, 0);
    }

    imshow("result", src);
    waitKey(0);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
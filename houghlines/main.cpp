#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main() {
    //src image
    Mat src = imread("building.jpeg");
    imshow("src", src);

    //canny edge
    Mat mid, dst;
    Canny(src, mid, 50, 200, 3);
    imshow("mid", mid);
    cout<<"&&&& "<<mid.depth()<<" "<<mid.type()<<mid.channels()<<endl;

    waitKey(0);

    //gray to BGR
    cvtColor(mid, dst, COLOR_GRAY2BGR);

    vector<Vec2f> lines;
    HoughLines(mid, lines, 1, CV_PI / 180, 150, 0, 0);

    vector<Vec4i> lines_p;
    HoughLines(mid, lines_p, 1, CV_PI / 180, 80, 50, 10);


    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;

        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));

        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(dst, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
    }

    Mat dst_p;
    for (size_t i = 0; i < lines_p.size(); i++) {
        Vec4i l = lines_p[i];
//        line(dst_p, Point(1[0], 1[1]), Point(1[2], 1[3]), Scalar(186, 88, 255), 1, LINE_AA);
    }

    imshow("mid", mid);
    imshow("houghlines_result", dst);
 //   imshow("houghlinesP_result", dst_p);
    waitKey(0);

    return 0;
}

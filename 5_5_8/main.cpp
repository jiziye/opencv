#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

int main() {

    Mat srcImage = imread("scene.jpg",0);
    cout << "empty " << srcImage.empty() << endl;

    cout << "channels " << srcImage.channels() << endl;
    cout << "type " << srcImage.type() << endl;
    cout << "rows,cols " << srcImage.rows << "," << srcImage.cols << endl;
    cout << "size " << srcImage.size << endl;

    cout << "img.data " << (long *) srcImage.data << endl;
    //cout<<srcImage.at(1,1);


    if (!srcImage.data) {
        printf("error");
        return false;
    }

    imshow("src", srcImage);
    //ShowHelpText();
//    cv::waitKey(0);

    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);

    Mat padded;
    copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[2] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};

//    std::vector<cv::Mat> planes(2, Mat::zeros(padded.size(), CV_32F));
//    planes[0] = Mat_<float>(padded);

    Mat complexI;
    merge(planes, 2, complexI);

    dft(complexI, complexI);

    split(complexI, planes);;
    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitudeImage = planes[0];

    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage);

    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);

    imshow("f", magnitudeImage);
    waitKey();

    return 0;
}





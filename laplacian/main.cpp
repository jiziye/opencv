#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("panda.jpg");
    if (!src.data) {
        printf("read image error. \n");
        return false;
    }
    imshow("src", src);
    cout<<"src.depth(): "<<src.depth()<<endl;



    //gaussian blur
    Mat dst;
    GaussianBlur(src, dst, Size(3, 3), 0, 0, BORDER_DEFAULT);

    //dst to gray
    Mat gray;
    cvtColor(dst, gray, COLOR_RGB2GRAY);

    Mat result,abs_result;
    Laplacian(gray,result,CV_16S,3,1,0,BORDER_DEFAULT);

    convertScaleAbs(result,abs_result);
    imshow("result_abs",abs_result);



    //waitKey(0);
    while (1) {
        int key;
        key = waitKey(0);
        if (char(key) = 'q')
            return false;
    }


}
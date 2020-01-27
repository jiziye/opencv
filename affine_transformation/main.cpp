#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define window_1 "src"
#define window_2 "warp"
#define window_3 "warp_rotate"

static void ShowHelpText();

int main() {

    ShowHelpText();

    //2 triangle
    Point2f srctriangle[3];
    Point2f dsttriangle[3];

    Mat rotMat(2,3,CV_32FC1);
    Mat warpMat(2,3,CV_32FC1);

    Mat src,dst_warp,dst_warp_rotate;

    src=imread("panda.jpg");
    if(!src.data){
        printf("read image error. \n");
        return false;
    }

    dst_warp=Mat::zeros(src.rows,src.cols,src.type());
   // dst_warp.create(src.size(),src.type());
    srctriangle[0]=Point2f(0,0);
    srctriangle[1]=Point2f(static_cast<float>(src.cols-1),0);
    srctriangle[2]=Point2f(0,static_cast<float>(src.rows-1));


    dsttriangle[0]=Point2f(static_cast<float>(src.cols*0.0), static_cast<float>(src.rows*0.33));
    dsttriangle[1]=Point2f(static_cast<float>(src.cols*0.65), static_cast<float>(src.rows*0.35));
    dsttriangle[2]=Point2f(static_cast<float>(src.cols*0.15), static_cast<float>(src.rows*0.6));

    warpMat=getAffineTransform(srctriangle,dsttriangle);

    warpAffine(src,dst_warp,warpMat,dst_warp.size());

    Point center=Point(dst_warp.cols/2,dst_warp.rows/2);
    double angle=-30.0;
    double scale=0.8;

    rotMat=getRotationMatrix2D(center,angle,scale);
    warpAffine(dst_warp,dst_warp_rotate,rotMat,dst_warp.size());

    imshow(window_1,src);
    imshow(window_2,dst_warp);
    imshow(window_3,dst_warp_rotate);
    waitKey(0);


    //    std::cout << "Hello, World!" << std::endl;
    return 0;
}
static void ShowHelpText()
{
    printf("\n\n\n\t welcome~~ \n\n");
    printf("\t opencv_version" CV_VERSION );
}
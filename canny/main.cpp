#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src=imread("panda.jpg");


    imshow("src",src);
    // Canny(src,src,150,100,3);
   // imshow("result",src);

    Mat src1=src.clone();
    std::cout <<src1.type() << std::endl;

    //color to gray
    Mat gray;
    cvtColor(src1,gray,COLOR_BGR2GRAY);
    imshow("gray",gray);

    //blur
    Mat gray_blur;
    blur(gray,gray_blur,Size(3,3));
    imshow("blur",gray_blur);

    //canny to get edge
    Mat edge;
    Canny(gray_blur,edge,3,9,3);
    imshow("edge",edge);//mono edge image

    //create black image
    Mat dst;
    dst.create(src1.size(),src1.type());
    imshow("dst_0",dst);
    dst=Scalar::all(0);//black image
    imshow("dst",dst);

    //src1+edge=dst
    src1.copyTo(dst,edge); //color edge image
    imshow("result",dst);

    waitKey(0);

    return 0;

}


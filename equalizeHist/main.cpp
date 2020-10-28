#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src,dst;
    src=imread("earth.jpg");
    if(!src.data){printf("read image error. \n");return false;}
    cvtColor(src,src,COLOR_BGR2GRAY);
    imshow("src",src);
    
    //equalizehist
    equalizeHist(src,dst);
    imshow("equa",dst);

    waitKey(0);
    
    return 0;

}

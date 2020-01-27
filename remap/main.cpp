#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
        Mat src,dst;
        Mat map_x,map_y;

        src=imread("panda.jpg");
        if(!src.data){printf("read image error \n");return false;}
        imshow("src",src);

        dst.create(src.size(),src.type());
        map_x.create(src.size(),CV_32FC1);
        map_y.create(src.size(),CV_32FC1);

        for(int j=0;j<src.rows;j++)
        {
            for(int i=0;i<src.cols;i++)
            {
                map_x.at<float>(j,i)= static_cast<float>(src.cols-i);
                map_y.at<float>(j,i)= static_cast<float>(src.rows-j);

            }
        }

        remap(src,dst,map_x,map_y,CV_INTER_LINEAR,BORDER_CONSTANT,Scalar(0,0,0));
        imshow("result",dst);
        waitKey(0);
        //        std::cout << "Hello, World!" << std::endl;
    return 0;
}
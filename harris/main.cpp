#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;

Mat src;
Mat scaled;
int thresh=30;

int main()
{
    src=imread("desk.jpg",0);
    imshow("src",src);
    std::cout<<src.type()<<std::endl;
    
    Mat corner;
    cornerHarris(src,corner,2,3,0.0001);
    std::cout<<"1: "<<corner.type()<<std::endl;

    normalize(corner,corner,0,255,NORM_MINMAX);
    std::cout<<corner.type()<<std::endl;
    //std::cout<<corner<<std::endl;
    
    convertScaleAbs(corner,scaled);
    std::cout<<scaled.type()<<std::endl;
    for(int j=0;j<corner.rows;j++)
    {for(int i=0;i<corner.cols;i++)
        {
            if((int)corner.at<float>(j,i)>thresh+80)
            {
                circle(src,Point(i,j),5,Scalar(10,10,255),2,8,0);
                circle(scaled,Point(i,j),5,Scalar(10,10,255),2,8,0);
            }
        }
    }

    double minvalue=0;
    double maxvalue=0;

    minMaxLoc(corner,&minvalue,&maxvalue,0,0);
 //   std::cout<<"minvalue: "<<minvalue<<" maxvalue: "<<maxvalue;
 
    Mat harrisCorner;
    threshold(corner,harrisCorner,0.0000001,255,THRESH_BINARY);
    

    imshow("src",src);
    imshow("result",harrisCorner);
    imshow("corner",corner);
    imshow("scaled",scaled);

    waitKey();
    return 0;

}
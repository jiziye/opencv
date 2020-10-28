#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/opencv.hpp>
#include<math.h>
#include<string>

using namespace cv;
using namespace std;

int main()
{
    //system("color 2F");

    Mat src1=imread("panda.jpg",1);
    Mat src2=imread("cat.jpg",1);
    if(!src1.data ||  !src2.data )
    {
        printf("read image error. \n");
        return false;
    }
    imshow("src1",src1);
    imshow("src2",src2);

    double minHessian=400;
    SurfFeatureDetector detector(minHessian);
    //Ptr<SURF> detector=SURF::create("detector");
    
    vector<KeyPoint> keypoint1,keypoint2;

    detector.detect(src1,keypoint1);
    detector.detect(src2,keypoint2);

    //detector->detect(src1,keypoint1);
    //detector->detect(src2,keypoint2);

    Mat img_key1,img_key2;
    drawKeypoints(src1,keypoint1,img_key1,Scalar(0,0,255),DrawMatchesFlags::DEFAULT);
    drawKeypoints(src2,keypoint2,img_key2,Scalar::all(-1));

    for(int i=0;i<keypoint1.size();i++)
    {    cout<<"pt: "<<keypoint1[i].pt<<endl;
         cout<<" size: "<<keypoint1[i].size<<" angle: "<<keypoint1[i].angle<<" octave: "<<keypoint1[i].octave<<" class_id:  "<<keypoint1[i].class_id<<endl;}

    imshow("surf dector features",img_key1);
    imshow("surf dector features1",img_key2);

    //integral()
    Mat sum=Mat::zeros(src1.rows+1,src1.cols+1,CV_32FC1);
    Mat sqsum=Mat::zeros(src1.rows,src1.cols,CV_32FC1);

    integral(src1,sum,sqsum);
    
    normalize(sum,sum,0,255,NORM_MINMAX,CV_8UC1,Mat());
    imshow("integral image",sum);

    string t[3]={"255","255","255"};
    //int l[]=static_cast
    //std::cout<<t_1<<std::endl;

   //unsigned int a=33;
   //cout<<"****"<<endl;
   //cout<<a<<endl;

    waitKey();
    return 0;
        


}


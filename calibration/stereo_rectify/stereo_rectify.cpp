#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{

    
    Mat img1 = imread("./../left1.png");
    Mat img2 = imread("./../right1.png");
    if(img1.empty() | img2.empty())
    {
        printf("read image error \n");
    }

    imshow("img1",img1);
    imshow("img2",img2);
    waitKey();

    Mat K1,K2,D1,D2,R,T;
    // K1 = (Mat_<double> (3,3) << 367.66039343485084601,0.00000000000000000,383.06494535676881696,
    //                             0.00000000000000000,367.47852947330636653,249.77022006312148505,
    //                              0.00000000000000000,0.00000000000000000,1.00000000000000000);
    // K2 = (Mat_<double>(3,3) << 367.41398810791054075,0.00000000000000000,376.93139972530980231,
    //                         0.00000000000000000,367.30543948442448254,250.98649747494613393,
    //                         0.00000000000000000,0.00000000000000000,1.00000000000000000);

    // D1 = (Mat_<double>(1,5) << -0.03714779910264787,0.06896521050109194,-0.11456687279457890,
    //                      0.05642247213855468,0.00000000000000000);
    // D2 = (Mat_<double>(1,5) <<-0.03227924969760760,0.08729804160500855,-0.20058822155545081,
    //                   0.14470784250692609,0.00000000000000000);


    // R = (Mat_<double>(3,3) << 0.99975921223665176, -0.00185756094684081, 0.02186474365910062, 
    //                             0.00185376175212171, 0.99999826295910843, 0.00019402611217360, 
    //                             -0.02186506609447545, -0.00015344736754484, 0.99976091908945386);
    // T = (Mat_<double>(1,3) << -119.54652216398160647, -0.19733558305898505, 0.68048567634258506);                                    

    //cout << "K1  = "<< format(K1,Formatter::FMT_PYTHON) << endl;        
                                         
    cout << "K1  = "<< K1 << endl;    //
    cout << "K2  = "<< K2 << endl;
    cout << "D1  = "<< D1 << endl;
    cout << "D2  = "<< D2 << endl;
    cout << "R  = "<<  R << endl;
    cout << "T  = "<< T << endl;


    Size imagesize = img1.size();
    Mat R1,R2,P1,P2,Q;
    Rect validRoi[2];
     cout << "*****************************"  << endl;
    //计算旋转矩阵和投影矩阵
    cv::stereoRectify(K1,D1,K2,D2,imagesize,R,T,R1,R2,P1,P2,Q,CALIB_ZERO_DISPARITY,0,imagesize,&validRoi[0],&validRoi[1]);
    cout << "*****************************"  << endl;
 
    cout << "R1  = "<< format(R1,Formatter::FMT_PYTHON) << endl;
    cout << "R2  = "<< format(R2,Formatter::FMT_PYTHON) << endl;
    cout << "P1  = "<< format(P1,Formatter::FMT_PYTHON) << endl;
    cout << "P2  = "<< format(P2,Formatter::FMT_PYTHON) << endl;
    cout << "Q  = "<< format(Q,Formatter::FMT_PYTHON) << endl;


   //计算校正查找映射表
    Mat rmap[2][2];
    cv::initUndistortRectifyMap(K1,D1,R1,P1,imagesize,CV_16SC2,rmap[0][0],rmap[0][1]);
    cv::initUndistortRectifyMap(K1,D1,R1,P1,imagesize,CV_16SC2,rmap[1][0],rmap[1][1]);
    
    Mat img_rect(imagesize.height, imagesize.width *2, CV_8UC1 );
    imshow("rectified",img_rect);

    Mat img1r,img2r,img;
    remap(img1,img1r,rmap[0][0],rmap[0][1],CV_INTER_AREA);
    remap(img2,img2r,rmap[1][0],rmap[1][1],CV_INTER_AREA);

    hconcat(img1r,img2r,img);
    imshow("img1r",img1r);
    imshow("img2r",img2r);

    return 0;
}
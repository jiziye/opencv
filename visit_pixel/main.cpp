//
// Created by mynt on 12/18/19.
//

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{   

    Mat src = imread("test.jpeg");
    //imread depth image,format :: 16UC1
    //Mat src=imread("depth65.png",CV_LOAD_IMAGE_UNCHANGED);
    imshow("src",src);

//    int rownumber=src.rows;
//    int colnumber=src.cols*src.channels();
//

//    //use pointer
////    for (int i=0;i<rownumber;i++)
////    {
////        uchar* data=src.ptr<uchar>(i);
////        for (int j=0;j<colnumber;j++)
////        {cout<<i<<" "<<j<<" "<<long(data[j])<<endl;}
////    }


    //use iterator
//    Mat_<Vec3b>::iterator it=src.begin<Vec3b>();
//    //Mat_<Vec3b>::iterator itend=src.end<Vec3b>();
//
//    for(; it!=src.end<Vec3b>(); ++it)
//    {
//
//        cout<<(*it)<<endl;
//
//    }

    //use dynamic address
    int rownumber=src.rows;
    int colnumber=src.cols;

    for (int i=0;i<rownumber;i++)
    {
        for(int j=0;j<colnumber;j++)

        {
            
            cout<<src.at<Vec3b>(i,j)[0] << src.at<Vec3b>(i,j)[1] << src.at<Vec3b>(i,j)[2] << endl;

            //cout 16UC1 IAMGE: ushort 2bytes 16bits
            cout<<src.at<ushort>(i,j);
        }
    }

    //cout << src << endl;
    cout << "channels: " << src.channels() << endl;
    cout << "type: " << src.type() << endl;

    waitKey(0);

    return true;
}
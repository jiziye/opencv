#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int n=200;
Mat out;
Mat tmp,dst1,dst2;

void Resize(int,void *);


int main() {
    Mat src=imread("panda.jpg");


    //tmp=src.clone();
    tmp=src;

    imshow("src",src);
    imshow("tmp",tmp);

    resize(tmp,dst1,Size(512,512),0,0,3);
    resize(tmp,dst2,Size(tmp.cols/2,tmp.rows/2),0,0,3);

    imshow("dst1",dst1);
    imshow("dst2",dst2);

    cout<<tmp.cols <<" "<<tmp.rows<<endl;
    cout<<dst1.cols<<" "<<dst1.rows<<endl;
    cout<<dst2.cols<<" "<<dst2.rows<<endl;

    namedWindow("out",W);
    resize(tmp,out,Size(n,n),0,0,3);
    createTrackbar("scale","out",&n,512,Resize);

    waitKey(0);

    return 0;
}


void Resize(int,void *)
{

resize(tmp,out,Size(n,n),0,0,3);
imshow("out",out);

}
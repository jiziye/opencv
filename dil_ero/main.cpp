#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat image,out;

int flag=0;//erode or dilate
int kernelsize = 3;

void Process();
void bar(int, void *);
void size(int, void *);

int main() {
    image = imread("panda.jpg");
    if (!image.data) {
        printf("error");
        return false;
    }

    namedWindow("src");
    namedWindow("dilate");
    namedWindow("erode");

    imshow("src", image);

    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));

    Mat out_dilate;
    dilate(image, out_dilate, element);
    imshow("dilate", out_dilate);

    Mat out_erode;
    erode(image, out_erode, element);
    imshow("erode", out_erode);



//createtrackbar

    namedWindow("result");


    Mat element_defined;
    erode(image, out, element_defined);
    imshow("result", out);

    createTrackbar("erode/dilate", "result", &flag, 1, bar);
    createTrackbar("kernel size", "result", &kernelsize, 21, size);

    while (char(waitKey(1)) != 'q') {}

    return 0;


}

void Process(){
    //kernel size
    Mat  element_defined=getStructuringElement(MORPH_RECT,Size(2*kernelsize+1,2*kernelsize+1),Point(kernelsize,kernelsize));

    //change erode/dilate

    if(flag==0){
        erode(image,out,element_defined);
    }
    else{
        dilate(image,out,element_defined);
    }
    imshow("result",out);

}

void bar(int,void *){
    Process();
}

void size(int,void *){
    Process();
}

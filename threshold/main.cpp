#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME "program window"

int thresholdvalue=100;
int thresholdtype=3;
Mat src,gray,dst;

void on_threshold(int,void*);

int main() {
    std::cout << "Hello, World!" << std::endl;
    src=imread("scene.jpg");
    if(!src.data){printf("read image error \n");return false;}

    cvtColor(src,gray,COLOR_RGB2GRAY);
    namedWindow(WINDOW_NAME,WINDOW_AUTOSIZE);

    createTrackbar("mode",WINDOW_NAME,&thresholdtype,4,on_threshold);
    createTrackbar("value",WINDOW_NAME,&thresholdvalue,255,on_threshold);

    on_threshold(0,0);

    while(1)
    {
       int key;
       key=waitKey(20);
       if((char)key==27){break;}
    }

}

void on_threshold(int,void *)
{
    threshold(gray,dst,thresholdvalue,255,thresholdtype);
    imshow(WINDOW_NAME,dst);
}
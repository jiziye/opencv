#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/photo/photo.hpp>

using namespace std;
using namespace cv;

#define window_name1 "src"
#define window_name2 "result"

Mat src1;
Mat inpaintMask;
Point previousPoint(-1,-1);

//define on_mouse 
static void On_Mouse(int event,int x,int y,int flags,void*)
{
    if(event==EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        previousPoint = Point(-1,-1);
    else if(event == EVENT_LBUTTONDOWN)
        previousPoint = Point(x,y);
    else if(event==EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
       Point pt(x,y);
       if(previousPoint.x<0)
       previousPoint=pt;

       line(inpaintMask,previousPoint,pt,Scalar::all(255),10,8,0);
       line(src1,previousPoint,pt,Scalar::all(255),10,8,0);
       previousPoint = pt;
       imshow(window_name1,src1); 
    }
}


//int main 
int main(int argc,char** argv)
{
    Mat src=imread("cat.jpg");
    if(!src.data){
        printf("read image errror\n");
        return false;
    }

    src1=src.clone();
    imshow(window_name1,src1);
        
    //define mask
    inpaintMask=Mat::zeros(src1.size(),CV_8U);

    //set mouse callback
    setMouseCallback(window_name1,On_Mouse,0);

    while(1)
    {
        char c=(char)waitKey();

        if (c=='1' || c==' ')
        {
            Mat inpaintedimage;
            inpaint(src1,inpaintMask,inpaintedimage,3,1);
            imshow(window_name2,inpaintedimage);
        }


        if(c=='2')
        {
            //imshow(window_name2,src1);
            inpaintMask=Scalar::all(0);
            src.copyTo(src1);
            imshow("window_name1",src1);
        }

        if(c==27 || c=='q')
        {
            break;
        }
    

   }

    return 0;

}
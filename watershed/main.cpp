#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define  window_name "program window"
static void on_mouse(int event,int x,int y,int flags, void* );
Point prevPt=Point(-1,-1);
Mat src,src_image,gray_image,mask_image;

int main(int argc,char ** argv)
{   

    src=imread("panda.jpg");
    imshow(window_name,src);

   
    src_image=src.clone();
    //src.copyTo(src_image);

    cvtColor(src_image,mask_image,COLOR_BGR2GRAY);
    cvtColor(mask_image,gray_image,COLOR_GRAY2BGR);
    mask_image=Scalar::all(0);

    setMouseCallback(window_name,on_mouse,0);

    while(1)
    {
        int c=waitKey(0);
        if((char)c==27)
        break;

        if((char)c=='2')
        {
            mask_image=Scalar::all(0);
            src_image.copyTo(src);
            imshow("iamge",src);
        }

        if((char)c=='1' || (char)c==' ')
        {
            vector<vector<Point>> contours;
            vector<Vec4i> hierarchy;
            //int compCount=0;
            int i,j,compCount=0;

            findContours(mask_image,contours,hierarchy,RETR_CCOMP,CHAIN_APPROX_SIMPLE);
            if(contours.empty())
            continue;

            Mat mask(mask_image.size(),CV_32S);
            mask=Scalar::all(0);

            for(int index=0;index>= 0;index=hierarchy[index][0],compCount++)
            drawContours(mask,contours,index,Scalar::all(compCount+1),-1,8,hierarchy,INT_MAX);
            
            if(compCount == 0)
            continue;

            vector<Vec3b> colorTab;
            for(i=0;i<compCount;i++)
            {
                int b=theRNG().uniform(0,255);
                int g=theRNG().uniform(0,255);
                int r=theRNG().uniform(0,255);

                colorTab.push_back(Vec3b((uchar)b,(uchar)g,(uchar)r));
               
            }

            double time=(double)getTickCount();
            watershed(src_image,mask);
            time=(double)getTickCount()-time;
            printf("\t time= %gms\n",time*1000./getTickFrequency());

            Mat watershedImage(mask.size(),CV_8UC3);
            for(i=0;i<mask.rows;i++)
                for(j=0;j<mask.cols;j++)
                {
                    int index=mask.at<int>(i,j);
                    if(index == -1)
                    watershedImage.at<Vec3b>(i,j)=Vec3b(255,255,255);
                    else if(index<0|| index>compCount)
                    watershedImage.at<Vec3b>(i,j)=Vec3b(0,0,0);
                    else
                    watershedImage.at<Vec3b>(i,j)=colorTab[index-1];
                }

                watershedImage=watershedImage*0.5+gray_image*0.5;
                imshow("watershed transform",watershedImage);


                   }

    }

    return 0;
}

static void on_mouse(int event,int x,int y,int flags, void *)
{
    if(x<0 || x>=src.cols || y<0 || y>=src.rows)
    return;

    if(event==EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
    prevPt=Point(-1,-1);

    else if(event == EVENT_LBUTTONDOWN)
    prevPt=Point(x,y);

    else if(event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
        Point pt(x,y);
        if(prevPt.x<0)
        prevPt=pt;
        line(mask_image,prevPt,pt,Scalar::all(255),5,8,0);
        line(src_image,prevPt,pt,Scalar::all(255),5,8,0);
        prevPt=pt;
        imshow(window_name,src_image);
    }
}
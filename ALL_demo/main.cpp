#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/legacy/legacy.hpp>
#include<opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;

Mat src1;

//17.trackbar
Mat src2;
Mat dst17;

int alpha_value;
int alpha_value_max = 100;
double alpha;
double beta;

void on_Trackbar(int,void*)
{
    alpha = (double) alpha_value/alpha_value_max;
    cout<<alpha<<endl;
    beta = (1.0-alpha);
    cout<<beta<<endl;
    addWeighted(src1,alpha,src2,beta,3,dst17);
    imshow("dst17",dst17);
}


//18.setmousecallback
Mat showImg;
Rect select1;

bool select_flag = false;

void onMouse(int event, int x, int y,int flags, void* param)
{       
    if(event == EVENT_LBUTTONDOWN)
    {
        select1.x = x;
        select1.y = y;
        select_flag = true;
        cout<<"click point: ["<<x<<","<<y<<"]"<<endl;
    }
    else if(select_flag && event == EVENT_MOUSEMOVE)
    {  
        
        src1.copyTo(showImg); 
        Point p1,p2;
        p1 = Point(select1.x, select1.y );
        p2 = Point(x,y);
        
        rectangle(showImg,p1,p2,Scalar(0,255,0),2);
        imshow("showimg",showImg);
        
        select1.width = p2.x-p1.x;
        select1.height = p2.y- p1.y;

        Mat rect_image = src1(select1);
        imshow("rect_image",rect_image);
        
        
    }
    else if(select_flag && event == EVENT_LBUTTONUP)
    {
        select_flag = false;
    }
}




void example(int acWelcome[]){
    cout<<sizeof(acWelcome)<<endl;
    return;
}


int main(int argc, char** argv)
{   
    //2.
    src1 = imread("./../logo.jpg");
    imshow("src1",src1);
   
#if 0
    //3.
    Mat dst_erode;
    Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
    
    erode(src,dst_erode,element);
    imshow("erode",dst_erode);
    
    
    //4.blur
    Mat dst_blur;
    blur(src,dst_blur,Size(3,3));
    imshow("blur",dst_blur);

    //5.canny
    Mat src_gray,gray_blur;
    cvtColor(src,src_gray,COLOR_BGR2GRAY);
    blur(src_gray,gray_blur,Size(3,3));
    Mat edges_canny,edges_canny_gray;
    Canny(dst_blur,edges_canny,50,150,3);
    Canny(gray_blur,edges_canny_gray,50,150,3);

    imshow("canny edge",edges_canny);
    imshow("canny edge gray",edges_canny_gray);

    //6.read video
    VideoCapture video("./../cat.mp4");
    //while(char(waitKey(1)) != 'q')
    while(1)
    {
        Mat video_1;
        video >> video_1;
        imshow("video_1",video_1);
        
        if(video_1.empty()) {break;}
        waitKey(30);
    }

    //7.read camera
    VideoCapture cap(0);
    //Mat video_image;
    while(char(waitKey(1))!= 'q')
    {   
        Mat video_image;
        cap >> video_image;
        imshow("video",video_image);
    }


    //14
    printf("test. \n");
    printf("\t %d",100);
   // getchar();

   

 

    //15
    // Mat rgba(100,100,CV_8UC4,Scalar(1,2,3,4));
    // Mat bgr(rgba.rows,rgba.cols,CV_8UC3);
    // Mat alpha(rgba.rows,rgba.cols,CV_8UC1);

    // Mat out[] = {bgr,alpha};
    // int fromTo[] = {0,2,1,1,2,0,3,3};
    
    Mat src_alpha(src.size(),CV_8UC4);
    Mat alpha(src.size(),CV_8UC1,Scalar::all(255));
    Mat in[]={src,alpha};

    imshow("test",alpha);
    int fromTo[] = {0,0,1,1,2,2,3,3};
    mixChannels(in,2,&src_alpha,1,fromTo,4);
    imshow("src_alpha",src_alpha);
    //cout<<src_alpha<<endl;

    imwrite("src_alpha.png",src_alpha);

    //16
    Mat logo = imread("./../logo.jpg");
    imshow("logo",logo);
    Mat src_roi=src1(Rect(50,50,logo.cols,logo.rows));
    
    addWeighted(src_roi,0.5,logo,0.5,0.,src_roi);
    namedWindow("src+logo");
    imshow("src+logo",src1);
   
    //17.trackbar      
    src2 = imread("./../color.jpg");
    imshow("src2",src2);
   
    if(!src2.data || !src1.data)
    {
        printf("read image error.  \n");
        return false;
    }

    alpha_value = 70;
    namedWindow("dst17",1);
    char TrackbarName[50];
    sprintf(TrackbarName,"alpha value %d ",alpha_value);
    
    createTrackbar(TrackbarName,"dst17", &alpha_value, alpha_value_max, on_Trackbar);
    
    on_Trackbar(alpha_value,0);

    //18.setmousecallback
    src1.copyTo(showImg);
    imshow("showimg",showImg);

    setMouseCallback("showimg",onMouse,0);
 
    //20.basic draw shape
    Mat shape_image = Mat::zeros(600,1280,CV_8UC3);
    Mat rookImage = Mat::zeros(600,600,CV_8UC3);
    RotatedRect box;

    ellipse(shape_image,Point(shape_image.cols/2,shape_image.rows/2),Size(shape_image.rows/4,shape_image.cols/4),90,0,360,Scalar(255,255,255));
    line(shape_image,Point(100,100),Point(200,100),Scalar(255,255,255));
    circle(shape_image,Point(100,100),100,Scalar(255,255,255));
    imshow("ellipse",shape_image);


    //21.visit pixel
    int rowsNumber = src1.rows;
    int colsNumber = src1.cols * src1.channels();

    for(int i = 0; i<rowsNumber; i++)
    {
         uchar* ptr_src1 = src1.ptr<uchar>(i);
         //cout<<ptr_src1<<endl;
    
        for(int j = 0;j < colsNumber; j++)
        {
           ptr_src1[j]=ptr_src1[j]/2;
        }
    }

    for(int i = 0; i < rowsNumber; i++)
    {
        uchar* ptr_src1_1 =  (uchar*)src1.data + i* colsNumber;
        for(int j = 0; j< colsNumber; j++)
        {
            int value = ptr_src1_1[j];
            cout<<"i"<<i<<"hang "<<j<<"lie: "<<value<<endl;
        }
    }

    cout<<src1.rows<<"  "<<src1.cols<<endl;
    imshow("visit pixel",src1);

    //22.iterator
    Mat_<Vec3b>::iterator it = src1.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = src1.end<Vec3b>();

    for(; it != itend; ++it)
    {
        cout<<(*it)<<endl;
    }

    //src1.ptr
    resize(src1,src1,Size(200,200));
    imshow("resize",src1);
    
    //23.at<>
    for(int i = 0; i < src1.rows; i++)
    {
       Vec3b vec;
        for(int  j = 0; j < src1.cols; j++)
        {   
           // cout<< src1.at<Vec3b>(i,j)<<endl;
            vec = src1.at<Vec3b>(i,j);
            cout<<vec<<endl;
        }
    }
#else
    //26.split
    vector<Mat> mvbegin;
    split(src1,mvbegin);
    Mat src1_0 = mvbegin[0];
   
    cout<<sizeof(char)<<" "<<sizeof(int)<<" "<<sizeof(long)<<endl;
    cout<<sizeof(char*)<<" "<<sizeof(int*)<<" "<<sizeof(long*)<<endl;


    // int acWelcome[]={1,3,4,6,8};
    // example(acWelcome);
    // cout<<"%%%%%%"<<sizeof(acWelcome)<<endl;
   
#endif
    waitKey(0);
    return 0;

}

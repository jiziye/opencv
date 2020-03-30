#include <iostream>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>

#include <linux/videodev2.h>

//#define S1030 
#define D1000

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    cout << "please choose which video to open : 0 or 1: " << endl;
    int dex;
    cin >> dex;
    cap.open(dex);
   
   VideoCapture cap_depth;
   cap_depth.open(2);

    if (!cap.isOpened())
        printf("open camer failed. \n");


    cout << "get cap format: " << cap.get(CV_CAP_PROP_FORMAT) << endl;
    cout << "get cap_depth format: " << cap_depth.get(CV_CAP_PROP_FORMAT) << endl;
#ifdef D1000
    cap.set(CV_CAP_PROP_FRAME_WIDTH,2560);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
    cap_depth.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    cap_depth.set(CV_CAP_PROP_FRAME_HEIGHT,720);
#endif
    //frame 
    int w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int size = w * h;

    cout <<  "cap get frame width * height =  " << w  << " x " 
         <<  h << endl;

    //depth
    int w_d = cap_depth.get(CV_CAP_PROP_FRAME_WIDTH);
    int h_d = cap_depth.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout <<  "cap get depth width * height =  " << w_d  << " x "  
         <<  h_d << endl;


    unsigned int mode = cap.get(CAP_PROP_MODE);
    // switch (mode)
    // {
    // case V4L2_PIX_FMT_BGR24:
    //     cout << "FMT_BGR24" << endl;
    //     break;
    // case V4L2_PIX_FMT_YVU420:
    //     cout << "FMT_YVU420" << endl;
    //     break;
    // case V4L2_PIX_FMT_YUV411P:
    //     cout << "FMT_YUV411P" << endl;
    //     break;
    // case V4L2_PIX_FMT_MJPEG:
    //     cout << "FMT_MJPG" << endl;
    //     break;
    // case V4L2_PIX_FMT_JPEG:
    //     cout << "FMT_JPG" << endl;
    //     break;
    // case V4L2_PIX_FMT_YUYV:
    //     cout << "FMT_YUYV" << endl;
    //     break;
    // case V4L2_PIX_FMT_RGB24:
    //     cout << "FMT_RGB24" << endl;
    //     break;
    // case V4L2_PIX_FMT_UYVY:
    //     cout << "FMT_UYVY" << endl;
    //     break;
    // default:
    //     cout << "mode not found!" << endl;
    //     break;
    // }

    // !!!
    //cap.set(cv::CAP_PROP_CONVERT_RGB, 1);

    while (char(waitKey(1)) != 'q')
    {
        Mat raw;
        cap.read(raw);
           
        // cv::Mat mat_dst = cv::Mat(raw.size(), CV_8UC1);
        // cv::cvtColor(raw, mat_dst, cv::COLOR_YUV2RGB_YUYV);

        //cv::Mat mat = raw.clone();
        imshow("raw",raw);

        Mat left, right;
#ifdef S1030
        
        left = Mat(raw.size(), CV_8UC3);
        right = Mat(raw.size(), CV_8UC3);

        unsigned char *data = raw.data;
        int size = raw.rows * raw.cols;

        for (int i = 0; i < size; ++i)
        {
             left.data[i] = data[i * 2];
             right.data[i] = data[i * 2 + 1];
        }
#endif


#ifdef D1000
        left = Mat(h,w/2,CV_8UC3);
        right = Mat(h,w/2,CV_8UC3);

    //use ptr 
        //left frame 
        // for (int i = 0; i < h ; i++)
        // {
        //     uchar *ptr = raw.ptr<uchar> (i);
        //     for( int j = 0; j < (w * 3) / 2; j++)
        //     left.ptr<uchar>(i) [j] = ptr[j];
        // }

        // //right frame 
        // for (int i = 0; i < h; i++)
        // {
        //     uchar *ptr = raw.ptr<uchar> (i);
        //     for( int j = (w * 3) /2 ; j < (w * 3); j++ )
        //     right.ptr<uchar>(i) [j] = ptr[j];
        // }
        
    //use ROI
        // left = raw(Rect(0,0,w/2,h));
        // right = raw(Rect(w/2,0,w/2,h));

        Mat depth(h_d,w_d,CV_8UC3);
       // cap_depth.read(depth);
       
#endif 

        // imshow("left", left);
        // imshow("right", right);
        imshow("depth",depth);
    }

    return 0;
}
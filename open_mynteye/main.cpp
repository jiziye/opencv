#include <iostream>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/opencv.hpp>

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
    if (!cap.isOpened())
    {
        cerr << "open cap failed."<<endl;
        return 1;
    }
    cout << "get cap format: " << cap.get(CV_CAP_PROP_FORMAT) << endl;
    
    unsigned int mode = cap.get(CAP_PROP_MODE);
    cout << "get cap mode: " << mode << endl;

#ifdef S1030    
     // !!!
    cap.set(cv::CAP_PROP_CONVERT_RGB, 0);
#endif 

#ifdef D1000
    VideoCapture cap_depth;
    //cap_depth.open(2);

    if (!cap.isOpened() && !cap_depth.isOpened())
    {
        cerr << "open depth failed."<<endl;
        return 1;
    }
        cout << "get cap format: " << cap.get(CV_CAP_PROP_FORMAT) << endl
             << "get cap_depth format: " << cap_depth.get(CV_CAP_PROP_FORMAT) << endl;

    cap.set(CV_CAP_PROP_FRAME_WIDTH,2560);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
    // cap_depth.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    // cap_depth.set(CV_CAP_PROP_FRAME_HEIGHT,720);
#endif

    //frame 
    int w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int size = w * h;
    int fps = cap.get(CV_CAP_PROP_FPS);

    cout <<  "cap get frame width * height =  " << w  << " x " 
         <<  h << endl;
    cout << "cap get frame: " << fps << endl;

#ifdef D1000
    //depth
    // int w_d = cap_depth.get(CV_CAP_PROP_FRAME_WIDTH);
    // int h_d = cap_depth.get(CV_CAP_PROP_FRAME_HEIGHT);


    // cout <<  "cap get depth width * height =  " << w_d  << " x "  
    //      <<  h_d << endl;
#endif

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

    // int32_t count = 0;

    while (true)
    {
        Mat raw;
        cap.read(raw);
        //imshow("raw",raw);


           
        // cv::Mat mat_dst = cv::Mat(raw.size(), CV_8UC1);
        // cv::cvtColor(raw, mat_dst, cv::COLOR_YUV2RGB_YUYV);
        //cv::Mat mat = raw.clone();
        

        Mat left, right;

#ifdef S1030
        
        left = Mat(raw.size(), CV_8UC1);
        right = Mat(raw.size(), CV_8UC1);

        unsigned char *data = raw.data;
        int size = raw.rows * raw.cols;

        for (int i = 0; i < size; ++i)
        {
             left.data[i] = data[i * 2];
             right.data[i] = data[i * 2 + 1];
        }
#endif


#ifdef D1000
        //color image
        left = Mat(h, w/2, CV_8UC3);
        right = Mat(h, w/2, CV_8UC3);
    
    
        //gray image
        // cvtColor(raw,raw,CV_BGR2GRAY);
        // left = Mat(h,w/2,CV_8UC1);
        // right = Mat(h,w/2,CV_8UC1);

        //use ptr 
        // //left frame 
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

        //use color image,only use width and height,don't need to consider channel
        left = raw(Rect(0, 0, w/2, h ));
        right = raw(Rect(w / 2, 0, w/2, h));
        

        //use gray image
        // left = raw(Rect(0,0,w/2,h));
        // right = raw(Rect(w/2,0,w/2 ,h));
 

    //use left image to dectect pedestrian
        vector<Rect> found;

        HOGDescriptor defaultHog;
        defaultHog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
        defaultHog.detectMultiScale(left,found);

        for (int i = 0; i < found.size();i++)
        {
            Rect r = found[i];
            rectangle(left,r,Scalar(0,0,255));

        }

        
        // Mat depth(h_d,w_d,CV_16UC1);
        // cap_depth.read(depth);
        // cout << depth <<endl;
        //imshow("depth",depth);
        //imshow("raw",raw);

#endif 

        imshow("left", left);
        imshow("right", right);
        Mat image_all;
        hconcat(left,right,image_all);
        imshow("left+right",image_all);

    char key = static_cast<char>(waitKey(1));
              
    //save left frame persistently since enter 's'
    // //bug  
    //     while (key == 32 || key == 's')
    //     {
    //         static int32_t count = 1;
    //         stringstream ss;
    //         ss << (count++) << ".png";
    //         string filename = ss.str();
    //         imwrite(filename,left);
    //         cout << "save " << filename << endl;
    //         if(char(waitKey(1)) == 'e'){break;}
    //     }

    //save left frame single method 1
        if (key == 32 || key == 's')
        {
            static int32_t count = 0;
            count++;
            cout << count << endl;
            stringstream ss_l,ss_r;
            ss_l << "left" << (count) << ".png";
            ss_r << "right" << (count) << ".png";
            string lfilename = ss_l.str();
            string rfilename = ss_r.str();
            imwrite(lfilename,left);
            imwrite(rfilename,right);
            cout << "save " <<  lfilename << endl;
            cout << "save " <<  rfilename << endl;
        }

    //save left frame single method 2 
            // if (key == 32 || key == 's' || key == 'S')
            // {     
            //     static int32_t count = 0;     
            //     char l_name[20];
            //     char r_name[20];
            //     ++count;
            //     cout << count << endl;
            //     snprintf(l_name, sizeof(l_name), "left_%d.jpg", count);
            //     snprintf(r_name, sizeof(r_name), "right_%d.jpg",count);
            //     imwrite(l_name, left);
            //     imwrite(r_name, right);
            //     cout << "save " << l_name << endl;
            //     cout << "save " << r_name << endl;
            // }
    
    
    //esc
         // char key = static_cast<char>(waitKey(1));
          if( key == 27 || key == 'q' | key == 'Q' )
            {break;}




    }

    return 0;
}
#include <iostream>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>

#include <linux/videodev2.h>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened())
        printf("open camer failed. \n");

    unsigned int mode = cap.get(CAP_PROP_MODE);
    switch (mode)
    {
    case V4L2_PIX_FMT_BGR24:
        cout << "FMT_BGR24" << endl;
        break;
    case V4L2_PIX_FMT_YVU420:
        cout << "FMT_YVU420" << endl;
        break;
    case V4L2_PIX_FMT_YUV411P:
        cout << "FMT_YUV411P" << endl;
        break;
    case V4L2_PIX_FMT_MJPEG:
        cout << "FMT_MJPG" << endl;
        break;
    case V4L2_PIX_FMT_JPEG:
        cout << "FMT_JPG" << endl;
        break;
    case V4L2_PIX_FMT_YUYV:
        cout << "FMT_YUYV" << endl;
        break;
    case V4L2_PIX_FMT_RGB24:
        cout << "FMT_RGB24" << endl;
        break;
    case V4L2_PIX_FMT_UYVY:
        cout << "FMT_UYVY" << endl;
        break;
    default:
        cout << "mode not found!" << endl;
        break;
    }

    // !!!
    cap.set(cv::CAP_PROP_CONVERT_RGB, 0);

    while (char(waitKey(1)) != 'q')
    {
        Mat raw;
        cap.read(raw);

        // cv::Mat mat_dst = cv::Mat(raw.size(), CV_8UC1);
        // cv::cvtColor(raw, mat_dst, cv::COLOR_YUV2RGB_YUYV);

        cv::Mat mat = raw.clone();

        Mat left, right;
        left = Mat(mat.size(), CV_8UC1);
        right = Mat(mat.size(), CV_8UC1);

        unsigned char *data = mat.data;
        int size = mat.rows * mat.cols;

        for (int i = 0; i < size; ++i)
        {
            left.data[i] = data[i * 2];
            right.data[i] = data[i * 2 + 1];
        }

        imshow("left", left);
        imshow("right", right);
    }

    return 0;
}
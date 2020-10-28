// #include<iostream>


#include "camera.hpp"

int main(int argc,char** argv)
{
    int index = 0;
    Camera cam(index);
    if(!cam.IsOpened())
    {
        std::cerr << "error: open camera failed" << std::endl;
    }

    std::cout << "cap_prop_convert_rgb disabled: " << cam.Set(cv::CAP_PROP_CONVERT_RGB,0)
              << std::endl;
    std::cout << "cap_prop_format: " << cam.Get(cv::CAP_PROP_FORMAT) << std::endl;

    std::cout << std::flush;

    cv::Mat left,right;

    cam.Capture([&cam,&left,&right](
        const cv::Mat& raw, const cv::Mat& depthmap){
        const int &w = raw.cols,&h = raw.rows;
        const int size= w * h;

        if(left.cols != w || left.rows != h || left.type()!= CV_8UC1)
            left = cv::Mat(h,w,CV_8UC1);
        if(right.cols != w || right.rows != h || right.type()!= CV_8UC1)
            right = cv::Mat(h,w,CV_8UC1);
        
        unsigned char *data = raw.data;
        for (int i=0 ; i < size; ++i){
            left.data[i] = data[i*2];
            right.data[i] = data[i*2 + 1];
        }

        cv::imshow("left",left);
        cv::imshow("right",right);

      
        char key = (char) cv::waitKey(10);
        return !(key == 27 || key == 'q' || key == 'Q');

        });
        return 0;
    }

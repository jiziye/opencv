#ifndef CAMERA_HPP_
#define CAMERA_HPP_
#pragma once


#include <functional>
#include <iostream>
#include <sstream>

#include<opencv2/opencv.hpp>

class Camera{
    public:
        //  another name/alias
        using VideoCapture = cv::VideoCapture;
        using FrameCallback = std::function<bool(const cv::Mat&,const cv::Mat&)>;

        Camera(int index=0) : cap_(new VideoCapture(std::move(index))),
#ifdef USE_OPENNI
            use_openni_(index == cv::CAP_OPENNI || index == cv::CAP_OPENNI2),
#endif
            fps_(-1){            
                int flag = 0;
#ifdef USE_OPENNI
            if(use_openni_){
                flag = cv::CAP_OPENNI_IMAGE_GENERATOR;
                Set(cv::CAP_OPENNI_IMAGE_GENERATOR_OUTPUT_MODE,cv::CAP_OPENNI_VGA_30HZ);
            }
#endif      
            std::cout << "capture frame width: " << Get(flag + cv::CAP_PROP_FRAME_WIDTH)
            << " , HEIGHT: " << Get(flag + cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
            fps_ = Get(flag + cv::CAP_PROP_FPS);
            std::cout << "capture fps: "<< fps_ <<std::endl
#ifdef USE_OPENNI
            << " USE openni: " << use_openni_ << std::endl
#endif  
            << std::endl;

            }

            virtual ~Camera() {}
            bool UseOpenNI(){
#ifdef USE_OPENNI
            return use_openni_;
#else       
            return false;
#endif
            }


    double Get(int prop_id) const {
        return cap_ ->get(prop_id);
    } 

    bool Set(int prop_id,double value){
        return cap_->set(prop_id,value);
    }

    bool IsOpened(){
#ifdef USE_OPENNI
        return use_openni_ || cap_ -> isOpened();
#else
        return cap_ ->isOpened();
#endif
    }

    void Preview(FrameCallback callback = nullptr){
        cv::namedWindow("camera",1);
        Capture([&callback] (const cv::Mat& frame, const cv::Mat& depthmap){
            cv::imshow("camera",frame);
            if(callback && !callback(frame,depthmap)){
                return false;
            }
        char key = (char) cv::waitKey(30);
        return !(key == 27 || key == 'q' || key == 'Q');
        });
    }

    void Capture(FrameCallback callback){
        if(!callback){
            std::cerr << "error: null framecallback\n";
            return;
        }

        cv::Mat frame;
        cv::Mat depthmap;
        double t;
        for(;;){
            t = (double)cv::getTickCount();

#ifdef USE_OPENNI
            if (use_openni_){
                cap_->grab();
                cap_->retrieve(depthmap,cv::CAP_OPENNI_DEPTH_MAP);
                cap_->retrieve(frame,cv::CAP_OPENNI_BGR_IMAGE);
            }
            else{cap_ -> read(frame);
#else  
            cap_ -> read(frame);
#endif
            if(frame.empty()){
                std::cerr << "error: blank frame grabbed\n";
                break;
            }

            bool ok = callback(frame,depthmap);

            t = (double)cv::getTickCount() -t ;
            fps_ = cv::getTickFrequency() / t;

            if(!ok) break;
            }
        }

        double FPS() const{
            return fps_;
        }

        std::string ExtraInfo() const{
            std::ostringstream info;
            info << "FPS: "<<fps_;
            return info.str();
        }

        void DrawInfo(const cv::Mat& im) const{
            using namespace std;
            int w = im.cols, h =im.rows;
            {
                ostringstream ss;
                ss << w << "x" << h;
                string text = ss.str();

                int baseline = 0;
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_PLAIN,1,1,&baseline);

                cv::putText(im,text,cv::Point(5,5 + textSize.height),cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(255,0,255));
            }

            {
                ostringstream ss;
                ss << "FPS: " << fps_;
                string text = ss.str();

                int baseline = 0;
                cv::Size textSize = cv::getTextSize(text,cv::FONT_HERSHEY_PLAIN,1,1,&baseline);

                cv::putText(im,text,cv::Point(w-5-textSize.width, 5+textSize.height),
                cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(255,0,255));
            }
        }

    

private:
    std::unique_ptr<VideoCapture> cap_;
#ifdef USE_OPENNI
    bool use_openni_;
#endif
    double fps_;
    
};

#endif 
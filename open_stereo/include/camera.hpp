#include<opencv2/opencv.hpp>

class Camera{
    public:
        using VideoCapture = cv::VideoCapture;
        using FrameCallback = std::function<bool(const cv::Mat&,const cv::Mat&)>;

        Camera(int index=0): cap_(new VideoCapture(std::move(index))),
#ifdef USE_OPENNI
            use_openni_(index == cv::CAP_OPENNI || index == cv::CAP_OPENNI2),
#endif
    
}
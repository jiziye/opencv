#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void colorReduce01(Mat& inputImage, Mat& outputImage,int div) {
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols * outputImage.channels();

    for (int i = 0; i < rowNumber; i++) {
        uchar *data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; j++) {
            data[j] = data[j] / div * div + div / 2;
        }
    }
}


void colorReduce02(Mat& inputImage,Mat& outputImage, int div) {
    outputImage = inputImage.clone();
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();

    for (; it != itend; ++it) {
        (*it)[0] = (*it)[0] / div * div + div / 2;
        (*it)[1] = (*it)[1] / div * div + div / 2;
        (*it)[2] = (*it)[2] / div * div + div / 2;
    }
}


void colorReduce03(Mat& inputImage,Mat& outputImage,int div)
{
    outputImage=inputImage.clone();
    int rowNumber=outputImage.rows;
    int colNumber=outputImage.cols;

    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<colNumber;j++)
        {
            outputImage.at<Vec3b>(i,j)[0]=outputImage.at<Vec3b>(i,j)[0]/div*div+div/2;
            outputImage.at<Vec3b>(i,j)[1]=outputImage.at<Vec3b>(i,j)[1]/div*div+div/2;
            outputImage.at<Vec3b>(i,j)[2]=outputImage.at<Vec3b>(i,j)[2]/div*div+div/2;

        }
}
int main() {
    Mat srcImage = imread("src.png", cv::IMREAD_GRAYSCALE);
//    cv::Mat srcImage(5, 2, CV_8UC3);
//    for(int i=0; i<srcImage.rows; i++) {
//        for(int j=0; j<srcImage.cols; j++) {
//            for(int k=0; k<3; k++) {
//                srcImage.at<cv::Vec3b>(i, j)[k] = (i + j) * 10 + k;
//            }
//        }
//    }
   // cout<<format(srcImage,"numpy")<<endl;

//    cout<<"channels: "<<srcImage.channels()<<endl;
//    for(int i=0;i<srcImage.rows;i++)
//    {
//        uchar* address=srcImage.ptr<uchar>(i);
//        cout<<i<<" address: "<<(long)address<<endl;
//    }

//    cout<<(long)&srcImage.at<uchar>(0,0) << ", " << (long)&srcImage.at<uchar>(0,1) <<std::endl;
//    cout<<(long)srcImage.ptr<uchar>(0)<<endl;

    imshow("src", srcImage);

    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

    double time0 = static_cast<double>(getTickCount()); //begin

    colorReduce01(srcImage, dstImage, 4);
    cout<<format(dstImage,"numpy")<<endl;

    colorReduce02(srcImage, dstImage, 4);
    cout<<format(dstImage,"numpy")<<endl;

    time0 = ((double) getTickCount() - time0) / getTickFrequency();
    cout << "run time: " << time0 << "s" << endl;

//    imshow("result", dstImage);
    waitKey(0);

    return 0;
}


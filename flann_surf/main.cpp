#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/nonfree/nonfree.hpp>
//#include<opencv2/features2d/features2d.hpp>

using namespace cv;

int main()
{
    Mat trainImage=imread("1.jpg");
    Mat trainImage_gray;
    cvtColor(trainImage,trainImage_gray,COLOR_BGR2GRAY);

    vector<KeyPoint> train_keypoint;    
    SurfFeatureDetector detector(80);
    detector.detect(trainImage_gray,train_keypoint);
    SurfDescriptorExtractor extractor;
    Mat descriptor;
    extractor.compute(trainImage_gray,train_keypoint,descriptor);

    FlannBasedMatcher matcher;
    vector<Mat> train_desc_collection(1,descriptor);
    matcher.add(train_desc_collection);
    matcher.train();

    VideoCapture cap(0);
    unsigned int framecount=0;

    while(char(waitKey())!='q')
    {
        int64 time0=getTickCount();
        Mat testIMage,testIMage_gray;
        cap>>testIMage;
        if(testIMage.empty())
        continue;

        cvtColor(trainImage,trainImage_gray,COLOR_BGR2GRAY);
        vector<KeyPoint> test_keypoint;
        Mat testDescriptor;
        detector.detect(testIMage_gray,test_keypoint);
        extractor.compute(testIMage_gray,test_keypoint,testDescriptor);

        vector<vector<DMatch>> matches;
        matcher.knnMatch(testDescriptor,matches,2);

        std::cout<<matches.size()<<std::endl;
        vector<DMatch> goodMathches;
        for(unsigned int i=0;i<matches.size();i++)
        {
            if(matches[i][0].distance<0.6*matches[i][1].distance)
            goodMathches.push_back(matches[i][0]);

        }

        Mat dstImage;
        drawMatches(testIMage,test_keypoint,trainImage,train_keypoint,goodMathches,dstImage);
        imshow("matches window",dstImage);

        std::cout<<"now fps: "<<getTickFrequency()/(getTickCount()-time0)<<std::endl;
        
    }

    return 0;
}
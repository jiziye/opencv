#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/nonfree.hpp>
///#include<opencv2/features2d/features2d.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat src=imread("1.jpg"),src_gray;
    cvtColor(src,src_gray,COLOR_BGR2GRAY);
    imshow("src",src);
    imshow("src_gray",src_gray);

    //ORB feature detector
    OrbFeatureDetector detector;
    vector<KeyPoint> keypoints;
    detector.detect(src_gray,keypoints);

    //ORB extractor descriptor
    OrbDescriptorExtractor extractor;
    Mat descriptors;
    extractor.compute(src_gray,keypoints,descriptors);

    flann::Index flannindex(descriptors,flann::LshIndexParams(12,20,2),cvflann::FLANN_DIST_HAMMING);

    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,360);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,900);
    
    unsigned int framecount = 0;


    while(char(waitKey(1)) != 'q')
    {  
        double time0 = static_cast<double>(getTickCount());
        //int64 time0 = getTickCount();
        Mat capimage,capimage_gray;
        cap >> capimage;
        if(capimage.empty()) continue;

        cvtColor(capimage,capimage_gray,COLOR_BGR2GRAY);
        vector<KeyPoint> cap_keypoints;
        detector.detect(capimage_gray,cap_keypoints);

        Mat cap_descriptors;
        extractor.compute(capimage_gray,keypoints,cap_descriptors);       

        Mat mathchIndex(cap_descriptors.rows,2,CV_32SC1);
        Mat matchDistance(cap_descriptors.rows,2,CV_32FC1);

        flannindex.knnSearch(cap_descriptors,mathchIndex,matchDistance,2,flann::SearchParams());

        vector<DMatch> goodmatches;
        for(int i=0; i < matchDistance.rows; i++)
        {
            if(matchDistance.at<float>(i,0) < 0.6 * matchDistance.at<float>(i,1))
            {
                DMatch dmathces(i,mathchIndex.at<int>(i,0),matchDistance.at<float>(i,0));
                goodmatches.push_back(dmathces);
            }
        }

        Mat resultimage;
        drawMatches(capimage,cap_keypoints,src,keypoints,goodmatches,resultimage);
        imshow("matches",resultimage);

        cout<<" fps: "<<getTickFrequency()/(getTickCount()-time0);
        

    }


}
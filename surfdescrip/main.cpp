#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/legacy/legacy.hpp>


using namespace cv;
using namespace std;

int main()
{
    Mat src1=imread("opencv_1.jpg",1);
    Mat src2=imread("opencv_2.jpg",1);
    if(!src1.data || !src2.data)
    {printf("read image error. \n");return false;}

    int minHessian=8000;
    SurfFeatureDetector detector(minHessian);
    vector<KeyPoint> keyPoint1,keyPoint2;

    detector.detect(src1,keyPoint1);
    detector.detect(src2,keyPoint2);

    SurfDescriptorExtractor extractor;
    Mat descriptors1,descriptors2;
    extractor.compute(src1,keyPoint1,descriptors1);
    extractor.compute(src2,keyPoint2,descriptors2);
    cout<<descriptors2.cols<<" "<<descriptors2.rows<<endl;
    
    BruteForceMatcher<L2<float>> matcher;
    vector<DMatch> matches;
    matcher.match(descriptors1,descriptors2,matches);

    Mat imgMatches;
    drawMatches(src1,keyPoint1,src2,keyPoint2,matches,imgMatches);
    imshow("match result",imgMatches);

    waitKey();
    return 0;

}

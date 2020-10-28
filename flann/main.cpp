#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/legacy/legacy.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/features2d/features2d.hpp>

#include<iostream>

using namespace cv;
using namespace std;

int main(int argc,char** argv)
{
    Mat img1=imread("1.jpg",1);
    Mat img2=imread("2.jpg",1);

    if(!img1.data || !img2.data)
    {
        printf("read image error. \n");
        return false;
    }

    int minHessian=400;
    SURF  detector(minHessian);
    vector<KeyPoint> keypoint1,keypoint2;

    detector.detect(img1,keypoint1);
    detector.detect(img2,keypoint2);

    drawKeypoints(img1,keypoint1,img1,Scalar::all(-1));
    drawKeypoints(img2,keypoint2,img2,Scalar::all(-1));

    imshow("keypoint1",img1);
    imshow("keypoint2",img2);


    SURF extractor;
    Mat descriptors1,descriptors2;
    extractor.compute(img1,keypoint1,descriptors1);
    extractor.compute(img2,keypoint2,descriptors2);
    cout<<"********descriptors1***********"<<endl<<descriptors1<<endl;
    cout<<"descriptors1.type "<<descriptors1.type()<<endl;


    FlannBasedMatcher matcher;
    vector<DMatch> matches;
    matcher.match(descriptors1,descriptors2,matches,Mat());

    double max_dist=0;
    double min_dist=100;

    for(int i=0;i<descriptors1.rows;i++)
    {
        double dist=matches[i].distance;
        if(dist<min_dist) min_dist=dist;
        if(dist>max_dist) max_dist=dist;

    }   

    printf(">max distance: %f. \n",max_dist);
    printf("<min distance: %f. \n ",min_dist);

    vector<DMatch> good_matches;
    for(int i=0;i<descriptors1.rows;i++)
    {
        if(matches[i].distance<2*min_dist)
        {good_matches.push_back(matches[i]);}
    }

    Mat img_matches;
    drawMatches(img1,keypoint1,img2,keypoint2,good_matches,img_matches,Scalar::all(-1),Scalar::all(-1),vector<char>(),2);

    for(int i=0;i<good_matches.size();i++)
    {
        printf(">good matches [%d] feature points1: %d -- feature points2: %d. \n",i,good_matches[i].queryIdx,good_matches[i].trainIdx);

    }

    imshow("feature point match",img_matches);
    waitKey();
    return 0;

    
}
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

int main()
{
    
    Mat src1=imread("1.jpg",1);
    Mat src2=imread("2.jpg",2);
    if(!src1.data || !src2.data)
    {
        std::printf("READ IMAGE ERROR. \n");
        return -1;
    }

//surf feature detect
    int minHessian = 800;
    SurfFeatureDetector detector(minHessian);
    vector<KeyPoint> KeyPoint_object,KeyPoint_scene;
    detector.detect(src1,KeyPoint_object);
    detector.detect(src2,KeyPoint_scene);

//extractor descriptor
    SurfDescriptorExtractor extractor;
    Mat descriptors_object,descriptors_scene;
    extractor.compute(src1,KeyPoint_object,descriptors_object);
    extractor.compute(src2,KeyPoint_scene,descriptors_scene);
    cout<<"descriptors_object rows: "<<descriptors_object.rows<<endl;
    cout<<"descriptors_object cols: "<<descriptors_object.cols<<endl;

    
//flann matcher
    FlannBasedMatcher matcher;
    vector<DMatch> matches;
    matcher.match(descriptors_object,descriptors_scene,matches);

    double max_dist=0;double min_dist=100;
    for(int i = 0; i<descriptors_object.rows;i++)
    {   
        double dist=matches[i].distance;
        if(dist<min_dist) min_dist=dist;
        if(dist>max_dist) max_dist=dist;
    }

    printf("min dist: %f . \n",min_dist);
    printf("max dist: %f .\n",max_dist);

    vector<DMatch> good_matches;
    for(int i=0;i<descriptors_object.rows; i++)
    {
        if(matches[i].distance < 2*min_dist) 
        {
            good_matches.push_back(matches[i]);
        }
    }

    Mat dst_matches;
    
    drawMatches(src1,KeyPoint_object,src2,KeyPoint_scene,good_matches,dst_matches,Scalar::all(-1));

    vector<Point2f> obj;
    vector<Point2f> scene;

    for(int i = 0; i<good_matches.size(); i++)
    {
        obj.push_back(KeyPoint_object[good_matches[i].queryIdx].pt);
        scene.push_back(KeyPoint_scene[good_matches[i].trainIdx].pt);
    }   

    //caculate homography
    Mat H = findHomography(obj,scene,RANSAC);

    vector<Point2f> obj_corners(4),scene_corners(4);
    
    obj_corners[0] = cvPoint(0,0);
    //obj_corners[1]=Point2i(0,0);
    obj_corners[1] = cvPoint(src1.cols,0);
    obj_corners[2] = cvPoint(src1.cols,src1.rows);
    obj_corners[3] = cvPoint(0,src1.rows);

    perspectiveTransform(obj_corners,scene_corners,H);

    line(dst_matches,scene_corners[0]+Point2f(static_cast<float>(src1.cols),0),scene_corners[1]+Point2f(static_cast<float>(src2.cols),0),Scalar(255,0,123),4);
    line(dst_matches,scene_corners[1]+Point2f(static_cast<float>(src1.cols),0),scene_corners[2]+Point2f(static_cast<float>(src1.cols),0),Scalar(255,0,123),4);
    line(dst_matches,scene_corners[2]+Point2f(static_cast<float>(src1.cols),0),scene_corners[3]+Point2f(static_cast<float>(src2.cols),0),Scalar(255,0,123),4);
    line(dst_matches,scene_corners[3]+Point2f(static_cast<float>(src1.cols),0),scene_corners[0]+Point2f(static_cast<float>(src2.cols),0),Scalar(255,0,123),4);

    imshow("good matches & object detection",dst_matches);

    waitKey();
    return 0;
}
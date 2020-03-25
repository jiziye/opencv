#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>


using namespace cv;
using namespace std;

Mat src,gray;
int maxCornerNumber=33;
int MaxtrackbarNumber=500;
void on_GoodFeaturesToTrack(int,void *);
RNG &rng=theRNG();

int main()
{
    src=imread("desk.jpg",1);
    cvtColor(src,gray,CV_BGR2GRAY);

    imshow("result",src);
    createTrackbar("maxcorners: ","result",&maxCornerNumber,MaxtrackbarNumber,on_GoodFeaturesToTrack);
    on_GoodFeaturesToTrack(0,0);

    waitKey();
    return 0;


}

void on_GoodFeaturesToTrack(int,void *)
{
    if(maxCornerNumber<=1){maxCornerNumber=1;}

    vector<Point2f> corners;
    double qualityLevel=0.01;
    double minDistance=5;
    int blockSize=3;
    double k=0.04;

    goodFeaturesToTrack(gray,corners,maxCornerNumber,qualityLevel,minDistance,Mat(),blockSize,false,k);  

    cout<<"corners numbers: "<<corners.size()<<endl;

    int r=4;
    for(unsigned int i=0;i<corners.size();i++)
    {
        circle(src,corners[i],r,Scalar(0,0,255));
        cout<<corners[i]<<endl;
    }
    imshow("result",src);

    Size winSize=Size(5,5);
    Size zeroZone=Size(-1,-1);

    TermCriteria criteria=TermCriteria(TermCriteria::EPS+TermCriteria::MAX_ITER,40,0.001);

    cornerSubPix(gray,corners,winSize,zeroZone,criteria);

    for(int i=0;i<corners.size();i++)
    {
        cout<<"corner point: "<<corners[i].x<<","<<corners[i].y<<endl;
    
    }


}









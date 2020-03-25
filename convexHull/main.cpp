#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image(600,600,CV_8UC3);
    RNG& rng=theRNG();
    //std::cout<<rng;
    
        cout<<"unsigned rng= "<<(unsigned)rng<<endl;

//        cout<<"unsigned int rng= "<<(unsigned int)rng<<endl;

while(1)
    {
	char key;
        int count=(unsigned)rng%100+3;
//	cout<<"unsigned int rng%100=  "<<(unsigned int)rng%100<<endl;
        cout<<"count=unsigned  rng%100=  "<<count<<endl;
 
        vector<Point> points;

        for(int i=0;i<count;i++)
        {
	    Point point;
            point.x=rng.uniform(image.cols/4,image.cols*3/4);
            point.y=rng.uniform(image.rows/4,image.rows*3/4);
	    cout<<i<<" "<<point<<endl;

            points.push_back(point);
//          cout<<"points= "<<points<<endl;         
        }

            
//	    cout<<"points= "<<points<<endl;
            cout<<"points count= "<<points.size()<<endl;

 	    vector<int> hull;
            convexHull(points,hull,true);
           // cout<<"**********************************"<<endl<<image<<endl;

           // image=Scalar::all(0);
           image=Mat::zeros(image.size(),CV_8UC3);
           //  cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<image<<endl;
            for(int i=0;i<count;i++)
            {
               // circle(image,points[i],13,Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),1,8,0);
               circle(image,points[i],13,Scalar(0,0,255));
            }

            int hullcount=(int)hull.size();
         
 	    cout<<"hullcount= "<<hullcount<<endl<<"hull[]= "<<hull[hullcount-1]<<endl;
            Point point0=points[hull[hullcount-1]];
 
            for(int i=0;i<hullcount;i++)
            {
             Point point=points[hull[i]];
            cout<<"hull["<<i<<"]= "<<hull[i]<<endl; 
            line(image,point0,point,Scalar(255,255,255),2);
             point0=point;
            }

           imshow("result",image);
 
           key=(char)waitKey();
           if(key==27 || key=='q' || key== 'Q')
           break;
  }

           return 0;
}



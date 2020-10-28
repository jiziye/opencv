#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

bool MultiChannelBlending();
void ShowHelpText();


int main() {
    system("color 9F");

    if(MultiChannelBlending())
    {
        cout<<endl<<"succeed";
    }
    waitKey(0);
    return 0;
}


bool MultiChannelBlending()
{
    Mat srcImage;
    Mat logoImage;
    vector<Mat> channels;

    Mat imageBlueChannels;

    logoImage=imread("game.png",0);
    cout<<"logoImage rows,cols: "<<logoImage.rows<<","<<logoImage.cols<<endl;
    imshow("logo",logoImage);

    srcImage=imread("ubuntu.png");
    cout<<"srcimage rows,cols: "<<srcImage.rows<<","<<srcImage.cols<<endl;
    imshow("src",srcImage);

    if(!logoImage.data){printf("read logoimage error \n"); return false;}
    if(!srcImage.data){printf("read srcimage error ]n"); return false;}

    split(srcImage,channels);

    imageBlueChannels=channels.at(0);
    addWeighted(imageBlueChannels(Rect(50,25,logoImage.cols,logoImage.rows)),1.0,
                 logoImage,0.5,0.,imageBlueChannels(Rect(50,25,logoImage.cols,logoImage.rows)));

    merge(channels,srcImage);

    namedWindow("BLUE CHANNELS");
    imshow("BLUE CHANNELS",srcImage);

   //greenchannels

    Mat imageGreenChannels;

    logoImage=imread("game.png",0);
    srcImage=imread("ubuntu.png");

    if(!logoImage.data){printf("read logoimage error \n"); return false;}
    if(!srcImage.data){printf("read srcimage error ]n"); return false;}

    split(srcImage,channels);

    imageBlueChannels=channels.at(1);
    addWeighted(imageGreenChannels(Rect(50,25,logoImage.cols,logoImage.rows)),1.0,
                logoImage,0.5,0.,imageGreenChannels(Rect(50,25,logoImage.cols,logoImage.rows)));

    merge(channels,srcImage);

    namedWindow("GREEN CHANNELS");
    imshow("GREEN CHANNELS",srcImage);


    return true;
}
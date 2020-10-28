#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
    char ad[128] = {0};
    int filename = 0, filenum = 0;
    Mat src = imread("digits_opencv/digits.png");
    Mat gray;
    cvtColor(src, gray, CV_BGR2GRAY);

    //单个图片是20x20, 把原图划分成成单个图片
    int b = 20;
    int rowsnum = gray.rows / b;
    int colsnum = gray.cols / b;
    for (int i = 0; i < rowsnum; i++)
    {
        int offsetRow = i * b;
        //5行一组数字
        if (i % 5 == 0 && i != 0)
        {
            filename++;
            filenum = 0;
        }
        for (int j = 0; j < colsnum; j++)
        {
            int offsetCol = j * b;
            // stringstream s;
            // s << "/home/jiziye/git_project/opencv-demo/watermeter_rec/" << filename <<"/"<< filenum++;
            // sprintf(ad, "s.str()");

            sprintf(ad, "%d/%d.jpg", filename, filenum++);
            ofstream ofs(ad);
            ofs.close();

            cout << ad;
            Mat tmp;
            gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);
            //imwrite(ad, tmp);
            // imwrite("/home/jiziye/git_project/opencv-demo/watermeter_rec/digits_opencv/0/test0.jpg", tmp);
            imshow("single_num", tmp);
            //waitKey(0);
        }
    }

    string file_name = filename;
    string file_num = string(filenum);

    const char *dir_name = "/home/jiziye/git_project/opencv-demo/watermeter_rec/";
    Mat img = imread(dir_name + name);
    imshow("img", img);

    waitKey(0);

    return 0;
}
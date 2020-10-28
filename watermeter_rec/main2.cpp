#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

//#include<tesseract/
using namespace std;
using namespace cv;
using namespace cv::ml;

int predict(Mat &img);

int main()
{
        //读图
        Mat src = imread("test5.jpeg");
        if (src.empty())
                cerr << " read image error" << endl;
        imshow("src", src);

        //图像处理
        Mat gray;
        cvtColor(src, gray, COLOR_RGB2GRAY); //转灰度
        imshow("gray", gray);

        //二值化 canny or  threshold
        Mat thre_1;
        adaptiveThreshold(gray, thre_1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 5, 15);
        //threshold(gray,  thre_1, 150, 255, CV_THRESH_BINARY_INV);//白底黑字=>黑底白字
        //Canny(gray,thre_1,30,180);

        //threshold(gray, thre_1, 100, 255, THRESH_BINARY);
        //  imshow("thre_1", thre_1);

        //霍夫线变换
        // Mat hough = Mat::zeros(thre_1.size(), CV_8UC3);
        // vector<Vec4i> lines;
        // HoughLinesP(thre_1, lines, 1, CV_PI/180, 30,20, 10);
        // //绘制线段
        // for(size_t i = 0; i<lines.size(); i++)
        // {
        //         Vec4i l =lines[i];
        //         line(hough, Point(l[0], l[1]), Point(l[2],l[3]), Scalar(0, 0, 255), 1, LINE_AA);
        // }
        // imshow("hough", hough);

        //膨胀
        Mat element = getStructuringElement(MORPH_RECT, Size(11, 11));
        Mat dil;
        dilate(thre_1, dil, element);
        //imshow("dilate", dil);

        //开运算
        // Mat element1 = getStructuringElement(MORPH_ELLIPSE,Size(4,4));
        // Mat morph;
        // morphologyEx(thre_1, morph, MORPH_RECT, element1);
        // imshow("morph", morph);

        //  整个数字框的轮廓
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        Mat cont = Mat::zeros(dil.size(), CV_8UC3); //格式要8UC3
        //CV_RETR_EXTERAL寻找外部轮廓 ; CV_RETR_LIST是检测所有的轮廓，并且不建立包含被包含的关系
        //CHAIN_APPROX_SIMPLE保存模式：仅保存边缘的拐点，如三角形保存3个顶点的坐标。
        //返回轮廓的点集，hierarchy向量内每一个元素的4个int型变量，分别表示每个轮廓的后一个轮廓，前一个轮廓，父轮廓，内嵌轮廓的索引编号
        //contourArea可以得到当前轮廓所包含区域的大小，方便轮廓的筛选
        findContours(dil, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE); //输入需要是二值化图像
        // for (int i = 0; i < contours.size(); i++)
        // {
        //         if (contourArea(contours[i]) < 500)
        //                 continue;
        //         //contours[i]. clear();
        //         // drawContours(cont,contours,-1,255);
        // }
        drawContours(cont, contours, -1, 255);
        //         int  count1 = 0;
        //        for(size_t i = 0; i < contours.size(); i++)
        //        {
        //                 count1 += 1;
        //                 Scalar color = Scalar(0, 0, 255);
        //                 drawContours(cont, contours, (int)i, color, 1, LINE_AA, hierarchy, 0);
        //        }
        //         cout << "count1 is " << count1 << endl;
        imshow("contours", cont);

        //对轮廓进行排序

        // 轮廓外界矩形 找到数字表盘部分矩阵 提取出对应图像
        //Mat cont_rect = Mat::zeros(dil.size(), CV_8UC3); //格式要8UC3
        vector<Rect> rect;
        Mat dst_thre, dst_origin, dst_gray;
        for (int i = 0; i < contours.size(); i++)
        {
                if (contourArea(contours[i]) > 5000)
                {
                        Rect temp = boundingRect(contours[i]);
                        if (temp.width > 200 && temp.width < 300)
                        {
                                rect.push_back(temp);
                                rectangle(cont, temp, Scalar(0, 0, 255)); //绘制轮廓
                                dst_thre = thre_1(temp);
                                dst_origin = src(temp);
                                dst_gray = gray(temp);
                        }
                        // cout << predict(dst);
                }
        }
        imshow("cont_rec", cont);
        imshow("dst_gray", dst_gray);
        imshow("dst_origin", dst_origin);
        imshow("dst_thre.jpg", dst_thre);
        
        imwrite("dst_thre.jpg", dst_thre); // 保存下来的数字矩形，尝试用tessarct识别
        imwrite("dst_origin.jpg", dst_origin);

        //调用tesseract识别
        tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
        if (api->Init(NULL, "eng"))
        {
                printf("init error");
                exit(1);
        }

        Pix *image = pixRead("dst_thre.jpg");
        api->SetImage(image);
        char *result;
        result = api->GetUTF8Text();
        printf("output: \n %s", result);

        //对数字矩形灰度图再做二值化处理后给tessarct识别，效果差

        // adaptiveThreshold(dst_gray, dst_gray, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 15);
        // imshow("test", dst_gray);

        //resize(dst,dst,Size(640, 480));
        //  floodFill(dst, Point(0,0), Scalar(0,0,0)); 暂无效果
        Mat element_1 = getStructuringElement(MORPH_RECT, Size(1, 1));
        //erode(dst,dst,element_1);
        // morphologyEx(dst, dst,MORPH_OPEN,  element_1);
        // imshow("dst_1", dst);

        //找单个数字轮廓和外接矩形框
        Mat cont_single = Mat::zeros(dst_thre.size(), CV_8UC3);
        vector<vector<Point>> contours1;
        vector<Vec4i> hierarchy1;
        findContours(dst_thre, contours1, hierarchy1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        drawContours(cont_single, contours1, -1, 255);
        imshow("cont_single", cont_single);

        vector<Rect> rec_vect;
        Mat single_number;
        for (int i = 0; i < contours1.size(); i++)
        {
                Rect temp = boundingRect(contours1[i]);
                if (temp.width > 20 && temp.height > 10)
                {
                        rectangle(cont_single, temp, Scalar(0, 0, 255));
                        imshow("cont_single_rect", cont_single);
                        rec_vect.push_back(temp);
                        single_number = dst_gray(temp);
                        static int count = 0;
                        stringstream ss;
                        ss << (count++) << ".jpg";
                        string filename = ss.str();
                        threshold(single_number, single_number, 100, 255, CV_THRESH_BINARY);
                        //resize(single_number, single_number, Size(60,100));放大图像没有用
                        imshow(filename, single_number);
                        imwrite(filename, single_number);
                }
        }
        //boundingRect(contours1);

        waitKey(0);
        return 0;
}

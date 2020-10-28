#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>

using namespace std;
using namespace cv;

//需要定义一个类，用来存放轮廓的外接矩阵以及方便后续的排序
class myRect
{
public:
	myRect(){}
	~myRect(){}
	myRect(Rect &temp):myRc(temp){}
	//比较矩形左上角的横坐标，以便排序
	bool operator<(myRect &rect)
	{
		if (this->myRc.x < rect.myRc.x)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//重载赋值运算符
	myRect operator=(myRect &rect)
	{
		this->myRc = rect.myRc;
		return *this;
	}
	//获取矩形
	Rect getRect()
	{
		return myRc;
	}
private:
	Rect myRc;//存放矩形
};

int main()
{
	Mat srcImage = imread("number.jpg");
	imshow("原图", srcImage);

	//对图像进行处理，转化为灰度图然后再转为二值图
	Mat grayImage;
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	Mat binImage;
	//第4个参数为CV_THRESH_BINARY_INV是因为我的输入原图为白底黑字
	//若为黑底白字则选择CV_THRESH_BINARY即可
	threshold(grayImage, binImage, 100, 255, CV_THRESH_BINARY_INV);

     //寻找轮廓，必须指定为寻找外部轮廓，不然一个数字可能有多个轮廓组成，比如4,6,8,9等数字
	Mat conImage = Mat::zeros(binImage.size(), binImage.type());
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//指定CV_RETR_EXTERNAL寻找数字的外轮廓
	findContours(binImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//绘制轮廓
	drawContours(conImage, contours, -1, 255);

    //可以将一个一个轮廓外接矩阵保存于该类中。而且类中重载了比较操作符，很容易对轮廓进行排序
    //将每个数字，分离开，保存到容器中
	vector<myRect> sort_rect;
	for (int i = 0; i < contours.size(); i++)
	{
		//boundingRect返回轮廓的外接矩阵
		Rect tempRect = boundingRect(contours[i]);
		sort_rect.push_back(tempRect);
	}

    //排序算法的话，采用比较简单的冒泡法
    //对矩形进行排序，因为轮廓的顺序不一定是数字真正的顺序
	for (int  i = 0; i < sort_rect.size(); i++)
	{
		for (int j = i + 1; j < sort_rect.size(); j++)
		{
			if (sort_rect[j] < sort_rect[i])
			{
				myRect temp = sort_rect[j];
				sort_rect[j] = sort_rect[i];
				sort_rect[i] = temp;
			}
		}
	}


        //sort_rect容器中的轮廓矩形是按我们输入的图片中的数字顺序存放的
       //进行数字匹配时，需要先加载模板进行比较。如果没有就要先新建一个。
       //新建模板需要输入的是0-9的数字模板，不用修改程序，只需要添加以下代码
               /*加载模板，若没有则需自己新建一个*/
 
	//新建,运行一次就好，不过制作模板的材料为0-9十个数字的图像
	for (int i = 0; i < 10; i++)
	{
		Mat ROI = conImage(sort_rect[i].getRect());
		Mat dstROI;
		resize(ROI, dstROI, Size(40, 50),0, 0, INTER_NEAREST);
		char name[64];
		sprintf(name, "C:/Users/Administrator/Desktop/number_recognition/number_recognition/image/%d.jpg", i);
		//imshow(str, dstROI);
		imwrite(name, dstROI);
	}

    //加载模板，也就是从文件中将各个模板图片读入，路径根据自己的情况修改
            //加载模板
	vector<Mat> myTemplate;
	for (int i = 0; i < 10; i++)
	{
		char name[64];
		sprintf(name, "C:/Users/Administrator/Desktop/number_recognition/number_recognition/image/%d.jpg", i);
		Mat temp = imread(name, 0);
		myTemplate.push_back(temp);
	}

    //按顺序取出和分割数字
	vector<Mat> myROI;
	for (int i = 0; i < sort_rect.size(); i++)
	{
		Mat ROI;
		ROI = conImage(sort_rect[i].getRect());
		Mat dstROI = Mat::zeros(myTemplate[0].size(),myTemplate[0].type());
		resize(ROI, dstROI, myTemplate[0].size(), 0, 0, INTER_NEAREST);
		myROI.push_back(dstROI);
	}

    //比较和匹配
    //求图片的像素和
    int getPiexSum(Mat &image)
    {
	int sum = 0;
	for (int i = 0; i < image.cols; i++)
	{
		for (int j = 0; j < image.rows; j++)
		{
			sum += image.at<uchar>(j, i);
		}
	}
	return sum;
    }

    //进行比较,将图片与模板相减，然后求全部像素和，和最小表示越相似，进而完成匹配
	vector<int> seq;   //顺序存放识别结果
	for (int i = 0; i < myROI.size(); i++)
	{
		Mat subImage;
		int sum = 0;
		int min = 100000;
		int min_seq = 0;//记录最小的和对应的数字
		for (int j = 0; j < 10; j++)
		{
			//计算两个图片的差值
			absdiff(myROI[i], myTemplate[j], subImage);
			sum = getPiexSum(subImage);
			if (sum < min)
			{
				min = sum;
				min_seq = j;
			}
			sum = 0;
		}
		seq.push_back(min_seq);
	}
 
	//输出结果
	cout << "识别结果为：";
	for (int i = 0; i < seq.size(); i++)
	{
		cout << seq[i];
	}
	cout << endl;
}
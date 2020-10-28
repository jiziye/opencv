#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;
using namespace cv::ml;

int dst_l(Mat &dst, int start);
int dst_r(Mat &dst, int start);
int dst_t(Mat &dst);
int dst_b(Mat &dst);
void train_pixel();
int predict(Mat &img);

int main(int argc,char** argv)
{
	
	string name1="a.png"; //预测的图片
	Mat img1 = imread(name1, 0); //读入图片
    if(!img1.data){cerr<< "read image error " << endl; }
	imshow("img1", img1);

	
	Mat dst, mid;
	resize(img1, img1, Size(1920, 1080)); //调整大小
	threshold(img1, mid, 100, 255, THRESH_BINARY); //二值化 可调参数 100    黑底白字
	imshow("二值化",mid);


	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	morphologyEx(mid, mid, MORPH_CLOSE, element); //闭运算 膨胀，去除部分黑字
	imshow("闭运算",mid);

	
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(mid, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE); //找轮廓
	
        int  count1 = 0; Mat cont = Mat::zeros(mid.size(), CV_8UC3);
       for(size_t i = 0; i < contours.size(); i++)
       {
                count1 += 1;
                Scalar color = Scalar(0, 0, 255);
                drawContours(cont, contours, (int)i, color, 1, LINE_AA, hierarchy, 0);
       }
        cout << "count1 is " << count1 << endl;
         imshow("contours", cont); 


	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(contours[i]); //轮廓矩形
		if (rect.size.width < rect.size.height)
		{
			float temp = rect.size.width;
			rect.size.width = rect.size.height;
			rect.size.height = temp;
			
		}
		//面积和比例满足要求
		if (rect.size.width / rect.size.height > 3 && rect.size.width / rect.size.height < 4 && rect.size.area() > 100000 && rect.size.area() < 140000)
		{
			dst = img1(Rect(rect.center.x - rect.size.width / 2, rect.center.y - rect.size.height / 2, rect.size.width, rect.size.height));
			break;
		}
	}
	imshow("dst", dst);

	

	threshold(dst, dst, 100, 255, THRESH_BINARY); //二值化 可调参数 100
	imshow("dst_1",dst);
	floodFill(dst, Point(0, 0), Scalar(0, 0, 0)); //漫水填充
	imshow("dst_2",dst);
	floodFill(dst, Point(0, dst.rows - 1), Scalar(0, 0, 0));
	imshow("dst_3",dst);
	floodFill(dst, Point(dst.cols - 1, 0), Scalar(0, 0, 0));
	floodFill(dst, Point(dst.cols - 1, dst.rows - 1), Scalar(0, 0, 0));
	element = getStructuringElement(MORPH_RECT, Size(5, 5)); //腐蚀
	erode(dst, dst, element);
	imshow("腐蚀",dst);

	
	int top = dst_t(dst); //上下边界
	int bot = dst_b(dst);
	int l1, r1, l2, r2, l3, r3, l4, r4, l5, r5; //5个数字的左右边界
	l1 = dst_l(dst, 0);
	r1 = dst_r(dst, l1 + 1);
	l2 = dst_l(dst, r1 + 1);
	r2 = dst_r(dst, l2 + 1);
	l3 = dst_l(dst, r2 + 1);
	r3 = dst_r(dst, l3 + 1);
	l4 = dst_l(dst, r3 + 1);
	r4 = dst_r(dst, l4 + 1);
	l5 = dst_l(dst, r4 + 1);
	r5 = dst_r(dst, l5 + 1);
	Mat a1, a2, a3, a4, a5; //5个数字的截取图
	a1 = dst(Range(top, bot), Range(l1, r1)); //截取轮廓
	a2 = dst(Range(top, bot), Range(l2, r2));
	a3 = dst(Range(top, bot), Range(l3, r3));
	a4 = dst(Range(top, bot), Range(l4, r4));
	a5 = dst(Range(top, bot), Range(l5, r5));
	imshow("a1", a1);
	
	//imwrite("label/" + to_string(count) + "_1.jpg", a1);
	//imwrite("label/" + to_string(count) + "_2.jpg", a2);
	//imwrite("label/" + to_string(count) + "_3.jpg", a3);
	//imwrite("label/" + to_string(count) + "_4.jpg", a4);
	//imwrite("label/" + to_string(count) + "_5.jpg", a5);
	ofstream out("out.txt", ios::app);
	// out << predict(a1) << " " << predict(a2) << " " << predict(a3) << " " << predict(a4) << " " << predict(a5) << "\n";
	// out.close();
	// cout << predict(a1) << " " << predict(a2) << " " << predict(a3) << " " << predict(a4) << " " << predict(a5) << "\n";


	waitKey();
	return 0;
}

int dst_t(Mat &dst)
{
	bool flag = true;
	int top;
	for (int i = 0; i < dst.rows; i++)
	{
		if (flag)
		{
			int num = 0;
			for (int j = 0; j < dst.cols; j++)
			{

				if (dst.at<uchar>(i, j) != 0) {
					num++;
					if (num > 20)
					{
						top = i;
						flag = false;
						break;
					}
				}
			}
		}
		else {
			flag = true;
			break;
		}
	}
	return top;
}

int dst_b(Mat &dst)
{
	bool flag = true;
	int bot;
	for (int i = dst.rows - 1; i >= 0; i--)
	{
		if (flag)
		{
			int num = 0;
			for (int j = 0; j < dst.cols; j++)
			{

				if (dst.at<uchar>(i, j) != 0) {
					num++;
					if (num > 20)
					{
						bot = i;
						flag = false;
						break;
					}
				}
			}
		}
		else {
			flag = true;
			break;
		}
	}
	return bot;
}

int dst_l(Mat &dst,int start)
{
	int l;
	bool flag = true;
	for (int j = start; j < dst.cols; j++)
	{
		if (flag)
		{
			for (int i = 0; i < dst.rows; i++)
			{
				if (dst.at<uchar>(i, j) != 0)
				{
					l = j;
					flag = false;
					break;
				}
			}
		}
		else
		{
			flag = true;
			break;
		}
	}
	return l;
}

int dst_r(Mat &dst, int start)
{
	int r;
	bool flag = true;
	for (int j = start; j < dst.cols; j++)
	{
		if (flag)
		{
			int num = 0;
			for (int i = 0; i < dst.rows; i++)
			{
				if (dst.at<uchar>(i, j) != 0)
				{
					num++;
					break;
				}
			}
			if (num == 0)
			{
				r = j;
				flag = false;
			}
		}
		else
		{
			flag = true;
			break;
		}
	}
	return r;
}

void train_pixel()
{
	Mat NumData, NumLabels;
	ifstream file("name.txt", ios::in);
	string name;
	int i = 0, trainNum=60;
	while (getline(file, name)) {
		string n;
		istringstream ss(name);
		ss>>n;
		Mat tmp,img = imread(n,0);
		resize(img, tmp, Size(50, 70));
		NumData.push_back(tmp.reshape(0, 1));  //序列化后放入特征矩阵
		NumLabels.push_back(i / trainNum);  //对应的标注
		i++;
	}
	file.close();
	NumData.convertTo(NumData, CV_32F); //uchar型转换为cv_32f
	Ptr<TrainData> tData = TrainData::create(NumData, ROW_SAMPLE, NumLabels);
	Ptr<KNearest> NumModel = KNearest::create();
	NumModel->setDefaultK(10);
	NumModel->setIsClassifier(true);
	NumModel->train(tData);
	NumModel->save("./num_knn_pixel.yml");
}

int predict(Mat &img)
{
	Ptr<KNearest> model_pixel = Algorithm::load<KNearest>("num_knn_pixel.yml");
	resize(img, img, Size(50, 70));
	Mat test;
	test.push_back(img.reshape(0, 1));
	test.convertTo(test, CV_32F);
	int result = model_pixel->predict(test);
	return result;
}
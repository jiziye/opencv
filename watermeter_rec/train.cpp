#include <iostream>
#include <sys/io.h>

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
using namespace ml;

ostringstream oss;


int num = -1;
Mat gray;
Mat thre;
Mat dealimage;

int main()
{
    //获取一张图片后将图片写特征写入容器，将标签写入另一个容器，保证特征和标签一一对应。

    const int classnum = 10;
    const int imagesSum = 500;
    
    Mat trainingData;//训练的数据，一行一个训练图片
    Mat labels;//训练的标签

    Mat traindata; //最终的训练数据
    Mat clas; //最终的训练样本标签

    //从指定文件夹下提取图片
    for(int i = 0; i < classnum; i++)
    {
        oss << "/home/jiziye/git_project/opencv-demo/watermeter_rec/";
        num +=1 ; //num从0 到9 10个文件夹
        int label = num;
        oss << num <<"/*.jpg" ;
        string pattern = oss.str();//路径赋给pattern
        cout << pattern << endl;

        oss.str("");//清空oss
        
        vector<Mat> input_images;
        vector<String> input_images_name;

        //input_images_name:存放符合模式的图片地址
        glob(pattern, input_images_name, false); //glob()函数返回一个包含匹配指定模式的文件名或目录的数组

        int all_num = input_images_name.size();

        for( int i = 0; i < imagesSum; i++) 
        {
            //读取每一个图片，灰度二值化后放在vector<Mat> input_images里
            cvtColor(imread(input_images_name[i]), gray, COLOR_BGR2GRAY);
            threshold(gray, thre, 0, 255, THRESH_OTSU);
            input_images.push_back(thre);
            dealimage = input_images[i];
            dealimage = dealimage.reshape(1, 1);//图片序列化：将原图像对应的矩阵拉伸成一个一行的向量，作为特征向量
           

            trainingData.push_back(dealimage);//将序列化后的图片依次存入
            labels.push_back(label);//label就是数字0123456789
        }
        
    }

    //转变
    Mat(trainingData).copyTo(traindata);
    traindata.convertTo(traindata,CV_32FC1);

    Mat(labels).copyTo(clas);

 
	//===============================创建SVM模型===============================

    //创建SVM模型
    Ptr<SVM> SVM_params = SVM::create();
    SVM_params->setType(SVM::C_SVC); //C_SVC用于分类
    SVM_params->setKernel(SVM::LINEAR);//linear线性核函数

    SVM_params->setDegree(0); //核函数中的参数degree
    SVM_params->setGamma(1);//核函数中的参数gamma
    SVM_params->setCoef0(0);//核函数中的参数
    SVM_params->setC(1);//SVM最优问题参数
    SVM_params->setNu(0);//SVM最优问题参数
    SVM_params ->setP(0);//SVM最优问题参数

    //结束条件
    SVM_params->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 1000, 0.01));
    Ptr<TrainData> tData = TrainData::create(traindata, ROW_SAMPLE, clas);

    //开始训练
    SVM_params->train(tData);

    //保存模型
    cout << "训练好了！ " << endl;


//===============================预测部分===============================
    //读图，灰度二值化
    Mat src = imread("test.jpg");
    cvtColor(src, src, COLOR_BGR2GRAY);
    threshold(src, src, 0, 255, CV_THRESH_OTSU);
    imshow("原图像", src);
    //序列化
    Mat input;
    src = src.reshape(1, 1);
    input.push_back(src);
    input.convertTo(input, CV_32FC1);

    float r = SVM_params->predict(input);
    cout << r << endl;
    waitKey(0);
    return 0;


    //预测部分


}
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
        Mat src = imread("1.png");
      
        Mat distortion = src.clone();
        Mat camera_matrix;
        Mat distortion_coefficients;
        imshow("src",src);
        FileStorage file_storage("./../camera.yaml", FileStorage::READ);
        if(!file_storage.isOpened())
        {
            cerr << "open yaml failed."<< endl;
        }
        file_storage["camera_matrix"] >> camera_matrix;
        file_storage["distortion_coefficients"] >> distortion_coefficients;
        file_storage.release();
        
        cout << camera_matrix << endl;
        cout << distortion_coefficients << endl;
        
        undistort(src, distortion, camera_matrix, distortion_coefficients);
        
        imshow("undistort",distortion);
        waitKey(0);
        
        return 0;
}
need camera.yaml to undistort the image;
use calibration to generate camera.yaml;


use correct path:
Mat src = imread("./../test1.png");
FileStorage file_storage("./../camera1.yaml", FileStorage::READ);
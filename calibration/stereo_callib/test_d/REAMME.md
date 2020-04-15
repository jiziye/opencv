如果 OpenCV 安装到了自定义目录或想指定某一版本，编译前可如下设置路径：

# OpenCV_DIR is the directory where your OpenCVConfig.cmake exists
export OpenCV_DIR=~/opencv

then cmake .. 
make  


cannot find #include "opencv2/imgcodecs.hpp"
C/C++ configurations:
include path: /usr/local/include
opencv make install => /usr/local/include
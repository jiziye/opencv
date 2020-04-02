1.use open_mynteye shoot some carlibration target pictures
2.move this picutures to calibration/imagelist_creator_build
3.make and use imagelist_creator to generate imagelist.yaml 
$ ./imagelist_creator imagelist.yaml 1.png 2.png 3.png 4.png 5.png 6.png 7.png 8.png 9.png 10.png 11.png 12.png 13.png 14.png 15.png 
4.move imagelist.yaml and calibration target pictures to calibration/build
5.use calibration  to generate camera.yaml
$ ./calibration -w=6 -h=8 -s=2 -n=10 -o=camera.yml -op -oe imagelist.xml

可以直接使用Opencv自带的摄像机标定示例程序，该程序位于 “\OpenCV\samples\c目录下的calibration.cpp”，程序的输入支持直接从USB摄像机读取图片标定，或者读取avi文件或者已经存放于电脑上图片进行标定。

使用说明

编译运行程序，如果未设置任何命令行参数，则程序会有提示，告诉你应该在你编译出来的程序添加必要的命令行，比如你的程序是calibration.exe(以windows操作系统为例）。则你可以添加如下命令行（以下加粗的字体所示）：

calibration -w=6 -h=8 -s=2 -n=10 -o=camera.yml -op -oe [<list_of_views.yaml>]

eg.
calibration -w=6 -h=8 -s=2 -n=10 -o=camera.yml -op -oe imagelist.xml

调用命令行和参数介绍

Usage: calibration

    -w <board_width>         # 图片某一维方向上的交点个数
    -h <board_height>        # 图片另一维上的交点个数
    [-n <number_of_frames>]  # 标定用的图片帧数
                             # (if not specified, it will be set to the number
                             #  of board views actually available)
    [-d <delay>]             # a minimum delay in ms between subsequent attempts to capture a next view
                             # (used only for video capturing)
    [-s <square_size>]       # square size in some user-defined units (1 by default) <s unit:m>
    [-o <out_camera_params>] # the output filename for intrinsic [and extrinsic] parameters
    [-op]                    # write detected feature points
    [-oe]                    # write extrinsic parameters
    [-zt]                    # assume zero tangential distortion
    [-a <aspect_ratio>]      # fix aspect ratio (fx/fy)
    [-p]                     # fix the principal point at the center
    [-v]                     # flip the captured images around the horizontal axis
    [input_data]             # 输入数据，是下面三种之中的一种:
                             #  - 指定的包含图片列表的txt文件
                             #  - name of video file with a video of the board
                             # if input_data not specified, a live view from the camera is used



上图中，横向和纵向分别为9个交点和6个交点，对应上面的命令行的命令参数应该为： -w 9 -h 6。

    经多次使用发现，不指定 -p参数时计算的结果误差较大，主要表现在对u0,v0的估计误差较大，因此建议使用时加上-p参数



list_of_views.yaml

该yaml文件表示的是你在电脑上面需要用以标定的图片列表。

view000.png
view001.png
#view002.png
view003.png
view010.png
one_extra_view.jpg

上面的例子中，前面加“井号”的图片被忽略。

[notice!!!!!]

[use imagelist_creator.cpp to generate list_of_views.yaml]
     
 OpenCV(地址为...opencv\sources\samples\cpp\imagelist_creator.cpp：是通过用户输入图像名称编写图像列表的程序；

创建一个新的工程imageListCreator（过程如Camera Calibration创建工程），并添加imagelist_creator.cpp，配置好OpenCV环境后，Build，Debug

在工程imageListCreator目录（...\imageListCreator\x64\Debug）下生成imageListCreator.exe文件。

Win+R打开运行，输入“cmd”回车，进入命令行窗口，找到...\imageListCreator\x64\Debug文件夹下，

运行 imageListCreator.exe，输入imageListCreator.exe imagelist.xml  image1_1.png image1_2.png image1_3.png image1_4.png image1_5.png image1_6.png image1_7.png image1_8.png image1_9.png image1_10.png  image1_11.png image1_12.png image1_13.png image1_14.png image1_15.png  。




输入为摄像机或者avi文件时

        "When the live video from camera is used as input, the following hot-keys may be used:\n"
            "  <ESC>, 'q' - quit the program\n"
            "  'g' - start capturing images\n"
            "  'u' - switch undistortion on/off\n";



请直接复制 calibration.cpp 中的相关代码。 


cannot find #include "opencv2/imgcodecs.hpp"

$pkg-config --modversion opencv
2.4.13.2
$cd /opt/ros/kinetic/include/opencv-3.3.1-dev/
$pwd
/opt/ros/kinetic/include/opencv-3.3.1-dev

use this path to configure C++ configurations
C/C++:edit configurations (UI)
Include path 
add path



# 读图
# 转灰度
## threshold阈值 二值化 
{
    黑底百字使用 THRESH_BINARY
    白底黑字使用 THRESH_BINARY_INV
}
变为黑底白字 二值化图像

## canny找边缘

    



# 找轮廓 
闭运算 膨胀 去除数字表盘周围黑色部分  
在运算后的二值化图像 上 找整个数字盘外部轮廓  ok   /直接找数字轮廓？
通过对轮廓的面积和比例进行筛选，提取出目标数字部分图像 ok

<!-- 对目标图像部分做漫水填充,腐蚀等操作
分别截取各个数字的图像 -->

再通过轮廓提取数字？

# 提取数字，放入KNN进行训练得到预测模型

# 加载模型进行测试


固定位置的水表，不需要用模型，边缘检测表盘，利用坐标知道数字。数字直接用OCR。

OPENCV二值化，丢给tesseract。


tesseract相关：
tesseract myimage.png stdout -c tessedit_char_whitelist=0123456789

tesseract 配置里改成只识别 0-9 数字，然后识别用 -psm 10

对于tesseract 3，我尝试根据FAQ创建配置文件。 在调用Init函数之前或将其放在名为
tessdata/configs/digits 的文本文件中：

tessedit_char_whitelist 0123456789                 

然后，它使用命令：

tesseract  imagename  outputbase  digits


tesseract  a.png stdout 可直接将结果打印至终端



设置白名单:让tesseract-OCR只识别指定内容
tesseract-ocr安装路径下的tessdata/configs/digits文件，可以看到里面有一个tessedit_char_whitelist，将其设置成我们需要得到的识别结果。
如：tessedit_char_whitelist ABCD
调用命令时，需要加上我们设置的文件名：tesseract xxx.png outfilename -psm 6 digits

tessdata/configs在/usr/share/tesseract-ocr下

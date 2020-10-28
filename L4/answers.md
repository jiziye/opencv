## 2. 图像去畸变
```c++
double x = (u-cx)/fx;
double y = (v-cy)/fy;

double x2 = x*x, y2 = y*y, xy = x*y, r2 = x2 + y2;
double x_radial = x * (1 + k1*r2 + k2*r2*r2);
double y_radial = y * (1 + k1*r2 + k2*r2*r2);
double x_tangential = 2*p1*xy + p2*(r2 + 2*x2);
double y_tangential = 2*p2*xy + p1*(r2 + 2*y2);
double xd = x_radial + x_tangential;
double yd = y_radial + y_tangential;

u_distorted = xd*fx + cx;
v_distorted = yd*fy + cy;
```
代码工程见 **UndistortImage文件夹**

## 3. 双目视差的使用
```c++
point[2] = fx * d / disparity.at<uchar>(v,u);
point[0] = (u-cx)/fx * point[2];
point[1] = (v-cy)/fy * point[2];

pointcloud.push_back(point);
```
代码工程见 **StereoDisparity文件夹**

## 4. 矩阵微分

## 5. 高斯牛顿法的曲线拟合实验
代码工程见 **GaussNewton文件夹**

 #include "sad.h"
 int main(int argc,  char* argv[])
 {
     Mat l = imread("left1.png", 0);
     Mat r  = imread("right1.png", 0);
     Mat Disparity;

     SAD mySAD;
     Disparity = mySAD.computerSAD(l,r);

     imshow("left", l);
     imshow("rigth",r);
     imshow("dispariy",Disparity);

     waitKey();
     return 0;
 }


#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src;
Mat src_gray;
int thresh = 100;
int max_thresh = 256;
RNG rng(123456);

void thresh_callback(int, void *);

int main(int argc, char const *argv[])
{
    /* code */
    const char *window_name = "source image";
    const char *filename = argc >= 2 ? argv[1] : "./pic/HotBalloon1.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray,src_gray,Size(3,3));
    namedWindow(window_name,WINDOW_AUTOSIZE);
    imshow(window_name,src_gray);
    createTrackbar( " Threshold:", window_name, &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );
    waitKey(0);
}


void thresh_callback(int, void *){
    Mat thresh_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    threshold(src_gray,thresh_output,thresh,255,THRESH_BINARY);
    findContours(thresh_output,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> center(contours.size());
    vector<float> radius(contours.size());

    for (size_t i = 0; i < contours.size(); i++)
    {
        /* code */
        // 功能：对图像轮廓点拟合多边形；该函数用另一条曲线或具有较少顶点的多边形逼近曲线或多边形，使它们之间的距离小于或等于指定的精度；
        // (1) 第一个参数，InputArray curve，一般是由图像的轮廓点组成的点集；
        // (2) 第二个参数，OutputArray approxCurve，表示输出的多边形点集；
        // (3) 第一个参数，double epsilon，主要表示输出的精度；这是原始曲线与其近似之间的最大距离；
        // (4) 第二个参数，bool closed，表示输出的多边形是否封闭；true表示封闭，false表示不封闭；
        approxPolyDP(Mat(contours[i]),contours_poly[i],3,true);
        // 用一个最小的矩形，把找到的形状包起来。
        boundRect[i]=boundingRect(Mat(contours_poly[i]));
        minEnclosingCircle(contours_poly[i],center[i],radius[i]);
    }
    Mat drawing =Mat::zeros(thresh_output.size(),CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        /* code */
        Scalar color=Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(drawing,contours_poly,(int)i,color,1,8,vector<Vec4i>(),0,Point());
        rectangle(drawing,boundRect[i].tl(),boundRect[i].br(),color,2,8,0);
        circle(drawing,center[i],(int)radius[i],color,2,8,0);
    }
    namedWindow("Contours",WINDOW_AUTOSIZE);
    imshow("Contours",drawing);
    
}
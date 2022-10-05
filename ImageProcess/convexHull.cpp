#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src;
Mat src_gray;
int thresh = 100;
int maxthresh = 256;
RNG rng(123456);

void thresh_callback(int, void *);

int main(int argc, char const *argv[])
{
    /* code */
    const char *window_name = "source image";
    const char *filename = argc >= 2 ? argv[1] : "./pic/hand.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    blur(src_gray, src_gray, Size(3, 3));
    imshow(window_name, src_gray);

    createTrackbar("Threshold:", window_name, &thresh, maxthresh, thresh_callback);
    thresh_callback(0, 0);
    waitKey(0);
    return 0;
}

void thresh_callback(int, void *)
{
    Mat thresh_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    threshold(src_gray, thresh_output, thresh, 255, THRESH_BINARY);
    imshow("thresh_output", thresh_output);
     // coutours向量内每个元素保存了一组由连续的Point点构成的点的集合的向量，每一组Point点集就是一个轮廓
    // hierarchy[i]定义了一个“向量内每一个元素包含了4个int型变量”的向量
    // 表示,i个轮廓的后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号
    // void findContours//提取轮廓，用于提取图像的轮廓
    // (
    // InputOutputArray image,//输入图像，必须是8位单通道图像，并且应该转化成二值的
    // OutputArrayOfArrays contours,//检测到的轮廓，每个轮廓被表示成一个point向量
    // OutputArray hierarchy,//可选的输出向量，包含图像的拓扑信息。其中元素的个数和检测到的轮廓的数量相等
    // int mode,//说明需要的轮廓类型和希望的返回值方式
    // int method,//轮廓近似方法
    // Point offset = Point()
    // )
    findContours(thresh_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    vector<vector<Point>> hull(contours.size());

    for (size_t i = 0; i < contours.size(); i++)
    {   
        convexHull(Mat(contours[i]), hull[i], false);
        // convexhull函数的作用：计算出图像的凸包，根据图像的轮廓点，通过函数convexhull转化成凸包的点点坐标，从而画出图像的凸包。
        // InputArray points: 得到的点集，一般是用图像轮廓函数求得的轮廓点
        // OutputArray hull: 输出的是凸包的二维xy点的坐标值，针对每一个轮廓形成的
        // bool clockwise = false: 表示凸包的方向，顺时针或者逆时针
        // bool returnPoint = true: 表示返回点还是点地址的索引
    }
    Mat drawing = Mat::zeros(thresh_output.size(), CV_8UC3);

    for (size_t i = 0; i < contours.size(); i++)
    {
        /* code */
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point());
        drawContours(drawing, hull, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point());
         // void drawContours//绘制轮廓，用于绘制找到的图像轮廓
        // (
        // InputOutputArray image,//要绘制轮廓的图像
        // InputArrayOfArrays contours,//所有输入的轮廓，每个轮廓被保存成一个point向量
        // int contourIdx,//指定要绘制轮廓的编号，如果是负数，则绘制所有的轮廓
        // const Scalar& color,//绘制轮廓所用的颜色
        // int thickness = 1, //绘制轮廓的线的粗细，如果是负数，则轮廓内部被填充
        // int lineType = 8, /绘制轮廓的线的连通性
        // InputArray hierarchy = noArray(),//关于层级的可选参数，只有绘制部分轮廓时才会用到
        // int maxLevel = INT_MAX,//绘制轮廓的最高级别，这个参数只有hierarchy有效的时候才有效
        // //maxLevel=0，绘制与输入轮廓属于同一等级的所有轮廓即输入轮廓和与其相邻的轮廓
        // //maxLevel=1, 绘制与输入轮廓同一等级的所有轮廓与其子节点。
        // //maxLevel=2，绘制与输入轮廓同一等级的所有轮廓与其子节点以及子节点的子节点
        // Point offset = Point()
        // )
    }

    namedWindow("Hull demo", WINDOW_AUTOSIZE);
    imshow("Hull demo", drawing);
}

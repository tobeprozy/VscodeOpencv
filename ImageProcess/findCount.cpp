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
    const char *filename = argc >= 2 ? argv[1] : "./pic/happyfish.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    blur(src_gray, src_gray, Size(3, 3));
    imshow(window_name, src_gray);

    createTrackbar("Canny thresh:", window_name, &thresh, maxthresh, thresh_callback);
    thresh_callback(0, 0);
    waitKey(0);
    return 0;
}

void thresh_callback(int, void *)
{
    Mat canny_output;
    vector<vector<Point>> coutours;

    vector<Vec4i> hierarchy;

    // void cv::Canny(InputArray image,OutputArray edges,double threshold1,double threshold2,
    //                int apertureSize = 3,bool L2gradient = false)
    Canny(src_gray, canny_output, thresh, thresh * 2, 3);
    imshow("canny", canny_output);

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
    findContours(canny_output, coutours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < coutours.size(); i++)
    {
        /* code */
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, coutours, (int)i, color, 2, 8, hierarchy, 0, Point());
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
    namedWindow("Counters", WINDOW_AUTOSIZE);
    imshow("Counters", drawing);
}

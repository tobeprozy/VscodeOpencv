#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    /* code */
    Mat src, src_gray, dst;
    int kernel_size=3,scale=1,delta=0,ddepth=CV_16S;
    const char* window_name = "Laplacian - Simple Edge Detector";
    const char *filename = argc >= 2 ? argv[1] : "./pic/lena.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;
    GaussianBlur(src,src,Size(3,3),0,0,BORDER_DEFAULT);
    cvtColor(src,src_gray,COLOR_BGR2GRAY);
    imshow("window_name",src_gray);

    Mat abs_dst;
    Laplacian(src_gray,dst,ddepth,kernel_size,scale,delta,BORDER_DEFAULT);
    // imshow("dst",abs(dst));
    // 将Laplace Operator的输出转换为CV_8U图像
    convertScaleAbs(dst,abs_dst);
    imshow(window_name,abs_dst);
    waitKey();
    return 0;
}
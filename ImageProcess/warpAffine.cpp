#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
const char *source_window = "Source image";
const char *warp_window = "Warp";
const char *warp_rotate_window = "Warp + Rotate";

int main(int argc, char const *argv[])
{
    /* code */
    Point2f srcTri[3];
    Point2f dstTri[3];

    Mat rot_mat(2, 3, CV_32FC1);
    Mat warp_mat(2, 3, CV_32FC1);

    Mat src, warp_dst, warp_rotate_dst;

    const char *filename = argc >= 2 ? argv[1] : "./pic/lena.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;

    //imshow("origin", src);
    warp_dst = Mat::zeros(src.rows, src.cols, src.type());

    srcTri[0] = Point2f(0, 0);
    srcTri[1] = Point2f(src.cols - 1.f, 0);
    srcTri[2] = Point2f(0, src.rows - 1.f);

    dstTri[0] = Point2f(src.cols * 0.0f, src.rows * 0.33f);
    dstTri[1] = Point2f(src.cols * 0.85f, src.rows * 0.25f);
    dstTri[2] = Point2f(src.cols * 0.15f, src.rows * 0.7f);

    //根据三对点计算变换矩阵
    warp_mat = getAffineTransform(srcTri, dstTri);
    warpAffine(src, warp_dst, warp_mat, warp_dst.size());
    //imshow("warp", warp_dst);

    Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
    double angle = -50.0;
    double scale = 0.6;

    rot_mat = getRotationMatrix2D(center, angle, scale);

    // src：输入图像
    // warp_dst：输出图像
    // warp_mat：仿射变换
    // warp_dst.size（）：输出图像所需的大小
    warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
    namedWindow(source_window, WINDOW_AUTOSIZE);
    imshow(source_window, src);

    namedWindow(warp_window, WINDOW_AUTOSIZE);
    imshow(warp_window, warp_dst);

    namedWindow(warp_rotate_window, WINDOW_AUTOSIZE);
    imshow(warp_rotate_window, warp_rotate_dst);

    waitKey(0);

    return 0;
}

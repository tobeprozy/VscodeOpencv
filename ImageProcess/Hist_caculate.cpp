#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    Mat src, dst;
    const char *source_window = "source image";
    const char *equalized_window = "Equalized image";

    const char *filename = argc >= 2 ? argv[1] : "./pic/lena.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;

    vector<Mat> bgr_planes;
    //在三个R，G和B平面中分离源图像。
    split(src, bgr_planes);

    int histSize = 256;
    float range[] = {0, 256};

    const float *histRange = {range};

    bool uniform = true;
    bool accumulate = false;

    Mat b_hist, g_hist, r_hist;
    
    // b_hist是1列256行表示每个像素的统计值
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    // &bgr_planes [0]：源数组（s）
    // 1：源数组的数量（在这种情况下，我们正在使用1.我们可以在这里输入一个数组列表）
    // 0：要测量的通道（dim）。在这种情况下，它只是强度（每个阵列是单通道），所以我们只写0。
    // Mat()：在源数组上使用的掩码（指示要忽略的像素的零）。如果未定义，则不使用它
    // b_hist：要存储直方图的Mat对象
    // 1：直方图维度。
    // histSize：每个使用的维数的数量
    // histRange：每个维度要测量的值的范围
    // uniform和accumulate：纸箱尺寸相同，直方图在开始时清除。
    // Draw the histograms for B G and R
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    // b_hist:输入数组
    // b_hist:输出归一化数组（可以相同）
    // 0和histImage.rows:对于这个例子，它们是对r_hist **的值进行归一化的下限和上限
    // NORM_MINMAX:指示归一化类型的参数（如上所述，它调整之前设置的两个限制之间的值）
    // -1:意味着输出归一化数组将与输入的类型相同
    // Mat():可选掩码   
    for (size_t i = 1; i < histSize; i++)
    {
        /* code */
        line(histImage, Point(bin_w * (i - 1),  - cvRound(b_hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
             Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
             Scalar(0, 0, 255), 2, 8, 0);
    }

    namedWindow("calcHist Demo", WINDOW_AUTOSIZE);
    imshow("calcHist Demo", histImage);
    waitKey(0);
    return 0;
}

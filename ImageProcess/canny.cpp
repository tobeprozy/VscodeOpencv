#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;
Mat src, src_gray, dst, detected_edge;
int lowThreshold;
int const max_lowThreshold = 100;
int eratio = 3;
int kernel_size = 3;
const char *window_name = "Edge Map";

static void cannyThreshold(int, void *)
{

    blur(src_gray, detected_edge, Size(3, 3));
    Canny(detected_edge, detected_edge, lowThreshold, eratio * lowThreshold, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edge);
    imshow(window_name, dst);
}

int main(int argc, char const *argv[])
{
    /* code */

    int kernel_size = 3, scale = 1, delta = 0, ddepth = CV_16S;
    const char *window_name = "Laplacian - Simple Edge Detector";
    const char *filename = argc >= 2 ? argv[1] : "./pic/lena.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;
    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, cannyThreshold);
    cannyThreshold(0, 0);
    waitKey(0);
    return 0;
}
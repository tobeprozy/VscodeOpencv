#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


int main(int argc, char const *argv[])
{
    /* code */
    Mat src,dst;
    const char* source_window="source image";
    const char* equalized_window="Equalized image";

    const char *filename = argc >= 2 ? argv[1] : "./pic/lena.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;

    cvtColor(src,src,COLOR_BGR2GRAY);
    equalizeHist(src,dst);

    namedWindow(source_window,WINDOW_AUTOSIZE);
    namedWindow(equalized_window,WINDOW_AUTOSIZE);

    imshow(source_window,src);
    imshow(equalized_window,dst);

    waitKey(0);
    return 0;
}

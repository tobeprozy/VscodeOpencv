#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is ../data/board.jpg\n" << endl;
}
int main(int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv,
        "{help h ||}{@image|./pic/board.jpg|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    string filename = parser.get<string>("@image");
    Mat img = imread(filename, IMREAD_COLOR);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/16, // change this value to detect circles with different distances to each other
                 100, 30, 1, 30 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );

    // gray：输入图像（灰度）。
    // circles：存储套3个的值的矢量：为每个检测到的圆。xc,yc,r
    // HOUGH_GRADIENT：定义检测方法。目前这是OpenCV中唯一可用的。
    // dp = 1：分辨率的反比。
    // min_dist = gray.rows / 16：检测到的中心之间的最小距离。
    // param_1 = 200：内部Canny边缘检测器的上限阈值。
    // param_2 = 100 *：中心检测阈值。
    // min_radius = 0：要检测的最小半径。如果未知，则将零置为默认值。
    // max_radius = 0：要检测的最大半径。如果未知，则将零置为默认值。

    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        //画一个圆
        circle( img, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        //在中心画一个圆点
        circle( img, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }
    imshow("detected circles", img);
    waitKey();
    return 0;
}
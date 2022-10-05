#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"


#include <iostream>
using namespace std;
using namespace cv;
static void help()
{
    cout << "\nThis program demonstrates line finding with the Hough transform.\n"
            "Usage:\n"
            "./houghlines <image_name>, Default is ../data/pic1.png\n" << endl;
}


int main(int argc, char const *argv[])
{
    /* code */
    Mat src;
    const char *window_name = "Laplacian - Simple Edge Detector";
    const char *filename = argc >= 2 ? argv[1] : "./pic/building.jpg";

    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;
    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
#if 0
    vector<Vec2f> lines;
    HoughLines(dst,lines,1,CV_PI/180,100,0,0);
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho=lines[i][0],theta=lines[i][1];
        Point pt1,pt2;
        double a = cos(theta), b = sin(theta);
        double x0=rho*cos(theta),y0=rho*sin(theta);

        pt1.x=cvRound(x0+1000*(-b));
        pt1.y=cvRound(y0+100*a);

        pt2.x=cvRound(x0-1000*(-b));
        pt2.y=cvRound(y0-1000*a);
        
        line(cdst,pt1,pt2,Scalar(0,0,255),3,CV_AA);
        /* code */
    }
    
#else
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1.5, LINE_AA);
    }
#endif
    imshow("source",src);
    imshow("detected lines",cdst);    
    waitKey(0);
    return 0;
}

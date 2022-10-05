#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src, dst;
Mat map_x, map_y;

const char *remap_window = "Remap Demo";

int ind = 0;

void update_map();

int main(int argc, char const *argv[])
{
    /* code */
    CommandLineParser parser(argc, argv, "{@image |./pic/chicky_512.png|input image name}");
    string filename = parser.get<string>("@image");
    src = imread(filename, IMREAD_COLOR);
    dst.create(src.size(), src.type());
    map_x.create(src.size(), CV_32FC1);
    map_y.create(src.size(), CV_32FC1);

    namedWindow(remap_window, WINDOW_AUTOSIZE);
    for (;;)
    {
        char c = (char)waitKey(1000);
        if (c == 27)
            break;
        update_map();
        remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
        imshow(remap_window, dst);
        /* code */
    }

    return 0;
}

void update_map(void)
{
    ind = ind % 4;
    for (size_t j = 0; j < src.rows; ++j)
    {
        for (size_t i = 0; i < src.cols; i++)
        {
            switch (ind)
            {
            case 0:
                if (i > src.cols * 0.25 && i < src.cols * 0.75 && j > src.rows * 0.25 && j < src.rows * 0.75)
                {
                    // Mat类的rows（行）对应IplImage结构体的heigh（高），行与高对应point.y   
                    // Mat类的cols（列）对应IplImage结构体的width（宽），列与宽对应point.x   
                    // 这个不难理解，opencv的坐标系原点在左上角，但是还是水平轴是x，垂直轴是y
                   
                    // cv::Point pt =  Point(10, 8);  
                    // 等同于:
                    // cv::Point pt;  
                    // pt.x = 10;  
                    // pt.y = 8; 
                    
                     // 注意因为at(y,x)，而不是at(x,y)
                    map_x.at<float>(j, i) = 2 * (i - src.cols * 0.25) + 0.5;
                    map_y.at<float>(j, i) = 2 * (j - src.rows * 0.25) + 0.5;
                }
                else
                {
                    map_x.at<float>(j, i) = 0;
                    map_y.at<float>(j, i) = 0;
                }
                break;
            case 1:
                map_x.at<float>(j, i) = i;
                map_y.at<float>(j, i) = src.rows - j;
                break;
            case 2:
                map_x.at<float>(j, i) = src.cols - i;
                map_y.at<float>(j, i) = j;
                break;
            case 3:
                map_x.at<float>(j, i) = src.cols - i;
                map_y.at<float>(j, i) = src.rows - j;
                break;
            } // end of switch
        }
    }
    ind++;
}
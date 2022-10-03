#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;
Mat src, dst;
int top, bottom, vleft, vright;
int borderType;
const char *windown_name = "copyMarkerBorder Demo";
RNG rng(123456);

int main(int argc, char const *argv[])
{
    /* code */
    const char *filename = argc >= 2 ? argv[1] : "./pic/lena.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;
    printf("\n \t copyMakeBorder Demo: \n");
    printf("\t -------------------- \n");
    printf(" ** Press 'c' to set the border to a random constant value \n");
    printf(" ** Press 'r' to set the border to be replicated \n");
    printf(" ** Press 'ESC' to exit the program \n");
    namedWindow(windown_name, WINDOW_AUTOSIZE);
    top = (int)(0.05 * src.rows);
    bottom = (int)(0.05 * src.rows);
    vleft = (int)(0.05 * src.cols);
    vright = (int)(0.05 * src.cols);

    dst = src;
    imshow(windown_name, dst);
    for (;;)
    {
        char c = (char)waitKey(500);
        if (c == 27)
            break; // esc
        else if (c == 'c')
        {
            borderType = BORDER_CONSTANT;
        }
        else if (c == 'r')
        {
            borderType = BORDER_REPLICATE;
        }
        // 如果按“r”，边框将成为边缘像素的副本。
        // 如果按“c”，随机彩色边框将再次出现
        Scalar value(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        copyMakeBorder(src,dst,top,bottom,vleft,vright,borderType,value);
        // src：源图像
        // dst：目的地图像
        // top, bottom, left, right：图像每边边框的宽度（以像素为单位）。我们将它们定义为图像的原始大小的5％。
        // borderType：定义应用什么类型的边框。对于该示例，它可以是常量或复制的。
        // value：如果borderType为BORDER_CONSTANT，则这是用于填充边框像素的值。
        imshow(windown_name,dst);
    }

    return 0;
}

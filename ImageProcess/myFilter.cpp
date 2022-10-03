#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(int argc, char const *argv[])
{
    /* code */
    Mat src,dst,kernal;
    Point anchor;
    double delta;
    int ddepth,kernal_size;
    const char* window_name = "filter2D Demo";
    const char *filename=argc>=2?argv[1]:"./pic/lena.jpg";
    src=imread(filename,IMREAD_COLOR);
    if(src.empty()) return -1;

    // 初始化线性滤波器的参数
    anchor=Point(-1,-1);
    delta=0;
    ddepth=-1;
    int ind=0;

    for(;;){
        char c=(char)waitKey(500);
        if(c=='q') break;
        kernal_size=3+2*(ind%5);

        //定义滤波器核
        kernal=Mat::ones(kernal_size,kernal_size,CV_32F)/(float)(kernal_size*kernal_size);
        filter2D(src,dst,ddepth,kernal,anchor,delta,BORDER_DEFAULT);
        // src：源图像
        // dst：目的地图像
        // ddepth：深度dst。负值（如−1）表示深度与源相同。
        // 内核：要通过图像扫描的内核
        // anchor：锚点相对于其内核的位置。位置点（-1，-1）表示默认的中心。
        // delta：在关联期间要添加到每个像素的值。默认情况下为0
        // BORDER_DEFAULT：我们默认设置此值

        imshow(window_name,dst);
        ind++;
    }
    return 0;
}

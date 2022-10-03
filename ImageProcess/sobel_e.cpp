#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    /* code */
    Mat src, src_gray, grad;
    const char* window_name = "Sobel Demo - Simple Edge Detector";
    const char *filename = argc >= 2 ? argv[1] : "./pic/lena.jpg";
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
        return -1;
    int scale = 1, delta = 0, ddepth = CV_16S;
    // 填充办法
    //   1，BORDER_CONSTANT：填充边缘用指定的像素值
    //   2，BORDER_REPLICATE：填充边缘用已知的边缘像素
    //   3，BORDER_WRAP：填充边缘用对应的另一边的像素
    //   4，BORDER_DEFAULT：不做操作。
    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    cvtColor(src, src_gray, COLOR_BGR2BGRA);
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    // Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT ); 
    // Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );   
    // ​src_gray​：在我们的示例中，输入图像。这里是​CV_8U​；
    // ​grad_x / * grad_y *​：输出图像；
    // ​ddepth​：输出图像的深度。我们将其设置为​CV_16S​以避免溢出；
    // ​x_order​：​x​方向上导数的顺序；
    // ​y_order​：​y​方向上导数的顺序；
    // ​scale​，​delta​和​BORDER_DEFAULT​：我们使用默认值。

    // 将部分结果转换回​CV_8U
    // void convertScaleAbs(InputArray src, OutputArray dst,double alpha = 1, double beta = 0);
    // convertScaleAbs函数是一个位深转化函数，可将任意类型的数据转化为CV_8UC1。具体数据处理方式如下：
    // (1). 对于src*alpha+beta的结果如果是负值且大于-255，则直接取绝对值；
    // (2). 对于src*alpha+beta的结果如果大于255，则取255；
    // (3). 对于src*alpha+beta的结果是负值，且小于-255，则取255；
    // (4). 对于src*alpha+beta的结果如果在0-255之间，则保持不变；

    convertScaleAbs( grad_x, abs_grad_x );  
    convertScaleAbs( grad_y, abs_grad_y );  

    // 梯度合成
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad ); 
    // src1：第一幅图片（背景图片）；
    // alpha：第一幅图片的权重；
    // src2：第二幅图片（需要融合的图片）；
    // beta：第二幅图片的权重；
    // gamma：一个作用到加权和后的图像上的标量， 可以理解为加权和后的图像的偏移量；
    // （计算两个数组的加权和 (dst =alphasrc1 + betasrc2 + gamma)）
    // dst：融合后的图片（输出图片）；
    // dtype：输出阵列的可选深度，有默认值-1。（笔者认为是第二幅图片的深度） 
    imshow(window_name,grad);
    waitKey(0);  
    return 0;
}

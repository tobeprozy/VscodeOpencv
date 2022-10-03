#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include<iostream>
using namespace std;
using namespace cv;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
void Threshold_Demo( int, void* );

int main(int argc, char const *argv[])
{
    /* code */
    const char*filename=argc>=2?argv[1]:"pic/chicky_512.png";

    src=imread(filename,IMREAD_COLOR);
    if (src.empty()) return -1;
    
    cvtColor(src,src_gray,COLOR_BGR2BGRA);
    namedWindow(window_name,WINDOW_AUTOSIZE);

  createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Threshold_Demo ); // Create Trackbar to choose type of Threshold
  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo ); // Create Trackbar to choose Threshold value
    Threshold_Demo(0,0);
    for(;;){
        char c=(char) waitKey(20);
        if(c=='q') break;
    }

    return 0;
}

void Threshold_Demo(int ,void*){
     /* 0: Binary
     1: Binary Inverted:倒数，大于阈值为0，小于阈值为最大值
     
     2: Threshold Truncated：截断，大于阈值为变为阈值
     3: Threshold to Zero：小于阈值为0
     4: Threshold to Zero Inverted：大于阈值为0，小于阈值保持保持不变
   */
  threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

// src_gray：我们的输入图像
// dst：目的地（输出）图像
// threshold_value：进行阈值操作时阈值的大小。
// max_BINARY_value：与二进制阈值操作（用于设置所选像素）一起使用的值
// threshold_type：阈值操作之一。它们列在上述功能的注释部分。
  imshow( window_name, dst );
}

#include<opencv2/opencv.hpp>

//一定要添加环境环境，不仅在vs配置，还要在电脑，否则没有错误也不运行，烦死
using namespace cv;
using namespace std;
int main()
{
    cout<<"nihao"<<endl;
    Mat srcImage=imread("F:/Programing/VscodeOpencv/1.jpg");
    imshow("Origin",srcImage);
    waitKey(0);
    cout<<"nihao"<<endl;
    return 0;
}
#include<opencv2/opencv.hpp>
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
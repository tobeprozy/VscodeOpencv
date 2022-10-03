#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    /* code */
     Mat image;
     const char* filename = argc >=2 ? argv[1] : "./pic/cat.jpg";
    image=imread(filename);
    imshow("Original image",image);

    Mat grayImage;
    if(image.channels()==3) cvtColor(image,grayImage,CV_BGR2GRAY);
    else grayImage=image;
    imshow("grayImage",grayImage);

    Mat bw;

    //自适应阈值
    // 根据图像不同区域亮度分布，计算其局部阈值，所以对于图像不同区域，能够自适应计算不同的阈值，因此被称为自适应阈值法。(其实就是局部阈值法)
    // Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
    adaptiveThreshold(~grayImage,bw,255,CV_ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,15,-2);

    imshow("binary",bw);
    
     // Create the images that will use to extract the horizontal and vertical lines
    Mat horizontal = bw.clone();
    Mat vertical = bw.clone();

    // Specify size on horizontal axis
    int horizontalsize = horizontal.cols / 30;
     // Create structure element for extracting horizontal lines through morphology operations
    // 第一个参数：矩形——MORPH_RECT，交叉形——MORPH_CROSS，椭圆形——MORPH_ELLIPSE
    // 第二个参数：卷积核的尺寸
    // 第三个参数：锚点的位置，默认值Point(-1, -1)，表示锚点位于中心点
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));

    erode(horizontal,horizontal,horizontalStructure,Point(-1,-1));
    dilate(horizontal,horizontal,horizontalStructure,Point(-1,-1));
    
    // Show extracted horizontal lines
    imshow("horizontal", horizontal);

    // Specify size on vertical axis
    int verticalsize = vertical.rows / 30;
    // Create structure element for extracting vertical lines through morphology operations
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size( 1,verticalsize));
    // Apply morphology operations
    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
    // Show extracted vertical lines
    imshow("vertical", vertical);
    
    // Inverse vertical image
    bitwise_not(vertical, vertical);
    imshow("vertical_bit", vertical);

    // Extract edges and smooth image according to the logic
    // 1. extract edges
    // 2. dilate(edges)
    // 3. src.copyTo(smooth)
    // 4. blur smooth img
    // 5. smooth.copyTo(src, edges)

    //step1:
    Mat edges;
    // 当block很小时，如block_size=3 or 5 or 7时，“自适应”的程度很高，即容易出现block里面的像素值都差不多，
    // 这样便无法二值化，而只能在边缘等梯度大的地方实现二值化，结果显得它是边缘提取函数
    adaptiveThreshold(vertical,edges,255,CV_ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,3,-2);
    imshow("edges",edges);

    //step2:
    Mat kernal=Mat::ones(2,2,CV_8UC1);
    dilate(edges,edges,kernal);
    imshow("dilate",edges);

    // Step 3
    //将vertical平滑处理一下，再和边缘叠加
    Mat smooth;
    vertical.copyTo(smooth);
    // Step 4
    blur(smooth, smooth, Size(2, 2));

    imshow("smooth1", smooth);
    // Step 5
    // mask和image重叠传递给imageRoi
    smooth.copyTo(vertical, edges);
    // Show final result
    imshow("smooth2", vertical);
    waitKey(0);
    return 0;
}

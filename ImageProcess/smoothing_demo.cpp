#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
Mat src; Mat dst;
char window_name[] = "Smoothing Demo";
int display_caption( const char* caption );//文字
int display_dst( int delay );
int main( void )
{
  namedWindow( window_name, WINDOW_AUTOSIZE );
  src = imread( "./pic/lena.jpg", IMREAD_COLOR );


  if( display_caption( "Original Image" ) != 0 ) { return 0; }
  dst = src.clone();
  if( display_dst( DELAY_CAPTION ) != 0 ) { return 0; }

  //均值滤波，或者叫归一化滤波器----blur是模糊的意思
  if( display_caption( "Homogeneous Blur" ) != 0 ) { return 0; }
  for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
      { blur( src, dst, Size( i, i ), Point(-1,-1) );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }
// src：源图像
// dst：目标图像
// Size（w，h）：定义要使用的内核的大小（宽度为w像素和高度h像素）
// Point（-1，-1）：表示相对于邻域的锚点（被评估的像素）的位置。如果存在负值，则内核的中心被认为是锚点。

  //高斯滤波
  if( display_caption( "Gaussian Blur" ) != 0 ) { return 0; }
  for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )

      { GaussianBlur( src, dst, Size( i, i ), 0, 0 );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }
  
  //中值滤波
  if( display_caption( "Median Blur" ) != 0 ) { return 0; }
  for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
      { medianBlur ( src, dst, i );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }
  
  // 双边滤波
  if( display_caption( "Bilateral Blur" ) != 0 ) { return 0; }
  for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
      { bilateralFilter ( src, dst, i, i*2, i/2 );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }
  display_caption( "End: Press a key!" );
  waitKey(0);
  return 0;
}

int display_caption( const char* caption )
{
  dst = Mat::zeros( src.size(), src.type() );
  putText( dst, caption,
           Point( src.cols/4, src.rows/2),
           FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );
  imshow( window_name, dst );
  int c = waitKey( DELAY_CAPTION );//有键按下，就退出
  if( c >= 0 ) { return -1; }
  return 0;
}


int display_dst( int delay )
{
  imshow( window_name, dst );
  int c = waitKey ( delay );
  if( c >= 0 ) { return -1; }
  return 0;
}
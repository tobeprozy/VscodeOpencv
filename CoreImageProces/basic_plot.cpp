#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include<iostream>

using namespace std;
using namespace cv;

void MyEllipse( Mat img, double angle );
void MyFilledCircle( Mat img, Point center );
void MyPolygon( Mat img );
void MyLine( Mat img, Point start, Point end );

#define w 400
int main(int argc, char const *argv[])
{
    
    char atom_window[]="Drawing 1:Atom";
    char rook_window[]="Drawing 2:Rook";

    Mat atom_image=Mat::zeros(w,w,CV_8UC3);
    Mat rook_image=Mat::zeros(w,w,CV_8UC3);

    // 椭圆
    MyEllipse(atom_image,90);
    MyEllipse(atom_image,0);
    MyEllipse(atom_image,45);
    MyEllipse(atom_image,-45);

    //圆
    MyFilledCircle(atom_image,Point(w/2,w/2));
    
    // 多边形
    MyPolygon(rook_image);

    // 矩形
    rectangle(rook_image,Point(0,7*w/8),Point(w,w),Scalar(0,255,255),FILLED,LINE_8);

    // 直线
    MyLine( rook_image, Point( 0, 15*w/16 ), Point( w, 15*w/16 ) );
    MyLine( rook_image, Point( w/4, 7*w/8 ), Point( w/4, w ) );
    MyLine( rook_image, Point( w/2, 7*w/8 ), Point( w/2, w ) );
    MyLine( rook_image, Point( 3*w/4, 7*w/8 ), Point( 3*w/4, w ) );

    imshow( atom_window, atom_image );
    moveWindow( atom_window, 0, 200 );
    imshow( rook_window, rook_image );
    moveWindow( rook_window, w, 200 );
    return 0;
}

// 绘制一个椭圆
void MyEllipse( Mat img, double angle )
{
  int thickness = 2;
  int lineType = 8;
  ellipse( img,
       Point( w/2, w/2 ),
       Size( w/4, w/16 ),
       angle,
       0,
       360,
       Scalar( 255, 0, 0 ),
       thickness,
       lineType );
// 椭圆显示在图像img中
// 椭圆中心位于**（w / 2，w / 2）**的点，并且被包围在大小为**（w / 4，w / 16）**
// 椭圆旋转角度
// 椭圆延伸0到360度之间的圆弧
// 图中的颜色将为标量（255,0,0），表示BGR值为蓝色。
// 椭圆的厚度为2。
}

void MyFilledCircle( Mat img, Point center )
{
  circle( img,
      center,
      w/32,
      Scalar( 0, 0, 255 ),
      FILLED,
      LINE_8 );

// 将显示圆圈的图像（img）
// 圆的中心表示为点中心
// 圆的半径：w / 32
// 圆的颜色：标量（0,0,255），表示BGR中的红色
// 由于厚度 = -1，圆将被绘制填充。
}

void MyPolygon( Mat img )
{
  int lineType = LINE_8;
  Point rook_points[1][20];
  rook_points[0][0]  = Point(    w/4,   7*w/8 );
  rook_points[0][1]  = Point(  3*w/4,   7*w/8 );
  rook_points[0][2]  = Point(  3*w/4,  13*w/16 );
  rook_points[0][3]  = Point( 11*w/16, 13*w/16 );
  rook_points[0][4]  = Point( 19*w/32,  3*w/8 );
  rook_points[0][5]  = Point(  3*w/4,   3*w/8 );
  rook_points[0][6]  = Point(  3*w/4,     w/8 );
  rook_points[0][7]  = Point( 26*w/40,    w/8 );
  rook_points[0][8]  = Point( 26*w/40,    w/4 );
  rook_points[0][9]  = Point( 22*w/40,    w/4 );
  rook_points[0][10] = Point( 22*w/40,    w/8 );
  rook_points[0][11] = Point( 18*w/40,    w/8 );
  rook_points[0][12] = Point( 18*w/40,    w/4 );
  rook_points[0][13] = Point( 14*w/40,    w/4 );
  rook_points[0][14] = Point( 14*w/40,    w/8 );
  rook_points[0][15] = Point(    w/4,     w/8 );
  rook_points[0][16] = Point(    w/4,   3*w/8 );
  rook_points[0][17] = Point( 13*w/32,  3*w/8 );
  rook_points[0][18] = Point(  5*w/16, 13*w/16 );
  rook_points[0][19] = Point(    w/4,  13*w/16 );
  const Point* ppt[1] = { rook_points[0] };
  int npt[] = { 20 };
  fillPoly( img,
        ppt,
        npt,
        1,
        Scalar( 255, 255, 255 ),
        lineType );
// 多边形将在img上绘制
// 多边形的顶点是ppt中的一组点
// 要绘制的顶点总数为npt
// 要绘制的多边形的数量只有1
// 多边形的颜色由Scalar（255,255,255）定义，它是白色的BGR值
}
void MyLine( Mat img, Point start, Point end )
{
  int thickness = 2;
//   画一条线
  int lineType = LINE_8;
  line( img,
    start,
    end,
    Scalar( 0, 0, 0 ),
    thickness,
    lineType );
// 从点开始到点结束绘制一条线
// 该行显示在图像img中
// 线颜色由Scalar（0,0,0）定义，它是与Black相对应的RGB值
// 线厚度设定为厚度（在这种情况下为2）
// 线是8连接线（lineType = 8）
}
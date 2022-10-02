#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    double alpha=1.0;
    int beta=0;

    string imageName("./pic/lena.jpg");
    
    Mat image=imread(imageName);
    imshow("origin",image);
    Mat new_image=Mat::zeros(image.size(),image.type());

    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";    cin >> beta;

    for(int y=0;y<image.rows;++y){//行
        for(int x=0;x<image.cols;++x){//列
            for(int c=0;c<3;++c){//通道数
                new_image.at<Vec3b>(y,x)[c]=saturate_cast<uchar>(alpha*(image.at<Vec3b>(y,x)[c])+beta);
            }
        }
    }

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("New Image", WINDOW_AUTOSIZE);
    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();

    return 0;
}

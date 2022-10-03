#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp" 
#include "opencv2/highgui.hpp"

using namespace std;

using namespace cv;


int main(int argc, char const *argv[])
{
    /* code */
    const char *filename =argc>2?argv[1]: "./pic/lena.jpg";
    Mat image=imread(filename,IMREAD_GRAYSCALE);
    if(image.empty()){
        return -1;
    }

    Mat padded;
    int m=getOptimalDFTSize(image.rows);
    int n=getOptimalDFTSize(image.cols);
   
    copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0)); // 复制图像并且制作边界。

    Mat planes[]={Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F)};

    Mat complexI;

    merge(planes,2,complexI);  // Add to the expanded another plane with zeros

    dft(complexI,complexI);// this way the result may fit in the source matrix
     // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI,planes);// planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0],planes[1],planes[0]);// planes[0] = magnitude
    Mat magI =planes[0];
    magI+=Scalar::all(1);
    log(magI,magI);
    
     // crop the spectrum, if it has an odd number of rows or columns
    magI=magI(Rect(0,0,magI.cols & -2,magI.rows & -2));
    
    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    //从magI中取部分图像(左上角，右下角)
    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    //q0和q3交换
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    //q1和q2交换
    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)  
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //规范化
    normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
     // viewable image form (float between values 0 and 1).

    imshow("Input image",image);
    imshow("spectrum magnitude", magI);
    waitKey();
    return 0;
}

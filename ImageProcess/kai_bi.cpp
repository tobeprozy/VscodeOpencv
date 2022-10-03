#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include<iostream>
using namespace std;
using namespace cv;
Mat src, dst;
int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;


const char* window_name = "Morphology Transformations Demo";
void Morphology_Operations( int, void* );

int main(int argc, char const *argv[])
{
    /* code */
    string imageName("pic/wen.png");
    if(argc > 1){
        imageName=argv[1];
    }
    src=imread(imageName,IMREAD_COLOR);
    if(src.empty()) return -1;

    namedWindow(window_name,WINDOW_AUTOSIZE);
    //开运算:先腐蚀后膨胀：dilate(erode(src,element))
    //闭运算：先膨胀后腐蚀：erode(dilate(src,element))
    //形态梯度：膨胀图与腐蚀图之差：dilate(src,element)-erode(src,element)
    //顶帽：原图与开运算之差：src-open(src,element)
    //黑帽：闭运算与原图之差：close(src,element)-src
    createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name,
    &morph_operator,max_operator,Morphology_Operations);
    createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
                  &morph_elem, max_elem,
                  Morphology_Operations);
    createTrackbar( "Kernel size:\n 2n +1", window_name,
                  &morph_size, max_kernel_size,
                  Morphology_Operations );
    Morphology_Operations(0,0);
    waitKey(0);

    return 0;
}

void Morphology_Operations(int,void *){
    int operation=morph_operator+2;
    Mat element=getStructuringElement(morph_elem,Size(2*morph_size+1,2*morph_size+1),Point(morph_size,morph_size));
    morphologyEx(src,dst,operation,element);
    imshow(window_name,dst);
}

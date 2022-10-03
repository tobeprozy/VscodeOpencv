#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include<iostream>
using namespace std;
using namespace cv;
const char* window_name = "Pyramids Demo";
Mat src,dst,tmp;
int main(int argc, char const *argv[])
{
    /* code */
    printf( "\n Zoom In-Out demo  \n " );
    printf( "------------------ \n" );
    printf( " * [u] -> Zoom in  \n" );
    printf( " * [d] -> Zoom out \n" );
    printf( " * [ESC] -> Close program \n \n" );
    const char *filename=argc>2?argv[1]:"pic/chicky_512.png";
    src=imread(filename);
    if(src.empty()) return -1;

    tmp=src;
    dst=tmp;
    imshow(window_name,dst);
    for(;;){
        char c=(char)waitKey(0);
        if(c=='q') break;
        if(c=='u'){
            pyrUp(tmp,dst,Size(tmp.cols*2,tmp.rows*2));
            printf( "** Zoom In: Image x 2 \n" );
        }else if(c=='d'){
            pyrDown(tmp,dst,Size(tmp.cols/2,tmp.rows/2));
            printf( "** Zoom Out: Image / 2 \n" );
        }
        imshow(window_name,dst);
        tmp=dst;
    }
    return 0;
}


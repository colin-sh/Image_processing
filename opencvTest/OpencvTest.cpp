
/*실습 1
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main()
{
IplImage *image = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);

cvNamedWindow("Test Viewer", CV_WINDOW_AUTOSIZE); // 그림을 띄울 창 만들기 ( 그림에 맞게 Auto 창 )
cvShowImage("Test Viewer", image); // 아까 불러왔던 Image를 연결 시키기

cvWaitKey();                    // Key를 누르면 꺼지기
cvDestroyWindow("Test Viewer"); // 종료하기
cvReleaseImage(&image);         //

// 색깔 바꾸는 법은 2가지가 존재합니다.
// 1. cvScalar s; s.val[0] = 255
// 2. cvGet2D or cvSet2D(image,y,x); ==> x,y 위치가 다르니깐 시험내기 좋겠죠?????

return 0;
}
*/
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

#define SUM_CONSTANT 50

int main()
{
	int i, j;
	// GRAY SCALE로 바꾸기
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *sumimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color를 바꾸기 위한 변수
	CvScalar pixelValue, temp;

	// 각 픽셀마다 색 바꾸기 
	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);

			// (j,i)위치 pixel 값 + 50을 했을 때 
			// 255 넘어가면 최댓값 255로 바꾸고 Set하기
			if (pixelValue.val[0] + SUM_CONSTANT >= 255)
			{
				temp.val[0] = 255;
				cvSet2D(sumimage, i, j, temp);
			}
			// 255 안넘어가면 그냥 그대로 넣어주기
			else {
				temp.val[0] = pixelValue.val[0] + SUM_CONSTANT;
				cvSet2D(sumimage, i, j, temp);
			}
		}
	}

	// 이건 전체 사진 픽셀 모두 바꾸는거임.
	//cvSet(sumimage, cvScalar(200,0,0)); ==> Blue  
	//cvSet(sumimage, CV_RGB(200,0,0));   ==> Red  색깔로 댐

	// 영상을 표시할 윈도우 하나 만들기 --> 없어도 되는데???
	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sum image", CV_WINDOW_AUTOSIZE);

	// 이미지 띄어주기
	cvShowImage("input image", inputimage);
	cvShowImage("sum image", sumimage);

	cvDestroyWindow("inputImage");
	cvDestroyWindow("sumImage");

	cvWaitKey(0);

	cvReleaseImage(&inputimage);
	cvReleaseImage(&sumimage);

	return 0;
}
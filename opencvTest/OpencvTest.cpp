
/*�ǽ� 1
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main()
{
IplImage *image = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);

cvNamedWindow("Test Viewer", CV_WINDOW_AUTOSIZE); // �׸��� ��� â ����� ( �׸��� �°� Auto â )
cvShowImage("Test Viewer", image); // �Ʊ� �ҷ��Դ� Image�� ���� ��Ű��

cvWaitKey();                    // Key�� ������ ������
cvDestroyWindow("Test Viewer"); // �����ϱ�
cvReleaseImage(&image);         //

// ���� �ٲٴ� ���� 2������ �����մϴ�.
// 1. cvScalar s; s.val[0] = 255
// 2. cvGet2D or cvSet2D(image,y,x); ==> x,y ��ġ�� �ٸ��ϱ� ���賻�� ������?????

return 0;
}
*/
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

#define SUM_CONSTANT 50

int main()
{
	int i, j;
	// GRAY SCALE�� �ٲٱ�
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *sumimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color�� �ٲٱ� ���� ����
	CvScalar pixelValue, temp;

	// �� �ȼ����� �� �ٲٱ� 
	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);

			// (j,i)��ġ pixel �� + 50�� ���� �� 
			// 255 �Ѿ�� �ִ� 255�� �ٲٰ� Set�ϱ�
			if (pixelValue.val[0] + SUM_CONSTANT >= 255)
			{
				temp.val[0] = 255;
				cvSet2D(sumimage, i, j, temp);
			}
			// 255 �ȳѾ�� �׳� �״�� �־��ֱ�
			else {
				temp.val[0] = pixelValue.val[0] + SUM_CONSTANT;
				cvSet2D(sumimage, i, j, temp);
			}
		}
	}

	// �̰� ��ü ���� �ȼ� ��� �ٲٴ°���.
	//cvSet(sumimage, cvScalar(200,0,0)); ==> Blue  
	//cvSet(sumimage, CV_RGB(200,0,0));   ==> Red  ����� ��

	// ������ ǥ���� ������ �ϳ� ����� --> ��� �Ǵµ�???
	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sum image", CV_WINDOW_AUTOSIZE);

	// �̹��� ����ֱ�
	cvShowImage("input image", inputimage);
	cvShowImage("sum image", sumimage);

	cvDestroyWindow("inputImage");
	cvDestroyWindow("sumImage");

	cvWaitKey(0);

	cvReleaseImage(&inputimage);
	cvReleaseImage(&sumimage);

	return 0;
}
*/

/*
//��ϴ�� �ǽ� !!
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

#define SUM_CONSTANT 50

int main()
{
	int i, j;
	// GRAY SCALE�� �ٲٱ�
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color�� �ٲٱ� ���� ����
	CvScalar pixelValue, temp;

	// �� �ȼ����� �� �ٲٱ� 
	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);
			temp.val[0] = 255 - pixelValue.val[0];
			cvSet2D(outputimage, i, j, temp);
		}
	}

	// �̰� ��ü ���� �ȼ� ��� �ٲٴ°���.
	//cvSet(sumimage, cvScalar(200,0,0)); ==> Blue  
	//cvSet(sumimage, CV_RGB(200,0,0));   ==> Red  ����� ��

	// ������ ǥ���� ������ �ϳ� ����� --> ��� �Ǵµ�???
	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	// �̹��� ����ֱ�
	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvDestroyWindow("inputImage");
	cvDestroyWindow("outputimage");

	cvWaitKey(0);

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
*/

/*
//�������� �ǽ� !!
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

#define SUM_CONSTANT 50

int main()
{
	int i, j;
	// GRAY SCALE�� �ٲٱ�
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color�� �ٲٱ� ���� ����
	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);
			temp.val[0] = pow(pixelValue.val[0], 1 / GAMMA_CONSTANT);
			if (temp.val[0] < 0) {
				temp.val[0] = 0;
				cvSet2D(outputimage, i, j, temp);
			}
			else if (temp.val[0] > 255) {
				temp.val[0] = 255;
				cvSet2D(outputimage, i, j, temp);
			}
			else {
				cvSet2D(outputimage, i, j, temp);
			}
		}
	}

	// �̰� ��ü ���� �ȼ� ��� �ٲٴ°���.
	//cvSet(sumimage, cvScalar(200,0,0)); ==> Blue  
	//cvSet(sumimage, CV_RGB(200,0,0));   ==> Red  ����� ��

	// ������ ǥ���� ������ �ϳ� ����� --> ��� �Ǵµ�???
	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	// �̹��� ����ֱ�
	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvDestroyWindow("inputImage");
	cvDestroyWindow("outputimage");

	cvWaitKey(0);

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
*/

/*
//����ȭ �ǽ� !!
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

#define BINARY_THRESHOLD 130

int main()
{
	int i, j;
	// GRAY SCALE�� �ٲٱ�
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color�� �ٲٱ� ���� ����
	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);
			
			if (pixelValue.val[0] >= BINARY_THRESHOLD) {
				temp.val[0] = 255;
				cvSet2D(outputimage, i, j, temp);
			}
			else {
				temp.val[0] = 0;
				cvSet2D(outputimage, i, j, temp);
			}
		}
	}

	// �̰� ��ü ���� �ȼ� ��� �ٲٴ°���.
	//cvSet(sumimage, cvScalar(200,0,0)); ==> Blue  
	//cvSet(sumimage, CV_RGB(200,0,0));   ==> Red  ����� ��

	// ������ ǥ���� ������ �ϳ� ����� --> ��� �Ǵµ�???
	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	// �̹��� ����ֱ�
	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvDestroyWindow("inputImage");
	cvDestroyWindow("outputimage");

	cvWaitKey(0);

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
*/

//�������� �ǽ�!!
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

#define STRESS_START_POINT 100
#define STRESS_END_POINT 150

int main()
{
	int i, j;
	// GRAY SCALE�� �ٲٱ�
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color�� �ٲٱ� ���� ����
	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {
			pixelValue = cvGet2D(inputimage, i, j);

			if (pixelValue.val[0] >= STRESS_START_POINT && pixelValue.val[0] <= STRESS_END_POINT) {
				temp.val[0] = 255;
				cvSet2D(outputimage, i, j, temp);
			}
			else {
				cvSet2D(outputimage, i, j, pixelValue);
			}
		}
	}

	// �̰� ��ü ���� �ȼ� ��� �ٲٴ°���.
	//cvSet(sumimage, cvScalar(200,0,0)); ==> Blue  
	//cvSet(sumimage, CV_RGB(200,0,0));   ==> Red  ����� ��

	// ������ ǥ���� ������ �ϳ� ����� --> ��� �Ǵµ�???
	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);

	// �̹��� ����ֱ�
	cvShowImage("input image", inputimage);
	cvShowImage("output image", outputimage);

	cvDestroyWindow("inputImage");
	cvDestroyWindow("outputimage");

	cvWaitKey(0);

	cvDestroyWindow("input image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&outputimage);

	return 0;
}
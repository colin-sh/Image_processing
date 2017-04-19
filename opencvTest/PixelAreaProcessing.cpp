/*
//������ �ǽ�
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(sum + 128));
			sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *resultImage = NULL;

	double emboMask[3][3] = { { -1., 0., 0. },{ 0., 0., 0., },{ 0.,0.,1. } };

	resultImage = ConvolutionProcess(inputImage, emboMask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", resultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&resultImage);
	cvReleaseImage(&inputImage);

}
*/

/*
//���� �ǽ�
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(sum));
			sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *resultImage = NULL;

	double emboMask[3][3] = { { 1 / 9., 1 / 9., 1 / 9. },{ 1 / 9., 1 / 9., 1 / 9., },{ 1 / 9.,1 / 9.,1 / 9. } };

	resultImage = ConvolutionProcess(inputImage, emboMask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", resultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&resultImage);
	cvReleaseImage(&inputImage);

}
*/

/*
//����þ����� �ǽ�
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(sum));
			sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *resultImage = NULL;

	double emboMask[3][3] = { { 1 / 16., 1 / 8., 1 / 16. },{ 1 / 8., 1 / 4., 1 / 8., },{ 1 / 16.,1 / 8.,1 / 16. } };

	resultImage = ConvolutionProcess(inputImage, emboMask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", resultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&resultImage);
	cvReleaseImage(&inputImage);

}
*/

/*
//������ �ǽ�
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(sum));
			sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *resultImage_1 = NULL;
	IplImage *resultImage_2 = NULL;

	double Mask_1[3][3] = { { -1., -1., -1. },{ -1., 9., -1., },{ -1.,-1.,-1. } };
	double Mask_2[3][3] = { { 0., -1., 0. },{ -1., 5., -1., },{ 0.,-1.,0. } };

	resultImage_1 = ConvolutionProcess(inputImage, Mask_1);
	resultImage_2 = ConvolutionProcess(inputImage, Mask_2);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image 1", resultImage_1);
	cvShowImage("Result Image 2", resultImage_2);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&resultImage_1);
	cvReleaseImage(&resultImage_2);
	cvReleaseImage(&inputImage);

}
*/

/*
//������ ��� ���� ó��
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(sum));
			sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *resultImage = NULL;

	double HPF_Mask[3][3] = { { -1/9., -1/9., -1/9. },{ -1/9., 8/9., -1/9., },{ -1/9.,-1/9.,-1/9. } };

	resultImage = ConvolutionProcess(inputImage, HPF_Mask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", resultImage);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&resultImage);
	cvReleaseImage(&inputImage);

}
*/
/*
//������ ��� ���� ó��
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(sum));
			sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *tempImage = NULL;
	IplImage *resultImage_1 = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage *resultImage_2 = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	double LPF_Mask[3][3] = { { 1 / 9., 1 / 9., 1 / 9. },{ 1 / 9., 1 / 9., 1 / 9., },{ 1 / 9.,1 / 9.,1 / 9. } };
	int i,j;
	CvScalar inputPixel, tempPixel;

	tempImage = ConvolutionProcess(inputImage, LPF_Mask);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			inputPixel = cvGet2D(inputImage, i, j);
			tempPixel = cvGet2D(tempImage, i, j);

			//UnSharp Masking = (������) - (������ ��� ���͸� ��� ����)
			cvSet2D(resultImage_1, i, j, cvScalar(inputPixel.val[0] - tempPixel.val[0]));
			//������� �غκ� ���� ��«
		}
	}

	resultImage_1 = ConvolutionProcess(inputImage, Mask_1);
	resultImage_2 = ConvolutionProcess(inputImage, Mask_2);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image 1", resultImage_1);
	cvShowImage("Result Image 2", resultImage_2);

	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&resultImage_1);
	cvReleaseImage(&resultImage_2);
	cvReleaseImage(&inputImage);

}
*/
/*
//�ι��� �ڵ�
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);
	// IPL_DEPTH_8U - 8 ��Ʈ�� RGB DEPTH ǥ��

	int i, j, n, m;
	double sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // ��� �Ǵ���??

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {                       // Mask�� �����ϱ�
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(sum)); // 128 ���ϸ� ������
			sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}

int main() {
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *sumImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage *rowImage = NULL;
	IplImage *colImage = NULL;

	double rowMask[3][3] = { { -1,0,0 },{ 0,1,0 },{ 0,0,0 } };
	double colMask[3][3] = { { 0,0,-1 },{ 0,1,0 },{ 0,0,0 } };

	int i, j;
	CvScalar horizontemp, vertical;

	rowImage = ConvolutionProcess(inputImage, rowMask);
	colImage = ConvolutionProcess(inputImage, colMask);

	cvOr(rowImage, colImage, sumImage);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", rowImage);
	cvShowImage("Result Image2", colImage);
	cvShowImage("sumImage", sumImage);

	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&sumImage);
	cvReleaseImage(&rowImage);
	cvReleaseImage(&colImage);
	cvReleaseImage(&inputImage);

}
*/
/*
//ĳ�� ���� ����
#include <opencv\cv.h>
#include <opencv\highgui.h>

#define LOW_THRESHOLD 30
#define HIGH_THRESHOLD 30*2.5

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *cannyImage_1 = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	cvCanny(inputImage, cannyImage_1, LOW_THRESHOLD, HIGH_THRESHOLD);


	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", cannyImage_1);

	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&cannyImage_1);
	cvReleaseImage(&inputImage);
}
*/
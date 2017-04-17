/*
//�̵��� ����ó��
#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *ConvolutionProcess(IplImage *inputImage, double Mask[3][3]);

int main() {
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *resultImage_1 = NULL;
	IplImage *resultImage_2 = NULL;

	double verticalMask[3][3] = { { 0,0,0 },{ -1,1,0 },{ 0,0,0 } };
	double horizonMask[3][3] = { { 0,-1,0 },{ 0,1,0 },{ 0,0,0 } };

	resultImage_1 = ConvolutionProcess(inputImage, verticalMask);
	resultImage_2 = ConvolutionProcess(inputImage, horizonMask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", resultImage_1);
	cvShowImage("Result Image2", resultImage_2);

	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&resultImage_1);
	cvReleaseImage(&resultImage_2);
	cvReleaseImage(&inputImage);

}

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
*/


/*
//���翬���ڱ��

#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage *HomogenProcess(IplImage *inputImage);
double ABS(double x);

int main() {
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *resultImage_1 = NULL;

	resultImage_1 = HomogenProcess(inputImage);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", resultImage_1);

	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&resultImage_1);
	cvReleaseImage(&inputImage);

}

IplImage *HomogenProcess(IplImage *inputImage) {
	IplImage *tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);
	// IPL_DEPTH_8U - 8 ��Ʈ�� RGB DEPTH ǥ��

	int i, j, n, m;
	double max = 0.0, temp;
	CvScalar tempScalar, ceterScalar;

	cvSetZero(tempinputImage); // ��� �Ǵ���??

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			ceterScalar = cvGet2D(tempinputImage, i + 1, j + 1);
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);//�̿���
					temp = ABS(ceterScalar.val[0] - tempScalar.val[0]);
					if (max < temp)
						max = temp;
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(max)); // 128 ���ϸ� ������
			max = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);
	return outputImage;
}
double ABS(double x) {
	if (x >= 0)
		return x;
	else
		return -x;
}
*/
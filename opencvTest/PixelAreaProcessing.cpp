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
/*
Roadimage(�ҷ��� �̹���, ����(Į������ �׷�������))
Createimage(������ �̹����� ũ��,depth(�׷��̽������� ���Ʈ�� 8bit 0~255), ä��(�������)
CVGet2D(�̹����� ������, Y��, X��)
CVSet2D(�̹����� ������, Y��, X��,cv��Į��)
cvScalar(B,G,R)
Cv_RGB(r,g,b)
cvSet(�̹���, cv��Į��)
*/





//�������� 1��
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

#define HISTGRAM_SIZE 256
#define LOW 0
#define HIGH 255

void Show_histogram(IplImage *img, char *imgWindowName, char * histogramWindowName) {

	int i, j, value;
	IplImage *inputImage = img;
	IplImage *histogramImage = cvCreateImage(cvSize(HISTGRAM_SIZE, HISTGRAM_SIZE + 20), IPL_DEPTH_8U, 1);

	CvScalar temp;

	double HIST[HISTGRAM_SIZE];
	unsigned char scale_HIST[HISTGRAM_SIZE];
	double MAX, MIN, DIF;

	//�����丣�׷� �迭 �ʱ�ȭ
	for (i = 0; i < HISTGRAM_SIZE; i++)
		HIST[i] = LOW;

	//�󵵼� ����
	for (i = 0; i<inputImage->height; i++)
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}

	//����ȭ�� ���� �ִ� �ּҰ� ���ϱ�
	MAX = HIST[0];
	MIN = HIST[0];

	for (i = 0; i < HISTGRAM_SIZE; i++) {
		if (HIST[i] > MAX)
			MAX = HIST[i];
		if (HIST[i] < MIN)
			MIN = HIST[i];
	}
	DIF = MAX - MIN;

	//�󵵼��� �� ��Ÿ���⿣ 256*256 size�� �� �Ѿ����
	//������� HIST[100]�� 2500���� ���� --> 256���� ���������
	for (i = 0; i<HISTGRAM_SIZE; i++)
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN)* HIGH / DIF);

	cvSet(histogramImage, cvScalar(255));

	//������׷��� ���� ���������� ���
	for (i = 0; i < HISTGRAM_SIZE; i++)
		for (j = 0; j < scale_HIST[i]; j++)
			cvSet2D(histogramImage, HISTGRAM_SIZE - j - 1, i, cvScalar(0));

	//�Ʒ� �κп� ������׷��� ���� ǥ��
	for (i = HISTGRAM_SIZE + 5; i < HISTGRAM_SIZE + 20; i++)
		for (j = 0; j < HISTGRAM_SIZE; j++)
			cvSet2D(histogramImage, i, j, cvScalar(j));

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);

}

int main() {
	int i, j;
	// GRAY SCALE�� �ٲٱ�
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage *sword = cvLoadImage("Funny_Barnstar.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage *outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color�� �ٲٱ� ���� ����
	CvScalar pixelValue, temp;

	for (i = 0; i < inputimage->height; i++) {
		for (j = 0; j < inputimage->width; j++) {

			pixelValue = cvGet2D(sword, i, j);

			if (pixelValue.val[0] < 240) {
				temp = cvGet2D(sword, i, j);
				cvSet2D(outputimage, i, j, temp);
			}
			else {
				temp = cvGet2D(inputimage, i, j);
				cvSet2D(outputimage, i, j, temp);
			}
		}
	}

	Show_histogram(inputimage, "Input Image", "input histogram");
	Show_histogram(sword, "sword Image", "sword histogram");
	Show_histogram(outputimage, "output Image", "output histogram");

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sword image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("ouput image", CV_WINDOW_AUTOSIZE);

	cvShowImage("input image", inputimage);
	cvShowImage("sword image", sword);
	cvShowImage("ouput image", outputimage);

	cvWaitKey(0);

	cvDestroyWindow("input image");
	cvDestroyWindow("sword image");
	cvDestroyWindow("output image");

	cvReleaseImage(&inputimage);
	cvReleaseImage(&sword);
	cvReleaseImage(&outputimage);

	return 0;
}


//��Ȱȭ
#include <opencv\cv.h>
#include <opencv\highgui.h>

#define LOW 0
#define HIGH 255
#define HISTGRAM_SIZE 256

#define ENDIN_LOW 30
#define ENDIN_HIGH 225

void Show_histogram(IplImage *img, char *imgWindowName, char * histogramWindowName);
int main() {

	int i, j, value;
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *equalImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	CvScalar temp;

	double HIST[HISTGRAM_SIZE];
	double sum_of_HIST[HISTGRAM_SIZE];
	double SUM = 0.0;

	//�����丣�׷� �迭 �ʱ�ȭ
	for (i = 0; i < HISTGRAM_SIZE; i++)
		HIST[i] = LOW;

	//1�ܰ� �󵵼�
	for (i = 0; i < inputImage->height; i++)
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}

	//2�ܰ� ������
	for (i = 0; i < HISTGRAM_SIZE; i++) {
		SUM = SUM + HIST[i];
		sum_of_HIST[i] = SUM;
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			cvSet2D(equalImage, i, j, cvScalar(sum_of_HIST[(int)temp.val[0]] * HIGH / (inputImage->height * inputImage->width)));
		}
	}

	Show_histogram(inputImage, "input Image", "input histogram");
	Show_histogram(equalImage, "equal Image", "Equal histogram");

	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&equalImage);
	cvReleaseImage(&inputImage);

	return 0;
}

void Show_histogram(IplImage *img, char *imgWindowName, char * histogramWindowName) {

	int i, j, value;
	IplImage *inputImage = img;
	IplImage *histogramImage = cvCreateImage(cvSize(HISTGRAM_SIZE, HISTGRAM_SIZE + 20), IPL_DEPTH_8U, 1);

	CvScalar temp;

	double HIST[HISTGRAM_SIZE];
	unsigned char scale_HIST[HISTGRAM_SIZE];
	double MAX, MIN, DIF;

	//�����丣�׷� �迭 �ʱ�ȭ
	for (i = 0; i < HISTGRAM_SIZE; i++)
		HIST[i] = LOW;

	//�󵵼� ����
	for (i = 0; i<inputImage->height; i++)
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}

	//����ȭ�� ���� �ִ� �ּҰ� ���ϱ�
	MAX = HIST[0];
	MIN = HIST[0];

	for (i = 0; i < HISTGRAM_SIZE; i++) {
		if (HIST[i] > MAX) MAX = HIST[i];
		if (HIST[i] < MIN) MIN = HIST[i];
	}
	DIF = MAX - MIN;

	//�󵵼��� �� ��Ÿ���⿣ 256*256 size�� �� �Ѿ����
	//������� HIST[100]�� 2500���� ���� --> 256���� ���������
	for (i = 0; i<HISTGRAM_SIZE; i++)
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN)* HIGH / DIF);

	cvSet(histogramImage, cvScalar(255));

	//������׷��� ���� ���������� ���
	for (i = 0; i < HISTGRAM_SIZE; i++)
		for (j = 0; j < scale_HIST[i]; j++)
			cvSet2D(histogramImage, HISTGRAM_SIZE - j - 1, i, cvScalar(0));

	//�Ʒ� �κп� ������׷��� ���� ǥ��
	for (i = HISTGRAM_SIZE + 5; i < HISTGRAM_SIZE + 20; i++)
		for (j = 0; j < HISTGRAM_SIZE; j++)
			cvSet2D(histogramImage, i, j, cvScalar(j));

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);

}
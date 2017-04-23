/*
Roadimage(불러올 이미지, 색상(칼라인지 그레이인지))
Createimage(생성할 이미지의 크기,depth(그레이스케일이 몇비트냐 8bit 0~255), 채널(허용색상수)
CVGet2D(이미지의 포인터, Y축, X축)
CVSet2D(이미지의 포인터, Y축, X축,cv스칼라값)
cvScalar(B,G,R)
Cv_RGB(r,g,b)
cvSet(이미지, cv스칼라)
*/





//도전과제 1번
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

	//히스토르그램 배열 초기화
	for (i = 0; i < HISTGRAM_SIZE; i++)
		HIST[i] = LOW;

	//빈도수 조사
	for (i = 0; i<inputImage->height; i++)
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}

	//정규화를 위한 최대 최소값 구하기
	MAX = HIST[0];
	MIN = HIST[0];

	for (i = 0; i < HISTGRAM_SIZE; i++) {
		if (HIST[i] > MAX)
			MAX = HIST[i];
		if (HIST[i] < MIN)
			MIN = HIST[i];
	}
	DIF = MAX - MIN;

	//빈도수를 다 나타내기엔 256*256 size를 걍 넘어버림
	//예를들어 HIST[100]은 2500개가 있음 --> 256으로 나눠줘야해
	for (i = 0; i<HISTGRAM_SIZE; i++)
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN)* HIGH / DIF);

	cvSet(histogramImage, cvScalar(255));

	//히스토그램의 값은 검은색으로 출력
	for (i = 0; i < HISTGRAM_SIZE; i++)
		for (j = 0; j < scale_HIST[i]; j++)
			cvSet2D(histogramImage, HISTGRAM_SIZE - j - 1, i, cvScalar(0));

	//아래 부분에 히스토그램의 색을 표시
	for (i = HISTGRAM_SIZE + 5; i < HISTGRAM_SIZE + 20; i++)
		for (j = 0; j < HISTGRAM_SIZE; j++)
			cvSet2D(histogramImage, i, j, cvScalar(j));

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);

}

int main() {
	int i, j;
	// GRAY SCALE로 바꾸기
	IplImage *inputimage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage *sword = cvLoadImage("Funny_Barnstar.jpg", CV_LOAD_IMAGE_COLOR);
	IplImage *outputimage = cvCreateImage(cvGetSize(inputimage), inputimage->depth, inputimage->nChannels);

	// Color를 바꾸기 위한 변수
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


//평활화
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

	//히스토르그램 배열 초기화
	for (i = 0; i < HISTGRAM_SIZE; i++)
		HIST[i] = LOW;

	//1단계 빈도수
	for (i = 0; i < inputImage->height; i++)
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}

	//2단계 누적합
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

	//히스토르그램 배열 초기화
	for (i = 0; i < HISTGRAM_SIZE; i++)
		HIST[i] = LOW;

	//빈도수 조사
	for (i = 0; i<inputImage->height; i++)
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}

	//정규화를 위한 최대 최소값 구하기
	MAX = HIST[0];
	MIN = HIST[0];

	for (i = 0; i < HISTGRAM_SIZE; i++) {
		if (HIST[i] > MAX) MAX = HIST[i];
		if (HIST[i] < MIN) MIN = HIST[i];
	}
	DIF = MAX - MIN;

	//빈도수를 다 나타내기엔 256*256 size를 걍 넘어버림
	//예를들어 HIST[100]은 2500개가 있음 --> 256으로 나눠줘야해
	for (i = 0; i<HISTGRAM_SIZE; i++)
		scale_HIST[i] = (unsigned char)((HIST[i] - MIN)* HIGH / DIF);

	cvSet(histogramImage, cvScalar(255));

	//히스토그램의 값은 검은색으로 출력
	for (i = 0; i < HISTGRAM_SIZE; i++)
		for (j = 0; j < scale_HIST[i]; j++)
			cvSet2D(histogramImage, HISTGRAM_SIZE - j - 1, i, cvScalar(0));

	//아래 부분에 히스토그램의 색을 표시
	for (i = HISTGRAM_SIZE + 5; i < HISTGRAM_SIZE + 20; i++)
		for (j = 0; j < HISTGRAM_SIZE; j++)
			cvSet2D(histogramImage, i, j, cvScalar(j));

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);

}
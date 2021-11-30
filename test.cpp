//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
#include "CompVisionModules.h"
#include "ShapeDetector.h"
#include "DocumentScanner.h"
#include "ProcessImage.h"
#include "FaceDetector.h"
#include "BodyDetector.h"
#include "ColorDetector.h"
using namespace cv;
using namespace std;


int main()
{
	//string path = "Resources/test.png";
	//Mat img = imread(path);
	//imshow("Image", img);
	//string path = "Resources/shapes4.png";
	//ShapeDetector detector(path);

	//string path = "Resources/paper.jpg";
	//DocumentScanner docScanner(520, 796);
	//docScanner.DocScanner(path);

	FaceDetector facedect;
	string path = "Resources/faces-1.jpg";
	BodyDetector bodydetect;

	string path_color = "Resources/car.jpg";
	Mat img_color = imread(path_color); //Mat - matrix datatype
	ColorDetector color_detect;
	color_detect.detectColors(img_color);
	//imshow("Image", facedect.DetectFaceImage(imread(path)));
	//waitKey(0);
	//VideoCapture cap(0);
	//Mat img;
	//while (true)
	//{
	//	cap.read(img);
	//	//facedect.DetectEyes(img, true);
	//	bodydetect.DetectUpperBody(img);
	//	imshow("Image", img);
	//	if (waitKey(30) == 27) { //wait time for each frame is 30 milliseconds//
	//		break;
	//	}
	//}

	return 0;
}
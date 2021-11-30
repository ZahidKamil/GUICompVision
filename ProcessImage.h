#pragma once
#include "CompVisionModules.h"

class ProcessImage
{
public:
	Mat getGrayImg(Mat img);
	Mat getBlurImg(Mat imgInput, int kernel_sizeX, int kernel_sizeY);
	Mat getDilatedImg(Mat imgInput, int MORPH_SHAPE, Size ksize);
	Mat getCannyImg(Mat img, int thresh1, int thresh2);
	Mat getErodedImg(Mat imgInput, int MORPH_SHAPE, Size ksize);
	//Mat getContours(Mat img);
	//Mat getCroppedImg(Mat img);
	//Mat drawContours(Mat img);
	//void putText();
	//void BoxColor();
	//void boxType();


public:
	Mat img;
};


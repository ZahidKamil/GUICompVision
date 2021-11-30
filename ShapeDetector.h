#pragma once
#include "CompVisionModules.h"
#include "ProcessImage.h"

class ShapeDetector
{
public:
	void getContours(Mat imgDil, Mat img);
	void findShapes(Mat &img);
private:
	ProcessImage imgProcessor;
};

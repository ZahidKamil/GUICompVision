#pragma once
#include "CompVisionModules.h"
#include "ProcessImage.h"

class ColorDetector
{
private:
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;
	Mat imgHSV;
	Mat mask;
public: 
	void detectColors(Mat &img);
};


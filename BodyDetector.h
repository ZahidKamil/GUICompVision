#pragma once

#include "CompVisionModules.h"
#include "ProcessImage.h"


class BodyDetector
{
private:
	string upperbody_hc = "Resources/HaarCascades/haarcascade_upperbody.xml";
	string fullbody_hc = "Resources/HaarCascades/haarcascade_fullbody.xml";
	string lowerbody_hc = "Resources/HaarCascades/haarcascade_lowerbody.xml";
	CascadeClassifier upper_body_cascade, lower_body_cascade, full_body_cascade;
	ProcessImage improcessor;
	vector<Rect> bodies;

public:
	BodyDetector();
	Mat DetectUpperBody(Mat& img);
	Mat DetectLowerBody(Mat& img);
	Mat DetectFullBody(Mat& img);
};


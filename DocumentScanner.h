#pragma once
#include "CompVisionModules.h"
#include "ProcessImage.h"

class DocumentScanner
{
private:
	Mat img;
	float w = 0.0;
	float h = 0.0;
	vector<Point> points;
	ProcessImage imgProcessor;
	Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWarp, imgCrop;
	vector<Point> initialPoints, docPoints;
public:
	DocumentScanner(float w, float h);
	Mat preProcessing(Mat img);
	vector<Point> getContours(Mat img);
	void drawPoints(vector<Point> points, Scalar color);
	vector<Point> reorder(vector<Point> points);
	Mat getWarp(Mat img, vector<Point> points, float w, float h);
	void DocScanner(string path);
};

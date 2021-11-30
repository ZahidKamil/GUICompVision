#pragma once
#include "CompVisionModules.h"
#include "ProcessImage.h"

class FaceDetector
{
private:
	string frontal_face_hc = "Resources/HaarCascades/haarcascade_frontalface_default.xml";
	string eye_hc = "Resources/HaarCascades/haarcascade_eye.xml";
	string eye_glasses_hc = "Resources/HaarCascades/haarcascade_eye_tree_eyeglasses.xml";
	CascadeClassifier face_cascade, eye_cascade, eye_glasses_cascade;
	Mat imgGray;
	ProcessImage improcessor;
	vector<Rect> faces;
public:
	FaceDetector();
	Mat DetectFaceImage(Mat img);
	Mat DetectFaceVideo(Mat& img);
	Mat DetectEyes(Mat& img, bool eye_tree_glasses);
};

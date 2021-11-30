#include "CompVisionModules.h"
#include "ProcessImage.h"

Mat ProcessImage::getGrayImg(Mat imgInput)
{
	cvtColor(imgInput, img, COLOR_BGR2GRAY);
	return img;

}

Mat ProcessImage::getBlurImg(Mat imgInput, int kernel_sizeX, int kernel_sizeY)
{
	GaussianBlur(imgInput, img, Size(kernel_sizeX, kernel_sizeY), 3, 0);
	return img;
}

Mat ProcessImage::getDilatedImg(Mat imgInput, int MORPH_SHAPE, Size ksize)
{
	Mat kernel = getStructuringElement(MORPH_SHAPE, ksize);
	dilate(imgInput, img, kernel);
	return img;
}

Mat ProcessImage::getCannyImg(Mat imgInput, int thresh1, int thresh2)
{
	Canny(imgInput, img, thresh1, thresh2);
	return img;
}

Mat ProcessImage::getErodedImg(Mat imgInput, int MORPH_SHAPE, Size ksize)
{
	Mat kernel = getStructuringElement(MORPH_SHAPE, ksize);
	erode(imgInput, img, kernel);
	return img;

}


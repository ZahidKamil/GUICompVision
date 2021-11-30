#include "ColorDetector.h"

void ColorDetector::detectColors(Mat &img)
{
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Minimum", "Trackbars", &hmin, 179);
	createTrackbar("Hue Maximum", "Trackbars", &hmax, 179);
	createTrackbar("Sat Minimum", "Trackbars", &smin, 255);
	createTrackbar("Sat Maximum", "Trackbars", &smax, 255);
	createTrackbar("Val Minimum", "Trackbars", &vmin, 255);
	createTrackbar("Val Maximum", "Trackbars", &vmax, 255);

	while (true)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Mask", mask);
		waitKey(1); // 0 for infinity
	}
}
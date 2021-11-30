
#include "DocumentScanner.h"




DocumentScanner::DocumentScanner(float w, float h)
{
	this->w = w;
	this->h = h;
}

Mat DocumentScanner::preProcessing(Mat img)
{
	//cvtColor(img, imgGray, COLOR_BGR2GRAY);
	imgGray = imgProcessor.getGrayImg(img);
	//GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	imgBlur = imgProcessor.getBlurImg(imgGray, 3, 3);
	//Canny(imgBlur, imgCanny, 25, 75);
	imgCanny = imgProcessor.getCannyImg(imgBlur, 25, 75);
	//Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate(imgCanny, imgDil, kernel);
	imgDil = imgProcessor.getDilatedImg(imgCanny, MORPH_RECT, Size(3, 3));
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}

vector<Point> DocumentScanner::getContours(Mat image)
{

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	
	//Initially maxArea will be 0, then we keep updating the area as it increases in size.
	//The paper will have the max area.
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl;



		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			//Finding the minimum number of vertices of a Polygon given the points of a contour. Reduces the number of coordinate points.
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {

				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				points = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };
				maxArea = area;
			}
			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);
			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return points;
}

void DocumentScanner::drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		cout << "points: " << points[i] << endl;
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

vector<Point> DocumentScanner::reorder(vector<Point> points)
{
	vector<Point> newPoints;

	vector<int> sumPoints, subPoints;
	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //0 - top-left
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1 - bottom-left
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2 - top-right
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3 - bottom-right

	return newPoints;
}

Mat DocumentScanner::getWarp(Mat img, vector<Point> points, float w, float h)
{
	Point2f source[4] = { points[0], points[1], points[2], points[3] };
	Point2f destination[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f, h}, {w,h} };


	//USing transformation matrix
	Mat matrix = getPerspectiveTransform(source, destination);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}

void DocumentScanner::DocScanner(string path)
{
	imgOriginal = imread(path);
	//Convert to grayscale, add blue and then use canny edge detector to find all edges. Once the edges are found we know the coordinates of the paper.
	//Based on the coordinates we can extract the 4 corners of the paper. Then we can warp the image to get the top view so that it looks scanned.

	//Preprocessing

	// Preprpcessing - Step 1 
	imgThre = preProcessing(imgOriginal);

	// Get Contours - Biggest  - Step 2
	initialPoints = getContours(imgThre);
	cout << "intialPoints " << initialPoints << endl;
	//drawPoints(initialPoints, Scalar(0, 0, 255));
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(0, 255, 0));

	//Warp
	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//Crop
	int cropVal = 5;
	Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal)); //(x_coordinate of top-left, y-coordinate of top-right, width, height)
	imgCrop = imgWarp(roi);
	imshow("Image", imgOriginal);
	imshow("Image Dilation", imgThre);
	imshow("Image Warp", imgWarp);
	imshow("Image Crop", imgCrop);
	waitKey(0);
}

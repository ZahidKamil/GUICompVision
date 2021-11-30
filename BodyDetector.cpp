#include "BodyDetector.h"

BodyDetector::BodyDetector()
{
    lower_body_cascade.load(lowerbody_hc);
    upper_body_cascade.load(upperbody_hc);
    full_body_cascade.load(fullbody_hc);
}

Mat BodyDetector::DetectLowerBody(Mat& img)
{
	if (!lower_body_cascade.load(lowerbody_hc)) { printf("--(!)Error loading\n");};
    Mat frame_gray;

    frame_gray = improcessor.getGrayImg(img);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    lower_body_cascade.detectMultiScale(frame_gray, bodies, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (size_t i = 0; i < bodies.size(); i++)
    {
        rectangle(img, bodies[i], Scalar(255, 0, 255));
    }

    return img;
}

Mat BodyDetector::DetectUpperBody(Mat& img)
{
    if (!upper_body_cascade.load(upperbody_hc)) { printf("--(!)Error loading\n"); };
    Mat frame_gray;

    frame_gray = improcessor.getGrayImg(img);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    upper_body_cascade.detectMultiScale(frame_gray, bodies, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (size_t i = 0; i < bodies.size(); i++)
    {
        rectangle(img, bodies[i], Scalar(255, 0, 255));
    }

    return img;

}


Mat BodyDetector::DetectFullBody(Mat& img)
{
    Mat frame_gray;
    if (!full_body_cascade.load(fullbody_hc)) { printf("--(!)Error loading\n"); };
    frame_gray = improcessor.getGrayImg(img);
    equalizeHist(frame_gray, frame_gray);
    //-- detect body */
    full_body_cascade.detectMultiScale(frame_gray, bodies, 1.1, 2, 18 | 9, Size(3, 7));
    for (int j = 0; j < bodies.size(); j++)
    {
        Point center(bodies[j].x + bodies[j].width * 0.5, bodies[j].y + +bodies[j].height * 0.5);
        ellipse(img, center, Size(bodies[j].width * 0.5, bodies[j].height * 0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
    }

    return img;
}

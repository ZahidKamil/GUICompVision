#include "FaceDetector.h"


FaceDetector::FaceDetector()
{
	face_cascade.load(frontal_face_hc);
	eye_cascade.load(eye_hc);
	eye_glasses_cascade.load(eye_glasses_hc);
}


Mat FaceDetector::DetectFaceImage(Mat img)
{
	if (face_cascade.empty())
	{
		cout << "XML file not loaded" << endl;
	}

	vector<Rect> faces;
	// scale factor - 1.1 defines how much the image size is reduced to scale to better detect faces. 
	// reducing the size by 10% thereby increasing the chance that a face is found. https://stackoverflow.com/questions/36218385/parameters-of-detectmultiscale-in-opencv-using-python

	face_cascade.detectMultiScale(img, faces, 1.5, 3);
	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

	return img;

}

Mat FaceDetector::DetectFaceVideo(Mat& img)
{
	imgGray = improcessor.getGrayImg(img);
	equalizeHist(imgGray, imgGray);

	face_cascade.detectMultiScale(imgGray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	//face_cascade.detectMultiScale(imgGray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++) { //for locating the face
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(img, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
		Mat faceROI = imgGray(faces[i]);//Storing face in the matrix//

	}

	return img;

}

Mat FaceDetector::DetectEyes(Mat& img, bool eye_tree_glasses)
{
	imgGray = improcessor.getGrayImg(img);
	equalizeHist(imgGray, imgGray);
	if (eye_tree_glasses)
	{
		eye_glasses_cascade.detectMultiScale(imgGray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t i = 0; i < faces.size(); i++) { //for locating the face
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(img, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
			Mat faceROI = imgGray(faces[i]);//Storing face in the matrix//

		}
	}
	else
	{
		face_cascade.detectMultiScale(imgGray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));


		for (size_t i = 0; i < faces.size(); i++) { //for locating the face
			//Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			//ellipse(img, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
			Mat faceROI = imgGray(faces[i]);//Storing face in the matrix//

			std::vector<Rect> eyes;
			eye_cascade.detectMultiScale(faceROI, eyes);

			//eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
				int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
				circle(img, eye_center, radius, Scalar(255, 0, 0), 4);
			}
		}
	}
	

	return img;

}




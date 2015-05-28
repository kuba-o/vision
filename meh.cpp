#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{	



	Mat base = imread("/home/kuba/Documents/vision/Photos/n/1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2, img3, img4, lastImg;
	String destination = "/home/kuba/Documents/vision/Photos/n/";
	String destiny = "/home/kuba/Documents/vision/Photos/n/droga.jpg";
	lastImg = imread(destiny, CV_LOAD_IMAGE_COLOR);
	img2 = imread(destiny, CV_LOAD_IMAGE_GRAYSCALE);
	addWeighted(base, 1, img2, -1, 0, img3);
	namedWindow("albonie", CV_WINDOW_AUTOSIZE);
	GaussianBlur( img3, img4, Size( 35, 35 ), 0, 0 );
	threshold(img4, lastImg, 3, 255,0);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(lastImg,contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	cout<<contours.size()<<endl;

	Scalar kolor = Scalar(0, 0, 255);
	Mat drawing = Mat::zeros(lastImg.size(),CV_8UC3);
	for(int i = 0; i < contours.size(); i++) {
		drawContours(drawing, contours,i,kolor,2,8,hierarchy, 0,Point());

	}

	vector<Moments> mu(contours.size());
	for(int i = 0;i<contours.size(); i++) {
		mu[i] = moments(contours[i],false);
		cout<<"AREA #"<<i<<": "<<mu[i].m00<<endl;
	}

	vector<Point2f> mc(contours.size());
	for(int i = 0;i<contours.size(); i++) {
		mc[i] = Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
		//putText( lastImg, "here", Point(firstWhiteX, firstWhiteY), 2, 2, Scalar(0, 255, 0), 2,2);
		if (mu[i].m00 > 50000 && mu[i].m00<100000)
			putText( drawing, "kurwa duze", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 255, 0), 2,2);
		else if (mu[i].m00>=100000)
			putText( drawing, "kurwa overload", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 255, 0), 2,2);
		else
			putText( drawing, "kurwa mniejsze", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 255, 0), 2,2);
	}

	imshow("albonie", drawing);
	
	waitKey(0);	
    return 0;
}
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
	//Mat img = imread("/home/kuba/Document/vision/Photos/")

	Mat base = imread("/home/kuba/Documents/vision/Photos/k/base.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	Mat base2 = imread("/home/kuba/Documents/vision/Photos/k/base.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat base = imread("/home/kuba/Documents/vision/Photos/n/1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2, img3, img4, lastImg;
	String destination = "/home/kuba/Documents/vision/Photos/n/";
	String destiny = "/home/kuba/Documents/vision/Photos/k/test2.JPG";
	lastImg = imread(destiny, CV_LOAD_IMAGE_GRAYSCALE);
	Mat meh = imread(destiny, CV_LOAD_IMAGE_COLOR);
	img2 = imread(destiny, CV_LOAD_IMAGE_GRAYSCALE);
	addWeighted(base, 1, img2, -1, 0, img3);
	namedWindow("albonie", CV_WINDOW_AUTOSIZE);
	GaussianBlur( img3, img4, Size( 51, 51 ), 0, 0 );
	threshold(img4, lastImg, 20, 255,0);
	imshow("lel3", meh);
	imshow("lel", lastImg);
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(lastImg,contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	cout<<contours.size()<<endl;

	Scalar kolor = Scalar(0, 0, 255);
	Mat drawing = Mat::zeros(lastImg.size(),CV_8UC3);
	for(int i = 0; i < contours.size(); i++) {
		drawContours(meh, contours,i,kolor,2,8,hierarchy, 0,Point());

	}
	imshow("lel2", meh);
	vector<Moments> mu(contours.size());
	for(int i = 0;i<contours.size(); i++) {
		mu[i] = moments(contours[i],false);
	}
	float ratio = 0;
	vector<Point2f> mc(contours.size());
	for(int i = 0;i<contours.size(); i++) {
		mc[i] = Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);

		ratio = mu[i].m00/mc[i].y;

		if ( ratio >= 100 && ratio < 160)
			putText( meh, "osobowy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 0), 2,2);
		else if (ratio >= 160 && ratio < 230)
			putText( meh, "dostawczy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 0), 2,2);
		else if (ratio >= 230)
			putText( meh, "tir", Point(mc[i].x, mc[i].y), 1, 2, Scalar(0, 0, 0), 2,2);
		else if (ratio < 100)
			putText( meh, "motor", Point(mc[i].x-50, mc[i].y), 1, 2, Scalar(0, 0, 0), 2,2);
	}
	//imshow("albonie", meh);
	//imwrite("test.png", meh);
	//imshow("albonie", meh);
	
	waitKey(0);	
    return 0;
}
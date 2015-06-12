#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int loop = 0;
int thresh;

vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

String path = "/home/kuba/Documents/vision/Photos/k/test1.JPG";
Mat base = imread("/home/kuba/Documents/vision/Photos/k/base.JPG", CV_LOAD_IMAGE_GRAYSCALE);
Mat img = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
Mat Image2, img2, img3, lastImg, drawing;
Mat pattern = imread(path, CV_LOAD_IMAGE_COLOR);

void function( int, void* ){
}

static void onMouse( int event, int x, int y, int, void* ){
	if( event == EVENT_LBUTTONDOWN ){
		createTrackbar("threshhold", "win", &thresh, 255, function );
		Image2 = pattern.clone();

		addWeighted(base, 1, img, -1, 0, img2);
		GaussianBlur( img2, img3, Size( 51, 51 ), 0, 0 );
		threshold(img3, lastImg, thresh, 255,0);
		findContours(lastImg,contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		for(int i = 0; i < contours.size(); i++) {
			drawContours(Image2, contours,i,Scalar(0, 0, 255),2,8,hierarchy, 0,Point());
		}
		vector<Moments> mu(contours.size());
		for(int i = 0;i<contours.size(); i++) {
			mu[i] = moments(contours[i],false);
		}
		float ratio = 0;
		vector<Point2f> mc(contours.size());
		for(int i = 0;i<contours.size(); i++) {
			mc[i] = Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
		ratio = mu[i].m00/mc[i].y;


		cout<<"RATIO: "<<ratio<<endl;
		
		if ( ratio >= 100 && ratio < 160)
			putText( Image2, "osobowy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio >= 160 && ratio < 230)
			putText( Image2, "dostawczy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio >= 230)
			putText( Image2, "tir", Point(mc[i].x, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio < 100)
			putText( Image2, "motor", Point(mc[i].x-50, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		}

		/*
		if ( ratio >= 100 && ratio < 160)
			putText( Image2, "osobowy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio >= 160 && ratio < 230)
			putText( Image2, "dostawczy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio >= 230)
			putText( Image2, "tir", Point(mc[i].x, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio < 100)
			putText( Image2, "motor", Point(mc[i].x-50, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		}
		*/
		imshow("win",Image2);
	}
}

int main(){
	namedWindow("win", CV_WINDOW_AUTOSIZE);
	imshow("win", pattern);
	setMouseCallback( "win", onMouse, 0 );

	waitKey(0);	
    return 0;
}
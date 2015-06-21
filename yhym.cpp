#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int loop = 0;
int thresh=29;
int i;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
char a = '1';
String path = "/home/kuba/Documents/vision/Photos/last/8/test.JPG";
Mat base = imread("/home/kuba/Documents/vision/Photos/last/8/base.JPG", CV_LOAD_IMAGE_GRAYSCALE);
Mat img = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
Mat Image2, img2, img3, lastImg, drawing;
Mat pattern = imread(path, CV_LOAD_IMAGE_COLOR);

void function( int, void* ){
}

static void onMouse( int event, int x, int y, int, void* ){
	if( event == EVENT_LBUTTONDOWN ){
		createTrackbar("Threshhold", "win", &thresh, 45, function );
		Image2 = pattern.clone();

		addWeighted(img, 1, base, -1, 0, img2);
		imwrite("Substracted.jpg", img2);
		GaussianBlur( img2, img3, Size( 51, 51 ), 0, 0 );
		threshold(img3, lastImg, thresh, 255,0);
		findContours(lastImg,contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		vector<Moments> mu(contours.size());
		for(int i = 0;i<contours.size(); i++) {
			mu[i] = moments(contours[i],false);
		}
		int cunt=0;
		float ratio = 0;
		vector<Point2f> mc(contours.size());
		for(int i = 0;i<contours.size(); i++) {
			mc[i] = Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
			ratio = mu[i].m00/mc[i].y;
			if (ratio > 50){

			drawContours(Image2, contours,i,Scalar(0, 0, 255),2,8,hierarchy, 0,Point());
			cunt++;

		if ( ratio >= 70 && ratio < 160)
			putText( Image2, "osobowy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio >= 160 && ratio < 230)
			putText( Image2, "dostawczy", Point(mc[i].x-100, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio >= 230)
			putText( Image2, "tir", Point(mc[i].x, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);
		else if (ratio < 70 && ratio > 50)
			putText( Image2, "motor", Point(mc[i].x-50, mc[i].y), 1, 2, Scalar(0, 0, 255), 2,2);

		cout<<ratio<<endl;
			}
		}
			cout<<"Ammount of viechcles: " << cunt<<endl;
		imshow("win",Image2);
		String str = "Contours number ";
		
		String b = ".jpg";
		imwrite(str+a+b, Image2);
		a++;
	}
}

int main(){
	namedWindow("win", CV_WINDOW_AUTOSIZE);
	imshow("win", pattern);
	setMouseCallback( "win", onMouse, 0 );

	waitKey(0);	
    return 0;
}

///image regustration // image alignment
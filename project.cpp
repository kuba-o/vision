#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{	
	Mat base = imread("/home/kuba/Documents/Projects/vision/Photos/n/1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2, img3, img4, lastImg;
	String destination = "/home/kuba/Documents/Projects/vision/Photos/n/";
	String destiny = "/home/kuba/Documents/Projects/vision/Photos/n/5.jpg";
	lastImg = imread(destiny, CV_LOAD_IMAGE_COLOR);
	img2 = imread(destiny, CV_LOAD_IMAGE_GRAYSCALE);
	addWeighted(base, 1, img2, -1, 0, img3);
	namedWindow("albonie", CV_WINDOW_AUTOSIZE);	
	
	String path;
	char a='2';
	string windowName = "Window";
	threshold(img3, img4, 15, 255,0);

	int whitePixels = 0;
	int blackPixels = 0;
	cout<<img4.cols<<endl;
	cout<<img4.rows<<endl;
	uchar* p = img4.data;
	int firstWhiteX = -1;
	int firstWhiteY = -1;
	int lastWhiteX = -1;
	int lastWhiteY = -1;
	for (int i = 0; i<1296; i++){
		for (int j = 0; j<864; j++){
			p = img4.data + img4.cols*j+i;
			if (*p==255){
				if (firstWhiteX == -1)
					firstWhiteX = i;
				if (firstWhiteY == -1)
					firstWhiteY = j;
				lastWhiteY = j;
				lastWhiteX = i;
				whitePixels++;
			}
			else
				blackPixels++;
		}
	}

	/*
		int firstWhiteX = -1;
	int firstWhiteY = -1;
	int lastWhiteX = -1;
	int lastWhiteY = -1;
	for (int i = 0; i<864; i++){
		for (int j = 0; j<1296; j++){
			p = img4.data + img4.cols*i+j;
			if (*p==255){
				if (firstWhiteX == -1)
					firstWhiteX = i;
				if (firstWhiteY == -1)
					firstWhiteY = j;
				lastWhiteY = j;
				lastWhiteX = i;
				whitePixels++;
			}
			else
				blackPixels++;
		}
	}
	*/

	cout<<lastWhiteX<<"LWX"<<endl;
	cout<<lastWhiteY<<"LWY"<<endl;
	putText( lastImg, "here", Point(firstWhiteX, firstWhiteY), 2, 2, Scalar(0, 255, 0), 2,2);
	line(img4,Point(firstWhiteX,firstWhiteY),Point(lastWhiteX, lastWhiteY),Scalar(0, 255, 0),5,1);
	imshow("albonie", lastImg);
	cout<<"black pixels: "<<blackPixels<<endl;
	cout<<"white pixels: "<<whitePixels<<endl;

	/*
	for (int i = 2; i<5; i++){
		string windowName = "Window";
		windowName +=a;
		path = destination + a + ".jpg";
		img2 = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
		addWeighted(img2,1,base,-1,0,img3);	
		namedWindow(windowName, CV_WINDOW_AUTOSIZE);	
		imshow(windowName, img3);
		a++;
	}
	*/
	waitKey(0);
	
    return 0;
}
//test
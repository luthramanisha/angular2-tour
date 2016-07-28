#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/core/core.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace cv;
int main(int argc, char ** argv) {

	//Start and end times
	time_t start,end;
	std::string fileName = argv[1];

	if (argc > 1) { fileName = argv[1]; }

	VideoCapture _vidCap(fileName);
  	char key = ' ';
  	assert(_vidCap.isOpened());

  	//Start the clock for tracking frames per second
  	time(&start);
  	int counter=0;

    // Get our first image
    cv::Mat prevImg, originalImage;

	_vidCap >> prevImg;

	 do {
		 // Get a new image
		_vidCap >> originalImage;
		// Check to make sure it's valid
		if (originalImage.empty() || (originalImage.data == NULL)) {
			cout<<"we are here";
			cout << "Can't load image from ";
			exit(EXIT_FAILURE);
		}

		// Leave original alone, work on a copy
		Mat dctImage = originalImage.clone();

		// split into planes
		vector<Mat> planes;
		split(dctImage, planes);
		vector<Mat> outplanes(planes.size());

		//divide each plane into blocks of 8X8 matrix
		//perform DCT
		for (size_t k = 0; k < planes.size(); k++) {
			for (int j = 0; j < planes[k].cols; j += 8) {  //height
				for (int l = 0; l < planes[k].rows; l+= 8) { //width
					Mat block = planes[k](Rect(j, l, 8, 8));
					planes[k].convertTo(block, CV_32FC1);
					dct(block, outplanes[k]);
				}
			}
		}

		merge(outplanes, dctImage);
		namedWindow("dctBlockImage");
		imshow("dctBlockImage", dctImage);

		//Stop the clock and show FPS
		time(&end);
		++counter;
		double sec=difftime(end,start);
		double fps=counter/sec;
		cout<<"fps:"<<fps<<"\n";

		// Check if a key was pressed
		key = cvWaitKey(1);

	}while (key != 'q');
}


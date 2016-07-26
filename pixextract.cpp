/*
		pixextract - extract pixel values according to a given mask
    Copyright (C) 2016  Vincent Mazoyer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>


using namespace cv;
using namespace std;

 // Global variables
 Mat image, mask;
 const char* remap_window = "Pixel extraction";


 int main( int argc, char** argv )
 {
	int i=0, j=0; // counters
	Vec3b intensity; // pixel color storage

	// Not enough arguments - print usage and exit
	if(argc<3)
	{
		cerr << "Usage: " << argv[0] << " [image] [mask]" << endl;
		exit(0);
	}

	// Load the images
  image = imread( argv[1], 1 ); // XXX vmazoyer: what if the file can't be read?
	mask = imread( argv[2], 1 );

	// image and mask should have the same size
	if(image.cols != mask.cols)
	{
		cerr << "Image and mask have different widths. Aborting." << endl;
		exit(1);
	}
	if(image.rows != mask.rows)
	{
		cerr << "Image and mask have different heights. Aborting." << endl;
		exit(1);
	}

  // Create window
  namedWindow( remap_window, CV_WINDOW_AUTOSIZE );

	// TODO vmazoyer: add flag to choose between BGR and HSV extraction
	// Convert BGR image to HSV
	cv::cvtColor(image, image, CV_BGR2HSV);

	// CSV header
	cout << "label,H,S,V" << endl;

  // Loop through every pixel of the mask
	for(i=0; i<image.rows; i++)
	{
		for(j=0; j<image.cols; j++)
		{
			// get the value of the mask's pixel
			intensity = mask.at<Vec3b>(j, i);

			// pair the pixel value with a label and print it out
			// XXX vmazoyer: rules are hardcoded :/
			if( (int)intensity.val[0]==0 && (int)intensity.val[1]==0 && (int)intensity.val[2]==255 )
			{
				intensity = image.at<Vec3b>(j, i);
				cout << "marking," << (int)intensity.val[0] << "," << (int)intensity.val[1] << "," << (int)intensity.val[2] << endl;
			}
			else if( (int)intensity.val[0]==255 && (int)intensity.val[1]==0 && (int)intensity.val[2]==0 )
			{
				intensity = image.at<Vec3b>(j, i);
				cout << "road," << (int)intensity.val[0] << "," << (int)intensity.val[1] << "," << (int)intensity.val[2] << endl;
			}
/*			else
			{
				intensity = image.at<Vec3b>(j, i);
				cout << "else," << (int)intensity.val[0] << "," << (int)intensity.val[1] << "," << (int)intensity.val[2] << endl;

			} */
		}
	}

  return 0;
 }

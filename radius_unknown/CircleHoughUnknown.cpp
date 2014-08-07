// CircleHoughUnknown.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cv.h>
#include <highgui.h>

// The main function
int main()
{
	IplImage* img = cvLoadImage("C:\\circle_variable.bmp", 0);			// The original image
	IplImage* edges = cvCreateImage(cvGetSize(img), 32, 1);		// Only edges
	IplImage* imgHough = cvCreateImage(cvGetSize(img), 8, 1);	// The accumulator cells

	// Ensure the accumulator cells are all zeroes out
	cvZero(imgHough);

	// Detect edges in the image
	cvSobel(img, edges, 1, 1);

	// Display the detected edges
	cvNamedWindow("test1");
	cvShowImage("test1", edges);

	// Uncomment to save to a file
	//cvSaveImage("C:\\circle_edges_variable.jpg", edges);

	// Loop through different values of the radius
	for(int radius = 10; radius<75; radius++)
	{
		// Loop through each pixel
		for(int x=0;x<img->width;x++)
		{
			for(int y=0;y<img->height;y++)
			{
				// Check if the current pixel is an edge
				int value = cvGetReal2D(edges, y, x);
				if(value==0) continue;
			
				// If it is an edge, generate its circle in the parameter space
				for(int theta=0;theta<360;theta++)
				{
					int a = x + radius*cos(theta*3.1412/180);
					int b = y + radius*sin(theta*3.1412/180);

					// Just in case
					if(a<0 || a>=img->width || b<0 || b>=img->height) continue;

					value = cvGetReal2D(imgHough, b, a);
					cvSetReal2D(imgHough, b, a, value+1);
				}
			}
		}

		// There will be several files... so save them all into files
		char* file = new char[50];
		sprintf(file, "C:\\folder\\hough_circle%d.jpg", radius);
		cvSaveImage(file, imgHough);
		cvZero(imgHough);

	}
	
	cvWaitKey(0);

	return 0;
}


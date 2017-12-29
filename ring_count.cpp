#include <opencv2/opencv.hpp>
using namespace cv;
#pragma comment(lib, "opencv_world340.lib")

#include <iostream>
using namespace std;

int main(void)
{
	Mat frame = imread("rings.jpg");

	if (frame.empty())
	{
		cout << "Error loading image file" << endl;
		return -1;
	}

	cvtColor(frame, frame, CV_BGR2GRAY);

	adaptiveThreshold(frame, frame, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

	// Use centre column
	int column_index = frame.cols / 2;
	int ring_count_vertical = 0;

	// Start with the second row
	for (int i = 1; i < frame.rows; i++)
	{
		// If this pixel is white and the previous pixel is black
		if (255 == frame.at<unsigned char>(i, column_index) && 0 == frame.at<unsigned char>(i - 1, column_index))
			ring_count_vertical++;
	}

	// Use centre row
	int row_index = frame.rows / 2;
	int ring_count_horizontal = 0;

	// Start with the second column
	for (int i = 1; i < frame.cols; i++)
	{
		// If this pixel is white and the previous pixel is black
		if (255 == frame.at<unsigned char>(row_index, i) && 0 == frame.at<unsigned char>(row_index, i - 1))
			ring_count_horizontal++;
	}

	if (ring_count_vertical > ring_count_horizontal)
		cout << ring_count_vertical << endl;
	else
		cout << ring_count_horizontal << endl;


	return 1;
}
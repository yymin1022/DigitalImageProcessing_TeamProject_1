#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <string>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void showLabel(Mat& img, string str, vector<Point> contour);
void imageColorToGray(Mat& org, Mat& res);
void imageGrayToBin(Mat& org, Mat& res);

#endif
#ifndef _MAIN_HPP
#define _MAIN_HPP

#include "opencv2/opencv.hpp"

void imageColorToGray(cv::Mat& org, cv::Mat& res);
void imageGrayToBin(cv::Mat& org, cv::Mat& res);
void showLabel(cv::Mat& img, std::string str, std::vector<cv::Point> contour);

#endif
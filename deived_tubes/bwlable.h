#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

void Two_PassNew(const Mat &bwImg, Mat &labImg);
cv::Scalar GetRandomColor();
void LabelColor(const cv::Mat& labelImg, cv::Mat& colorLabelImg,int&asd);

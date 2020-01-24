//
// Created by liris on 30/10/2019.
//

#ifndef SEGMENTATIONPHOTOMETRIQUE_TRAITEMENT_H
#define SEGMENTATIONPHOTOMETRIQUE_TRAITEMENT_H

#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "SmallImage.h"

using namespace cv;
using namespace std;
//!
//! \param imageTrans
void arrierePlanBlanc(Mat &imageTrans);

void imageReconstruction(std::vector <SmallImage> &tableImg, Mat &img);
void WriteOnDisk(vector <SmallImage> &tableImag);
/*vector <SmallImage>*/ void patchClassification(vector <SmallImage> &tabImg, vector <SmallImage> &tabImgReal);
cv::Mat imagePreprocessing(Mat &image);
vector <vector<SmallImage> >imageCrop(cv::Mat &img, cv::Mat &real);
vector <SmallImage>updateRatio(std::vector <SmallImage> &table);

#endif //SEGMENTATIONPHOTOMETRIQUE_TRAITEMENT_H

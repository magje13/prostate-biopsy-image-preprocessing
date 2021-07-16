#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <string>



using namespace std;
using namespace cv;

//
Mat globThres(Mat &img, int threshold);
int otsu(Mat const &img);
Mat gauss(Mat &img, int kern);
Mat dilation(Mat const &gray);
Mat erosion(Mat const &gray);
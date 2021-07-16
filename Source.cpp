#include"header.h"


Mat erosion(Mat const &gray) {

	Mat gray2 = gray.clone();
	int high = 0;

	for (int i = 1; i < gray.rows - 1; i++) {

		for (int j = 1; j < gray.cols - 1; j++) {

			high = 0;

			for (int k = i - 1; k < i + 2; k++) {

				for (int l = j - 1; l < j + 2; l++) {	//hardcoded til 3x3

					if (gray.at<uchar>(k, l) > high) {

						high = gray.at<uchar>(k, l);

					}

				}

			}

			gray2.at<uchar>(i, j) = high;

		}
	}


	return gray2;

}

Mat dilation(Mat const &gray) {

	Mat gray2 = gray.clone();
	int low = 255;
	for (int i = 1; i < gray.rows - 1; i++) {

		for (int j = 1; j < gray.cols - 1; j++) {

			low = 255;

			for (int k = i - 1; k < i + 2; k++) {

				for (int l = j - 1; l < j + 2; l++) {	//hardcoded til 3x3

					if (gray.at<uchar>(k, l) < low) {

						low = gray.at<uchar>(k, l);

					}

				}

			}

			gray2.at<uchar>(i, j) = low;
		}
	}
	
	return gray2;
}

Mat globThres(Mat &img, int threshold) {

	Mat bin = img.clone();
	uchar min = 0;
	uchar max = 255;

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {

			if (img.at<uchar>(i, j) <= threshold) {

				bin.at<uchar>(i, j) = min;
			}
			else {
				bin.at<uchar>(i, j) = max;
			}

		}
	}
	imwrite("otsuThres.png", bin);
	return bin;
}

int otsu(Mat const &img) {

	int imax = img.rows;
	int jmax = img.cols;
	int N = imax * jmax;
	double histArray[256] = { 0 };
	double w[256];
	double m[256];
	int intensity_max = 255;
	double sum = 0.0;
	double my = 0.0;
	double myT;
	double sigma = 0.0;
	double sigmaNew = 0.0;
	int k_star;
	double num;
	double denom;

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {

			histArray[img.at<uchar>(i, j)]++;

		}
	}

	for (int i = 0; i <= intensity_max; i++) {

		histArray[i] = histArray[i] / N;	//formel 1		
		// tjek om der er normaliseret
		sum += histArray[i]; 				//formel 6
		w[i] = sum;

		my += (i * histArray[i]);			//formel 7;
		m[i] = my;
	}

	myT = m[intensity_max];					//formel 8;

	for (int k = 1; k <= intensity_max; k++) {

		num = pow(myT * w[k] - m[k], 2);
		denom = w[k] * (1 - w[k]);

		sigmaNew = num / denom;				// formel 18

		if (sigmaNew > sigma) {				// formel 19 

			sigma = sigmaNew;
			k_star = k;
		}
	}

	return k_star;
}

Mat gauss(Mat &img, int kern) {

	Mat gau = img.clone();
	GaussianBlur(img, gau, Size(kern, kern), 0, 0);

	imwrite("gaussian.png", gau);
	return gau;
}
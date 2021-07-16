#include"header.h"




int main()
{

	Mat biops = imread("images/biopsy_sample.png", 1); //indlæser som rgb
	Mat biops_gray;
	
	

	if (biops.empty()){
		cout << "image is empty!" << endl;
	}

	cvtColor(biops, biops_gray, COLOR_BGR2GRAY); //kopierer i grayscale
	 
	//gaussian blur filter
	Mat biops_blur = gauss(biops_gray, 3);
	
	//Otsu thresholding
	Mat biops_otsu = globThres(biops_blur, otsu(biops_blur));

	Mat biops_dil = dilation(dilation(biops_otsu));
	imwrite("dilation.png", biops_dil);

	Mat biops_ero = erosion(erosion(biops_dil));
	imwrite("erosion.png", biops_ero);
} 
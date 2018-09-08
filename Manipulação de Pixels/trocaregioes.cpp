#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void troca(Mat &original, Mat &parte)//, int rowS, int colS, int rowE, int colE)
{
	int i, j, iaux, jaux;
	iaux=127;
	jaux=127;
	for(i = 0; i <= 127; i++){
	iaux++;
		for(j = 0; j <= 127; j++){
			jaux++;
			parte.at<uchar>(i,j) = original.at<uchar>(iaux,jaux)+0;
			
		}
	
		}
	
	iaux= 128;
	jaux= 0;
	for(i = 0; i <= 127; i++){
		for(j = 128; j <= 255; j++){
		parte.at<uchar>(i,j) = original.at<uchar>(iaux,jaux)+0;
		jaux++;
		}
	iaux++;
	}
	
	iaux= 0;
	jaux= 128;
	for(i = 128; i <= 255; i++){
		for(j = 0; j <= 127; j++){
		parte.at<uchar>(i,j) = original.at<uchar>(iaux,jaux)+0;
		jaux++;
		}
	iaux++;
	}

	iaux= 0;
	jaux= 0;
	for(i = 128; i <= 255 ; i++){
		for(j = 128; j <= 255; j++){
		parte.at<uchar>(i,j) = original.at<uchar>(iaux,jaux)+0;
		jaux++;
		}
	iaux++;
	}

}

int main(){

  Mat image;
  Mat partes(256,256,CV_8UC1);


  image = imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data)
		cout << "Não abriu a imagem" << endl;
  troca(image, partes);//, 0, 0, 255, 255);

  imshow("original", image);
  imshow("Pieces", partes);

  waitKey();
  return 0;
}

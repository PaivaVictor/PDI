#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void troca(Mat &original)//, int rowS, int colS, int rowE, int colE)
{

Mat parte(256,256,CV_8UC1, Scalar(0));
	
	int i, j;
	for(i = 0; i <= 127; i++){
	
		for(j = 0; j <= 127; j++){
			
			parte.at<uchar>(i,j) = original.at<uchar>(i+128,j+128);
		}
		}
	
	for(i = 0; i <= 127; i++){
		for(j = 128; j <= 255; j++){
		parte.at<uchar>(i,j) = original.at<uchar>(i+128,j-128);
		}
	}
	
	for(i = 128; i <= 255; i++){
		for(j = 0; j <= 127; j++){
		parte.at<uchar>(i,j) = original.at<uchar>(i-128,j+128);
		}
	}

	for(i = 128; i <= 255 ; i++){
		for(j = 128; j <= 255; j++){
		parte.at<uchar>(i,j) = original.at<uchar>(i-128,j-128);
		}
	} 
	imshow("trocado", parte);
	imwrite("trocado.png", parte);

}

int main(){

  Mat image;
  
  image = imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data)
		cout << "Não abriu a imagem" << endl;

  troca(image);

  imshow("original", image);


  waitKey();
  return 0;
}

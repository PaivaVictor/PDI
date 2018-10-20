#include <iostream>
#include <stdio.h>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double janela = 0;
double alfa = 0;
float alpha = 0;
double decaimento = 0;
double altura = 0;
double pos1 = 0;
double pos2 = 0;

int width, height, width1, height1, width2, height2;

int janela_slider = 0;
int janela_slider_max = 100;

int altura_slider = 0;
int altura_slider_max = 100;

int decaimento_slider = 0;
int decaimento_slider_max = 100;

int pos1_slider = 0;
int pos1_slider_max = 100;

Mat image = imread("taj.jpg"), media(image.rows,image.cols,CV_32FC3);
Mat tilt = Mat::zeros(image.rows,image.cols,CV_32FC3);
Mat pond1 = Mat::zeros(image.rows,image.cols,CV_32FC3);
Mat pond2 = Mat(image.rows,image.cols,CV_32FC3, Scalar(1,1,1)); 
Mat shift1(image.rows,image.cols,CV_32FC3,Scalar(0,0,0)), shift2(image.rows,image.cols,CV_32FC3,Scalar(0,0,0));
Vec3f foco, semfoco; 

char TiltShift[50];

//calcula o coeficiente alfa para as matrizes de ponderação
void ponderacao(int, void*){

 altura = (double) altura_slider/(10*altura_slider_max);
 decaimento = (double) decaimento_slider*100/decaimento_slider_max;
 pos1 = (double) pos1_slider*(height/2)/pos1_slider_max;
 janela = (double) janela_slider*100/janela_slider_max;
 pos2 = pos1 + janela;

	for(int x =0 ; x<height; x++){
		alfa = 0.5*(tanh((x-pos1)/decaimento) -tanh((x-pos2)/decaimento));
		for(int y =0; y<width; y++){
			foco[0] = alfa;
			semfoco[0] = 1-alfa;
			foco[1] = alfa;
			semfoco[1] = 1-alfa;
			foco[2] = alfa;
			semfoco[2] = 1- alfa;
			pond1.at<Vec3f>(x,y) = foco;
			pond2.at<Vec3f>(x,y) = semfoco;
		}
	}

  multiply(image, pond1, shift1, 1, -1);

  multiply(media, pond2, shift2, 1, -1);

 tilt = shift1 + shift2;
 tilt.convertTo(tilt, CV_8UC3);
 imshow("TiltShifted", tilt); 

}

int main(){

  width=image.size().width;
  height=image.size().height;

  image.convertTo(image, CV_32FC3);

  medianBlur(image, media, 5);

  namedWindow("TiltShifted", 1);
  
  sprintf( TiltShift, "Altura x %d", altura_slider_max );

  createTrackbar( TiltShift, "TiltShifted",
				  &altura_slider,
				  altura_slider_max,
				  ponderacao );

  ponderacao(altura_slider,0);

 
  sprintf( TiltShift, "Decaimento x %d", decaimento_slider_max );
  createTrackbar( TiltShift, "TiltShifted",
				  &decaimento_slider,
				  decaimento_slider_max,
				  ponderacao );
  ponderacao(decaimento_slider,0);
  
  sprintf( TiltShift, "Centro x %d", pos1_slider_max );
  createTrackbar( TiltShift, "TiltShifted",
				  &pos1_slider,
				  pos1_slider_max,
				  ponderacao  );
  ponderacao(pos1_slider,0);

  sprintf( TiltShift, "Janela x %d", janela_slider_max );
  createTrackbar( TiltShift, "TiltShifted",
				  &janela_slider,
				  janela_slider_max,
				  ponderacao  );
  ponderacao(janela_slider,0);

  waitKey(0);
  imwrite("foto.jpg",tilt);
  return 0;
}

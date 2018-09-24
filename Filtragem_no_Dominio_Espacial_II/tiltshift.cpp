#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

double alpha, l1 = 20, l2 =30;
int altura = 0;
int altura_max = 100;

int decaimento = 1;
int decaimento_max = 100;

int posVertical = 0;
int posVertical_max = 100;

Mat image1, image2, blended;
Mat imageTop; 


char TrackbarName[50];

double alpha_x(){


	alpha = altura*(tanh((x+posVertical)/decaimento)-tanh((x-(posVertical+10))/decaimento))  // quanto maior o decaimento mais suave é a descida/subida. l1 e l2 mexem na posição de subida e descida, respectivamente.

	return alpha;
}

void on_trackbar_alpha(int, void*){
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted( image1, alfa, imageTop, 1-alfa, 0.0, blended);
 imshow("addweighted", blended);
}

void on_trackbar_decaimento(int, void*){
  image1.copyTo(imageTop);
  int limit = top_slider*255/100;
  if(limit > 0){
	Mat tmp = image2(Rect(0, 0, 256, limit));

	tmp.copyTo(imageTop(Rect(0, 0, 256, limit)));
  }
  on_trackbar_blend(alfa_slider,0);
}

int main(int argvc, char** argv){
  image1 = imread("blend1.jpg");
  image2 = imread("blend2.jpg");
  image2.copyTo(imageTop);
  namedWindow("addweighted", 1);
  
  sprintf( TrackbarName, "Altura do centro x %d", altura_max );
  createTrackbar( TrackbarName, "addweighted",
				  &altura,
				  altura_max,
				  on_trackbar_alpha );
  on_trackbar_alpha(alfa_slider, 0 );
  
  sprintf( TrackbarName, "Decaimento x %d", decaimento_max );
  createTrackbar( TrackbarName, "addweighted",
				  &decaimento,
				  decaimento_max,
				  on_trackbar_decaimento );
  on_trackbar_decaimento(top_slider, 0 );

  sprintf( TrackbarName, "Posição Vertical x %d", posVertical_max );
  createTrackbar( TrackbarName, "addweighted",
				  &posVertical,
				  posVertical_max,
				  on_trackbar_posVertical );
  on_trackbar_posVertical(top_slider, 0 );

  waitKey(0);
  return 0;
}

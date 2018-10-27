#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 5
#define JITTER 3

int RAIO = 3;

int T2_slider = 10;
int T2_slider_max = 200;

int T1 = 0;

char Pontilhismo[50];

Mat image, border;

void pontilhismotech(int, void*){
  T1 = 3*T2_slider;
  Canny(image, border, T2_slider, T1); // calcula as bordas
  imshow("canny", border);

  for(auto a : xrange){	// calcula a distancia entre os pixels brancos (bordas) 
	random_shuffle(yrange.begin(), yrange.end());
	for(auto b : yrange){	// numa mesma linha para definir o raio
		if (border.at<uchar>(a,b) == 255){
			if(conta2 == 1){ 
				conta2 = 2;
				p1[conta2] = b;
				conta2 = 1;
			}
			RAIO = (int) (p1[1] - p1[0])/2.0;
		}
		
	}
  }



}

int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;

  Mat frame, points;

  int width, height, gray, conta2 = 1;
  int p1[2];
  int x, y;
  
  image= imread("biel.png");

  srand(time(0));
  
  if(!image.data){
	cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=image.size().width;
  height=image.size().height;

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);
  
  iota(xrange.begin(), xrange.end(), 0); 
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  points = Mat(height, width, CV_8U, Scalar(255));

  random_shuffle(xrange.begin(), xrange.end());
  
  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      gray = image.at<uchar>(x,y);
      circle(points,
             cv::Point(y,x),
             RAIO,
             CV_RGB(gray,gray,gray),
             -1,
             CV_AA, 0);
    }
  }

  sprintf( Pontilhismo, "Limite inferior", T2_slider_max );
  namedWindow("canny",1);
  createTrackbar( Pontilhismo, "canny",
                &T2_slider,
                T2_slider_max,
                pontilhismotech );

  pontilhismotech(T2_slider, 0 );

  waitKey();

  imwrite("pontos.jpg", points);
  return 0;
}

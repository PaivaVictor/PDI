#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){

  int p1x = 0, p1y = 0, p2x = 0, p2y = 0;
  char aux; 
  Mat image;
  image = imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);

  cout << "Insira duas coordenadas para o ponto P1: " << endl;
  cout << "P1x: ";
  cin >> p1x;
  cout << "P1y: ";
  cin >> p1y;
  cout << "Insira duas coordenadas para o ponto P2: " << endl;
  cout << "P2x: ";
  cin >> p2x;
  cout << "P2y: ";
  cin >> p2y;

  for(int i= p1x; i<= p2x;i++){
    for(int j= p1y; j<= p2y; j++){
    aux = image.at<uchar>(i,j);
    image.at<uchar>(i,j) = 255 - aux;	
    }
  }
  imshow("image", image);
  waitKey();
  return 0;
}

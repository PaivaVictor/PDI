#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void limpaborda (Mat &imagem, int h, int w){
int i=0,j=0, cont2;
CvPoint z;
z.x = 0;
z.y = 0;

	for(cont2=1; cont2<=2; cont2++){ // retirando bolhas das linhas: 0 e 255;
		for(j=0; j<w; j++){
			if(imagem.at<uchar>(i,j) == 255){
			z.x = j;
			z.y = i;
			floodFill(imagem,z,0);		
			}
		}
		i = 255;
	}
  j = 0;
	for(cont2=1;cont2<=2; cont2++){ // retirando bolhas das colunas: 0 e 255;
		for(i=0; i<h; i++){
			if(imagem.at<uchar>(i,j) == 255){
			z.x = j;
			z.y = i;
			floodFill(imagem,z,0);		
			}
		}
		j = 255;
	}
}

void contaburaco (Mat &imagem, int h, int w){
int i=0,j=0, bolhas=0, buracos=0, margem=50; // margem: para efeito visual, diferenciar um tom do outro
CvPoint z;
z.x = 0;
z.y = 0;

  if(imagem.at<uchar>(i,j)==0){ // diferencia o fundo dos buracos das bolhas
	z.x = j;
	z.y = i;
	floodFill(imagem,z,margem);
  }

  namedWindow("função",WINDOW_AUTOSIZE);
  imshow("função", imagem);
	for(i=0; i < h; i++){
		for(j=0; j < w;j++){
			if(imagem.at<uchar>(i,j) == 255){ // pinta o contorno da bolha com outro tom de cinza
			z.x = j;
			z.y = i;
			floodFill(imagem,z,2*margem);
			bolhas++;
			}
			if(imagem.at<uchar>(i,j) == 0){ // pinta o buraco com outro tom de cinza
			cout << "entrei" << endl;
			z.x = j;
			z.y = i;
			floodFill(imagem,z,3*margem);
			buracos++;
			}		
		}
	}
  cout << "Número de bolhas:" << bolhas << endl;
  cout << "Número de buracos:" << buracos << endl;
  cout << bolhas - buracos <<" bolhas não tem buracos" << endl;
}

int main(){
  Mat image, copy;
  int height, width;

  image= imread("bolhas.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu bolhas.png" << endl;
  namedWindow("janela",WINDOW_AUTOSIZE);

  height = image.size().height;
  width = image.size().width;
  copy.create(height,width,CV_8U);

  limpaborda(image, height, width);

  contaburaco(image, height, width);

  imshow("janela", image); 
  
  waitKey();
  return 0;
}

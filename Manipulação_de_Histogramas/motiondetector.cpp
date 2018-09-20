#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image1, image2, cinza1(256,256,CV_8U), cinza2(256,256,CV_8U);
  int width, height;
  VideoCapture cap1;
  Mat histC1(64,64,CV_8U), histC2(64,64,CV_8U);
  int nbins = 64, channel = 0;
  float range[] = {0, 256}, tolerancia = 5, distancia=0;
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap1.open(0);
  
  if(!cap1.isOpened()){
    cout << "cameras indisponiveis" << endl;
    return -1;
  }
  
  width  = cap1.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap1.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;
  
  int histw = nbins, histh = nbins/2;
  Mat histImgC1(histh, histw, CV_8U, Scalar(0));

  while(waitKey(30)!=32){

    
	cap1 >> image1;
	cvtColor(image1,cinza1,CV_BGR2GRAY);
	waitKey(50);

	calcHist(&cinza1,1,0,Mat(),histC1,1,&nbins,&histrange,uniform,acummulate);  //Histograma para imagem cinza normal
	normalize(histC1, histC1, 0, histImgC1.rows, NORM_MINMAX, -1, Mat());
  	histImgC1.setTo(Scalar(0));

	cap1 >> image2;
	cvtColor(image2,cinza2,CV_BGR2GRAY);
	
	calcHist(&cinza2,1,0,Mat(),histC2,1,&nbins,&histrange,uniform,acummulate);

	distancia=compareHist(histC2,histC1,CV_COMP_BHATTACHARYYA);

	if(distancia*100>tolerancia){
	cout << "Movimento!!" << endl;
	}

	for(int i=0; i<nbins; i++){
      line(histImgC1,
           Point(i, histh),
           Point(i, histh-cvRound(histC1.at<float>(i))),
           Scalar(255), 1, 8, 0);
    }

	histImgC1.copyTo(cinza1(Rect(0, 0,nbins, histh)));
	imshow("Tom Cinza", cinza1);

  }
  return 0;
}

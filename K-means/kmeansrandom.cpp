#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace cv; 
using namespace std;

int main(){
  int nClusters = 5;
  Mat rotulos;
  int nRodadas = 1, iteracoes = 100;
  double erro = 0.01;
  Mat centros;
  
  Mat img = imread("furacao.jpg");
  Mat samples(img.rows * img.cols, 3, CV_32F);

  for( int y = 0; y < img.rows; y++ ){
    for( int x = 0; x < img.cols; x++ ){
      for( int z = 0; z < 3; z++){
        samples.at<float>(y + x*img.rows, z) = img.at<Vec3b>(y,x)[z];
	  }
	}
  }
  
  kmeans(samples,
		 nClusters,
		 rotulos,
		 TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, iteracoes, erro),
		 nRodadas,
		 KMEANS_RANDOM_CENTERS,
		 centros );
	cout << centros.rows << " x " << centros.cols << endl;

  Mat rotulada( img.size(), img.type() );
  for( int y = 0; y < img.rows; y++ ){
    for( int x = 0; x < img.cols; x++ ){ 
	  int indice = rotulos.at<int>(y + x*img.rows,0);
	  rotulada.at<Vec3b>(y,x)[0] = (uchar) centros.at<float>(indice, 0);
	  rotulada.at<Vec3b>(y,x)[1] = (uchar) centros.at<float>(indice, 1);
	  rotulada.at<Vec3b>(y,x)[2] = (uchar) centros.at<float>(indice, 2);
	}
  }
  imshow( "clustered image", rotulada );
  imwrite("cluster10.jpg", rotulada);
  waitKey( 0 );
}

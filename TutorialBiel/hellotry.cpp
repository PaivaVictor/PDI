#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image,bru;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  bru =image;
  imshow("image", bru);
  waitKey();
  return 0;
}
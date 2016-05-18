#include <Eigen/Dense>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include "camera.h"
#include "scene.h"
#include "plane.h"
#include "light.h"
#include <omp.h>

#include "types.h"

using namespace Eigen;
using namespace std;
using namespace cv;

int main(int argc, char const *argv[]) {

  //omp_set_num_threads(1);

  //rendering resolution
  int SIZE_IMG = 1024;
  std::string FILE = "../mini_cornell.json";
  //std::string FILE = "../cornell_box.json";
  if (argc > 1) {
      FILE = std::string(argv[1]);
      if (argc > 2) SIZE_IMG = atoi(argv[2]);
  }

  srand(time(NULL));
  // load assets
  Scene cornellBox(FILE);
  Camera cam(FILE);

  //*
  Mat depthMap = cam.renderDepth(cornellBox, SIZE_IMG, SIZE_IMG);
  flip(depthMap, depthMap, 1);
  imwrite("../depth.jpg", depthMap);
  /**/

  //*
  Mat colorImg = cam.renderDirect(cornellBox, SIZE_IMG, SIZE_IMG);
  cvtColor(colorImg, colorImg, CV_BGR2RGB);
  flip(colorImg, colorImg, 1);
  imwrite("../color.png", colorImg);
  /**/

  //*
  Mat bounceImg = cam.renderBounceOnce(cornellBox, SIZE_IMG, SIZE_IMG);
  cvtColor(bounceImg, bounceImg, CV_BGR2RGB);
  flip(bounceImg, bounceImg, 1);
  imwrite("../color_bounce.png", bounceImg);
  /**/


  return 0;
}

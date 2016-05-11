#include <Eigen/Dense>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include "camera.h"
#include "scene.h"
#include "plane.h"
#include "light.h"

#include "types.h"

using namespace Eigen;
using namespace std;
using namespace cv;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Scene cornellBox("../cornell_box.json");

  //rendering resolution
  int SIZE_IMG = 212;

  Camera cam("../cornell_box.json");

  Mat depthMap = cam.renderDepth(cornellBox, SIZE_IMG, SIZE_IMG);
  flip(depthMap, depthMap, 1);
  imwrite("../depth.jpg", depthMap);

  Mat colorImg = cam.renderDirect(cornellBox, SIZE_IMG, SIZE_IMG);
  cvtColor(colorImg, colorImg, CV_BGR2RGB);
  flip(colorImg, colorImg, 1);
  imwrite("../color.jpg", colorImg);

  Mat bounceImg = cam.renderBounceOnce(cornellBox, SIZE_IMG, SIZE_IMG);
  cvtColor(bounceImg, bounceImg, CV_BGR2RGB);
  flip(bounceImg, bounceImg, 1);
  imwrite("../color_bounce.jpg", bounceImg);

  return 0;
}

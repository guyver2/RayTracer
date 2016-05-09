#include <Eigen/Dense>
#include <vector>
#include <opencv2/opencv.hpp>
#include "camera.h"
#include "scene.h"
#include "plane.h"
#include "light.h"

#include "types.h"

using namespace Eigen;
using namespace std;
using namespace cv;

int main(int argc, char const *argv[]) {

  Scene cornellBox("../cornell_box.json");

  //rendering resolution
  int SIZE_IMG = 2000;

  Camera cam("../cornell_box.json");

  Mat depthMap = cam.renderDepth(cornellBox, SIZE_IMG, SIZE_IMG);
  flip(depthMap, depthMap, 1);
  imwrite("../depth.jpg", depthMap);

  Mat colorImg = cam.renderDirect(cornellBox, SIZE_IMG, SIZE_IMG);
  cvtColor(colorImg, colorImg, CV_BGR2RGB);
  flip(colorImg, colorImg, 1);
  imwrite("../color.jpg", colorImg);
  return 0;
}

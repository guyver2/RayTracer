#include "camera.h"
#include "scene.h"
#include "plane.h"
#include <Eigen/Dense>
#include <vector>

using namespace Eigen;
using namespace std;

int main(int argc, char const *argv[]) {
  Vector3d center(278, 273, -800);
  Vector3d up(0, 1, 0);
  Vector3d dir(0, 0, 1);

  vector<Vector3d> pts_floor(0);
  pts_floor.push_back(Vector3d(556.0, 0.0,   0.0));
  pts_floor.push_back(Vector3d(  0.0, 0.0,   0.0));
  pts_floor.push_back(Vector3d(  0.0, 0.0, 559.2));
  pts_floor.push_back(Vector3d(556.0, 0.0, 559.2));
  Plane *floor = new Plane(pts_floor, "Floor");

  vector<Vector3d> pts_ceiling(0);
  pts_ceiling.push_back(Vector3d(556.0, 548.8,   0.0));
  pts_ceiling.push_back(Vector3d(556.0, 548.8, 559.2));
  pts_ceiling.push_back(Vector3d(  0.0, 548.8, 559.2));
  pts_ceiling.push_back(Vector3d(  0.0, 548.8,   0.0));
  Plane *ceiling = new Plane(pts_ceiling, "Ceiling");

  vector<Vector3d> pts_back(0);
  pts_back.push_back(Vector3d(556.0,   0.0, 559.2));
  pts_back.push_back(Vector3d(  0.0,   0.0, 559.2));
  pts_back.push_back(Vector3d(  0.0, 548.8, 559.2));
  pts_back.push_back(Vector3d(556.0, 548.8, 559.2));
  Plane *back = new Plane(pts_back, "Back");

  vector<Vector3d> pts_right(0);
  pts_right.push_back(Vector3d(  0.0,   0.0, 559.2));
  pts_right.push_back(Vector3d(  0.0,   0.0,   0.0));
  pts_right.push_back(Vector3d(  0.0, 548.8,   0.0));
  pts_right.push_back(Vector3d(  0.0, 548.8, 559.2));
  Plane *right = new Plane(pts_right, "Right");

  vector<Vector3d> pts_left(0);
  pts_left.push_back(Vector3d(556.0,   0.0,   0.0));
  pts_left.push_back(Vector3d(556.0,   0.0, 559.2));
  pts_left.push_back(Vector3d(556.0, 548.8, 559.2));
  pts_left.push_back(Vector3d(556.0, 548.8,   0.0));
  Plane *left = new Plane(pts_left, "Left");


  // small box
  vector<Vector3d> pts_sb0(0);
  pts_sb0.push_back(Vector3d(130.0, 165.0,  65.0));
  pts_sb0.push_back(Vector3d( 82.0, 165.0, 225.0));
  pts_sb0.push_back(Vector3d(240.0, 165.0, 272.0));
  pts_sb0.push_back(Vector3d(290.0, 165.0, 114.0));
  Plane *sb0 = new Plane(pts_sb0, "sb0");

  vector<Vector3d> pts_sb1(0);
  pts_sb1.push_back(Vector3d(290.0,   0.0, 114.0));
  pts_sb1.push_back(Vector3d(290.0, 165.0, 114.0));
  pts_sb1.push_back(Vector3d(240.0, 165.0, 272.0));
  pts_sb1.push_back(Vector3d(240.0,   0.0, 272.0));
  Plane *sb1 = new Plane(pts_sb1, "sb1");

  vector<Vector3d> pts_sb2(0);
  pts_sb2.push_back(Vector3d(130.0,   0.0,  65.0));
  pts_sb2.push_back(Vector3d(130.0, 165.0,  65.0));
  pts_sb2.push_back(Vector3d(290.0, 165.0, 114.0));
  pts_sb2.push_back(Vector3d(290.0,   0.0, 114.0));
  Plane *sb2 = new Plane(pts_sb2, "sb2");

  vector<Vector3d> pts_sb3(0);
  pts_sb3.push_back(Vector3d( 82.0,   0.0, 225.0));
  pts_sb3.push_back(Vector3d( 82.0, 165.0, 225.0));
  pts_sb3.push_back(Vector3d(130.0, 165.0,  65.0));
  pts_sb3.push_back(Vector3d(130.0,   0.0,  65.0));
  Plane *sb3 = new Plane(pts_sb3, "sb3");

  vector<Vector3d> pts_sb4(0);
  pts_sb4.push_back(Vector3d(240.0,   0.0, 272.0));
  pts_sb4.push_back(Vector3d(240.0, 165.0, 272.0));
  pts_sb4.push_back(Vector3d( 82.0, 165.0, 225.0));
  pts_sb4.push_back(Vector3d( 82.0,   0.0, 225.0));
  Plane *sb4 = new Plane(pts_sb4, "sb4");

  // tall box
  vector<Vector3d> pts_tb0(0);
  pts_tb0.push_back(Vector3d(423.0, 330.0, 247.0));
  pts_tb0.push_back(Vector3d(265.0, 330.0, 296.0));
  pts_tb0.push_back(Vector3d(314.0, 330.0, 456.0));
  pts_tb0.push_back(Vector3d(472.0, 330.0, 406.0));
  Plane *tb0 = new Plane(pts_tb0, "tb0");

  vector<Vector3d> pts_tb1(0);
  pts_tb1.push_back(Vector3d(423.0,   0.0, 247.0));
  pts_tb1.push_back(Vector3d(423.0, 330.0, 247.0));
  pts_tb1.push_back(Vector3d(472.0, 330.0, 406.0));
  pts_tb1.push_back(Vector3d(472.0,   0.0, 406.0));
  Plane *tb1 = new Plane(pts_tb1, "tb1");

  vector<Vector3d> pts_tb2(0);
  pts_tb2.push_back(Vector3d(472.0,   0.0, 406.0));
  pts_tb2.push_back(Vector3d(472.0, 330.0, 406.0));
  pts_tb2.push_back(Vector3d(314.0, 330.0, 456.0));
  pts_tb2.push_back(Vector3d(314.0,   0.0, 456.0));
  Plane *tb2 = new Plane(pts_tb2, "tb2");

  vector<Vector3d> pts_tb3(0);
  pts_tb3.push_back(Vector3d(314.0,   0.0, 456.0));
  pts_tb3.push_back(Vector3d(314.0, 330.0, 456.0));
  pts_tb3.push_back(Vector3d(265.0, 330.0, 296.0));
  pts_tb3.push_back(Vector3d(265.0,   0.0, 296.0));
  Plane *tb3 = new Plane(pts_tb3, "tb3");

  vector<Vector3d> pts_tb4(0);
  pts_tb4.push_back(Vector3d(265.0,   0.0, 296.0));
  pts_tb4.push_back(Vector3d(265.0, 330.0, 296.0));
  pts_tb4.push_back(Vector3d(423.0, 330.0, 247.0));
  pts_tb4.push_back(Vector3d(423.0,   0.0, 247.0));
  Plane *tb4 = new Plane(pts_tb4, "tb4");


  Scene cornellBox;
  cornellBox.addElt(floor);
  cornellBox.addElt(ceiling);
  cornellBox.addElt(back);
  cornellBox.addElt(right);
  cornellBox.addElt(left);

  // small box
  cornellBox.addElt(sb0);
  cornellBox.addElt(sb1);
  cornellBox.addElt(sb2);
  cornellBox.addElt(sb3);
  cornellBox.addElt(sb4);

  // Tall box
  cornellBox.addElt(tb0);
  cornellBox.addElt(tb1);
  cornellBox.addElt(tb2);
  cornellBox.addElt(tb3);
  cornellBox.addElt(tb4);



  Camera cam(center, up, dir, 0.035, 0.025, 0.025);
  cam.render(cornellBox, 2000, 2000);
  return 0;
}

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE "ImageSonar_test"

#include <iostream>

// #include <osg/Image>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vizkit3d_normal_depth_map/ImageViewerCaptureTool.hpp>
#include <vizkit3d_image_sonar/ImageSonar.hpp>

using namespace vizkit3d_normal_depth_map;
using namespace vizkit3d_image_sonar;


cv::Mat3f plotSonarTest( cv::Mat3f image,
                         int height, int width) {

  cv::Mat3b imagePlotMap = cv::Mat3b::zeros(height, width);

  for(int x = 0; x < image.rows; x++ )
    for(int y = 0; y < image.cols; y++ ){
      cv::Point2i point( image[y][x][2], image[y][x][1]) ;
      point = point + cv::Point2i(width/2, 0);
      imagePlotMap[point.y][point.x][1] = 255;
    }


  return imagePlotMap;
}


void makeSimpleScene(osg::ref_ptr<osg::Group> root) {

  osg::Geode *sphere = new osg::Geode();
  sphere->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), 1)));
  root->addChild(sphere);

  osg::Geode *cylinder = new osg::Geode();
  cylinder->addDrawable(
    new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(30, 0, 10), 10, 10)));
  root->addChild(cylinder);

  osg::Geode *cone = new osg::Geode();
  cylinder->addDrawable(
    new osg::ShapeDrawable(new osg::Cone(osg::Vec3(0, 30, 0), 10, 10)));
  root->addChild(cone);

  osg::Geode *box = new osg::Geode();
  cylinder->addDrawable(
    new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, -30, -10), 10)));
  root->addChild(box);
}

void viewPointsFromScene(std::vector<osg::Vec3d> *eyes,
                          std::vector<osg::Vec3d> *centers,
                          std::vector<osg::Vec3d> *ups) {

  // view1 - near from the ball with the cylinder in back
  eyes->push_back(osg::Vec3d(-8.77105, -4.20531, -3.24954));
  centers->push_back(osg::Vec3d(-7.84659, -4.02528, -2.91345));
  ups->push_back(osg::Vec3d(-0.123867, -0.691871, 0.711317));

  // view2 - near from the ball with the cube in back
  eyes->push_back(osg::Vec3d(3.38523, 10.093, 1.12854));
  centers->push_back(osg::Vec3d(3.22816, 9.12808, 0.918259));
  ups->push_back(osg::Vec3d(-0.177264, -0.181915, 0.967204));

  // view3 - near the cone in up side
  eyes->push_back(osg::Vec3d(-10.6743, 38.3461, 26.2601));
  centers->push_back(osg::Vec3d(-10.3734, 38.086, 25.3426));
  ups->push_back(osg::Vec3d(0.370619, -0.854575, 0.36379));

  // view4 - Faced the cube plane
  eyes->push_back(osg::Vec3d(0.0176255, -56.5841, -10.0666));
  centers->push_back(osg::Vec3d(0.0176255, -55.5841, -10.0666));
  ups->push_back(osg::Vec3d(0, 0, 1));
}

BOOST_AUTO_TEST_CASE(first_test){

  std::vector<osg::Vec3d> eyes, centers, ups;

  float maxRange = 50;
  float maxAngleX = M_PI * 1.0 / 6; // 30 degrees
  float maxAngleY = M_PI * 1.0 / 6; // 30 degrees

  uint height = 1000;
  ImageViewerCaptureTool capture(height, height);
  ImageSonar image_sonar(maxRange, maxAngleX/2,  maxAngleY/2);

  capture.setBackgroundColor(osg::Vec4d(0, 0, 0, 0));


  osg::ref_ptr<osg::Group> root = new osg::Group();
  viewPointsFromScene(&eyes, &centers, &ups);
  makeSimpleScene(root);
  image_sonar.addNodeScene(root);

  for (uint i = 0; i < eyes.size(); ++i) {
    capture.setCameraPosition(eyes[i], centers[i], ups[i]);
    image_sonar.setCameraPosition(centers[i], eyes[i], ups[i]);

    osg::ref_ptr<osg::Image> osgImage =
          capture.grabImage(image_sonar.getImageSonarNode());
    cv::Mat3f cv_image(osgImage->t(), osgImage->s());
    cv_image.data = osgImage->data();
    cv_image = cv_image.clone();
    cv::cvtColor(cv_image, cv_image, cv::COLOR_RGB2BGR, CV_32FC3);
    cv::flip(cv_image, cv_image, 0);
    cv::imshow("out image", cv_image);


    // cv::Mat3b cv_plot = plotSonarTest(cv_image * height, 1000, 1000);
    // cv::imshow("out plot", cv_plot);

    cv::waitKey();
  }
}

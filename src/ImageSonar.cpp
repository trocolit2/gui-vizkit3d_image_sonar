#include "ImageSonar.hpp"

#include <osg/Node>
#include <osg/Program>
#include <osg/ref_ptr>
#include <osg/Group>
#include <osg/Shader>
#include <osg/StateSet>
#include <osg/Uniform>
#include <osgDB/FileUtils>

namespace vizkit3d_image_sonar {

#define SHADER_PATH_FRAG "vizkit3d_image_sonar/shaders/createImageSonar.frag"
#define SHADER_PATH_VERT "vizkit3d_image_sonar/shaders/createImageSonar.vert"

ImageSonar::ImageSonar(){
_image_sonar_node = createImageSonarShaderNode();

}

ImageSonar::ImageSonar( float maxRange,
                        float maxHorizontalAngle,
                        float maxVerticalAngle){

_image_sonar_node = createImageSonarShaderNode( maxRange,
                                                maxHorizontalAngle,
                                                maxVerticalAngle);
}


void ImageSonar::addNodeScene(osg::ref_ptr<osg::Node> node){
  _image_sonar_node->addChild(node);
}

osg::ref_ptr<osg::Group> ImageSonar::createImageSonarShaderNode(
                                float maxRange,
                                float maxHorizontalAngle,
                                float maxVerticalAngle){


  std::cout<<" out 1 "<<std::endl;

  osg::ref_ptr<osg::Group> localRoot = new osg::Group();
  osg::ref_ptr<osg::Program> program(new osg::Program());

  osg::ref_ptr<osg::Shader> shaderVertex =
          osg::Shader::readShaderFile( osg::Shader::VERTEX,
                                       osgDB::findDataFile(SHADER_PATH_VERT));
  osg::ref_ptr<osg::Shader> shaderFragment =
          osg::Shader::readShaderFile( osg::Shader::FRAGMENT,
                                       osgDB::findDataFile(SHADER_PATH_FRAG));
  program->addShader(shaderFragment);
  program->addShader(shaderVertex);

  osg::ref_ptr<osg::StateSet> ss = localRoot->getOrCreateStateSet();
  ss->setAttribute(program);

  // add uniform data
  // osg::ref_ptr<osg::Uniform> max_range_uniform(
  //                                     new osg::Uniform("max_range", maxRange));
  // ss->addUniform(max_range_uniform);
  //
  // osg::ref_ptr<osg::Uniform> angle_x_uniform(
  //                         new osg::Uniform( "max_x_angle", maxHorizontalAngle));
  // ss->addUniform(angle_x_uniform);
  //
  // osg::ref_ptr<osg::Uniform> angle_y_uniform(
  //                           new osg::Uniform( "max_y_angle", maxVerticalAngle));
  // ss->addUniform(angle_y_uniform);


  // camera data
  osg::Vec3d position, eye, up;
  ss->addUniform( new osg::Uniform( "camera_position", position) );
  ss->addUniform( new osg::Uniform( "camera_eye", eye) );
  ss->addUniform( new osg::Uniform( "camera_up", up) );

  return localRoot;
}


// void NormalDepthMap::setMaxRange(float maxRange) {
//     _normalDepthMapNode->getOrCreateStateSet()->getUniform("farPlane")->set(maxRange);
// }

void ImageSonar::setCameraPosition( osg::Vec3d position,
                                    osg::Vec3d eye,
                                    osg::Vec3d up){

  std::cout<<" out 2 "<<std::endl;
  _image_sonar_node->getOrCreateStateSet()->
                                  getUniform("camera_position")->set(position);
  _image_sonar_node->getOrCreateStateSet()->
                                  getUniform("camera_eye")->set(eye);
  _image_sonar_node->getOrCreateStateSet()->
                                  getUniform("camera_up")->set(up);

}

}

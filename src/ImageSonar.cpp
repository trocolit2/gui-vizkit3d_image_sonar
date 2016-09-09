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

  osg::ref_ptr<osg::Uniform> farPlaneUniform(
                                        new osg::Uniform("maxRange",
                                                         maxRange));
  ss->addUniform(farPlaneUniform);

  osg::ref_ptr<osg::Uniform> maxHorizontalAngleUniform(
                                      new osg::Uniform( "limitHorizontalAngle",
                                                        maxHorizontalAngle));
  ss->addUniform(maxHorizontalAngleUniform);

  osg::ref_ptr<osg::Uniform> maxVerticalAngleUniform(
                                        new osg::Uniform( "limitVerticalAngle",
                                                          maxVerticalAngle));
  ss->addUniform(maxVerticalAngleUniform);

  return localRoot;
}

}

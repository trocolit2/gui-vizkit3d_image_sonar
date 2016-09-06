#include <osg/Node>
#include <osg/Group>
#include <osg/ref_ptr>

namespace vizkit3d_image_sonar {

class ImageSonar {

  public:
    ImageSonar();
    ImageSonar(float maxRange, float maxHorizontalAngle, float maxVerticalAngle);

    void addNodeScene(osg::ref_ptr<osg::Node> node);

    const osg::ref_ptr<osg::Group> getImageSonarNode() const {
        return _image_sonar_node;
    }

    void setMaxRange(float maxRange);
    float getMaxRange();

    void setMaxHorizontalAngle(float maxHorizontalAngle);
    float getMaxHorizontalAngle();

    void setMaxVerticalAngle(float maxVerticalAngle);
    float getMaxVerticalAngle();

    //
    // void setDrawNormal(bool drawNormal);
    // bool isDrawNormal();
    //
    // void setDrawDepth(bool drawDepth);
    // bool isDrawDepth();

  private:
    osg::ref_ptr<osg::Group> _image_sonar_node; //main shader node

    osg::ref_ptr<osg::Group> createImageSonarShaderNode(
                                    float maxRange = 50.0,
                                    float maxHorizontalAngle = M_PI * 1.0 / 6.0,
                                    float maxVerticalAngle = M_PI * 1.0 / 6.0);

};
}

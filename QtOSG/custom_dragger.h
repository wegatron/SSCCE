#ifndef CUSTOM_DRAGGER_H
#define CUSTOM_DRAGGER_H

#include <osgManipulator/Dragger>

class CustomTransformDragger : public osgManipulator::Dragger
{
public:
  CustomTransformDragger();
  virtual void setupDefaultGeometry();
  virtual void initColor();
  virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
  virtual bool handle(const osg::Vec3d& intersect, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
  virtual ~CustomTransformDragger() {}
private:
  osg::Vec3d orientation_;
  osg::Vec3d  prev_pt_;
  osg::ref_ptr<osg::Node> transform_ctrl_;
  osg::Vec4 _color;
  osg::Vec4 _pickColor;
};

#endif /* CUSTOM_DRAGGER_H */

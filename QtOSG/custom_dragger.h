#ifndef CUSTOM_DRAGGER_H
#define CUSTOM_DRAGGER_H

#include <osgManipulator/Dragger>
#include <osgManipulator/Projector>

class CustomTransformDragger : public osgManipulator::Dragger
{
public:
  CustomTransformDragger();
  virtual void setupDefaultGeometry();
  virtual void initColor();
  virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
  virtual bool handle2(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
  virtual ~CustomTransformDragger() {}
 private:
  osgManipulator::PointerInfo point_info_;
  osg::ref_ptr<osgManipulator::PlaneProjector> projector_;
  osg::Vec3 orientation_;
  osg::Vec3d  prev_pt_;
  osg::ref_ptr<osg::Node> transform_ctrl_;
  osg::Vec4 _color;
  osg::Vec4 _pickColor;
};

#endif /* CUSTOM_DRAGGER_H */

#include "custom_dragger.h"

#include <osgDB/ReadFile>
#include <osg/Material>

CustomTransformDragger::CustomTransformDragger() : orientation_(0.0, 0.0, 1.0)
{
  setupDefaultGeometry();
  initColor();
}

void CustomTransformDragger::setupDefaultGeometry()
{
  transform_ctrl_ = osgDB::readNodeFile("/home/wegatron/cube.obj");
  addChild(transform_ctrl_);
}

void CustomTransformDragger::initColor()
{
  osg::StateSet *stateset = this->getOrCreateStateSet();
  osg::Material *mat = dynamic_cast<osg::Material*>(stateset->getAttribute(osg::StateAttribute::MATERIAL));

  if(!mat) {
    mat = new osg::Material;
    mat->setDataVariance(osg::Object::DYNAMIC);
    stateset->setAttribute(mat);
  }
  _color = osg::Vec4(0.889404, 0.611356, 0.008204, 0.4);
  mat->setDiffuse(osg::Material::FRONT_AND_BACK, _color);

  stateset->setMode(GL_BLEND, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);
  stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
  stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

  _pickColor = osg::Vec4(1.000000, 0.528255, 0.013920, 0.6);
}


bool CustomTransformDragger::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
  osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
  if(!view) return false;
  bool handled = false;

  switch(ea.getEventType()) {
  case osgGA::GUIEventAdapter::PUSH: {
    osgUtil::LineSegmentIntersector::Intersections intersections;
    if (view->computeIntersections(ea, intersections)) {
      for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
           hitr!=intersections.end(); ++hitr) {
        // todo
        for(osg::NodePath::const_iterator citr = hitr->nodePath.cbegin();
            citr != hitr->nodePath.cend(); ++ citr) {
          CustomTransformDragger* dragger = dynamic_cast<CustomTransformDragger*>(*itr);
          if (dragger == this) {
            hitr->getWorldIntersectPoint();
          }
        }
      }
    }
    break;
  }
  default:
    break;
  }
  return handled;
}

bool CustomTransformDragger::handle(const osg::Vec3d& intersect, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
  return false;
}

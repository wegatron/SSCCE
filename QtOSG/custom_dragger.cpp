#include "custom_dragger.h"

#include <osgDB/ReadFile>
#include <osg/Material>
#include <osgViewer/View>
#include <osg/io_utils>

CustomTransformDragger::CustomTransformDragger() : orientation_(0.0, 0.0, 1.0)
{
  projector_ = new osgManipulator::PlaneProjector;
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

  point_info_.reset();
  switch(ea.getEventType()) {
  case osgGA::GUIEventAdapter::PUSH: {
    osgUtil::LineSegmentIntersector::Intersections intersections;
    if (view->computeIntersections(ea, intersections)) {
      for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
           !handled && hitr!=intersections.end(); ++hitr) {
        for(osg::NodePath::const_iterator citr = hitr->nodePath.cbegin();
            citr != hitr->nodePath.cend(); ++ citr) {
          CustomTransformDragger* dragger = dynamic_cast<CustomTransformDragger*>(*citr);
          if (dragger == this) {
            point_info_.addIntersection(hitr->nodePath, hitr->getLocalIntersectPoint());
            std::cout << "local:" << hitr->getLocalIntersectPoint() << std::endl;
            std::cout << "world:" << hitr->getWorldIntersectPoint() << std::endl;
            point_info_.setCamera(view->getCamera());
            osg::Camera *camera = view->getCamera();
            std::cout << "point info's mvpW:" << camera->getViewMatrix() * camera->getProjectionMatrix() << std::endl;
            handled = handle2(ea, aa);
            _draggerActive = handled;
            break;
          }
        }
      }
    }
    break;
  }

  case osgGA::GUIEventAdapter::DRAG:
  case osgGA::GUIEventAdapter::RELEASE: {
    if(!_draggerActive) {break;}
    if(osgGA::GUIEventAdapter::RELEASE == ea.getEventType()) {_draggerActive = false;}
    // trigger handler
    handle2(ea, aa);
    handled = true;
    break;
  }
  default:
    break;
  }
  return handled;
}

bool CustomTransformDragger::handle2(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
  bool handled = false;
  //projector
  switch(ea.getEventType()) {
  case (osgGA::GUIEventAdapter::PUSH): {
    // init projector
    osg::NodePath nodePathToRoot;
    computeNodePathToRoot(*this,nodePathToRoot);
    osg::Matrix localToWorld = osg::computeLocalToWorld(nodePathToRoot);
    osg::Vec3 world_intersect = point_info_.getLocalIntersectPoint();
    std::cout << "compute - world coord:" << world_intersect << std::endl;
    osg::Plane plane(point_info_.getEyeDir(), world_intersect);
    projector_->setPlane(plane);
    projector_->setLocalToWorld(localToWorld);

    // project
    point_info_.setMousePosition(ea.getX(), ea.getY());
    osg::Vec3d projected_point;
    projector_->project(point_info_, projected_point);
    prev_pt_ = projector_->getLocalToWorld()*projected_point;

    // dispatch command
    osg::ref_ptr<osgManipulator::TranslateInLineCommand> cmd =
      new osgManipulator::TranslateInLineCommand();
    cmd->setStage(osgManipulator::MotionCommand::START);
    dispatch(*cmd);

    // reset material and request redraw
    setMaterialColor(_pickColor,*this);
    aa.requestRedraw();
    handled = true;
    break;
  }
  case (osgGA::GUIEventAdapter::DRAG) :
  case (osgGA::GUIEventAdapter::RELEASE): {
    // compute projected point
    point_info_.setMousePosition(ea.getX(), ea.getY());
    osg::Vec3d projected_point;

    osg::Vec3d nearPoint, farPoint;
    point_info_.getNearFarPoints(nearPoint,farPoint);
    std::cout << "near far point:" << nearPoint << " () " << farPoint << std::endl;

    // osg::Plane plane = projector_->getPlane();
    //std::cout << "plane normal:" << plane.getNormal() << std::endl;
    projector_->project(point_info_, projected_point);
    projected_point = projector_->getLocalToWorld() *projected_point;

    // compute transform vector and dispatch command
    osg::ref_ptr<osgManipulator::TranslateInLineCommand> cmd = new osgManipulator::TranslateInLineCommand();
    cmd->setTranslation(projected_point - prev_pt_);
    std::cout << "current world:" << projected_point<< std::endl;
    dispatch(*cmd);
    // reset
    handled = true;
    if(osgGA::GUIEventAdapter::RELEASE == ea.getEventType()) {
      std::cout << "release!" << std::endl;
      setMaterialColor(_color, *this);
    }
    aa.requestRedraw();
    break;
  }
  default:
    break;
  }
  return handled;
}

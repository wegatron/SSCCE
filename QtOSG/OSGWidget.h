#ifndef OSGWidget_h__
#define OSGWidget_h__

#include <QPoint>
#include <QtOpenGL>

#include <osg/ref_ptr>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>

class OSGWidget : public QGLWidget
{
  Q_OBJECT

public:
  OSGWidget( QWidget* parent = 0,
             const QGLWidget* shareWidget = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();

protected:

  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );

  virtual void mouseMoveEvent( QMouseEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );
  virtual void wheelEvent( QWheelEvent* event );

  virtual bool event( QEvent* event );

private:

  virtual void onHome();
  virtual void onResize( int width, int height );

  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> graphicsWindow_;
  //osg::ref_ptr<osgViewer::CompositeViewer> viewer_;
  osg::ref_ptr<osgViewer::Viewer> viewer_;
//  QPoint selectionStart_;
//  QPoint selectionEnd_;

//  bool selectionActive_;
//  bool selectionFinished_;

//  void processSelection();
};

class ui_handler :  public osgGA::GUIEventHandler
{
public:
  virtual ~ui_handler() {}
  // handle viewer event
  bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

  // @TODO handle mainWindow event

  //	virtual event_return on_reshape(int width, int height);
  //	virtual event_return on_keyboard(unsigned char key, int x, int y);
  //	virtual event_return on_mouse(int button, int state, int x, int y);
  //	virtual event_return on_motion(int x, int y);
protected:
  virtual void pick(osgViewer::Viewer* view, const osgGA::GUIEventAdapter& ea);
};

#endif

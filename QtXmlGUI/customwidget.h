#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QtGui>

class CustomWidget : public QWidget
{
  Q_OBJECT
 public:
 CustomWidget(QWidget* parent=0, Qt::WindowFlags f=0) : QWidget(parent, f) {}
 private:
  std::string cid_;
};

#endif /* CUSTOMWIDGET_H */

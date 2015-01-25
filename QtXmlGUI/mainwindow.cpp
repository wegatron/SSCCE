#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  initToolBar();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::initToolBar()
{
  QToolBar *tool_bar = ui->mainToolBar;
  QIcon file_icon("/home/wegatron/workspace/ui_framework/branches/4zsw/resource/background/file.png");
  tool_bar->addAction(file_icon, "load model", NULL, NULL);
  tool_bar->addAction(file_icon, "load model2", NULL, NULL);
}

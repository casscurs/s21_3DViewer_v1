#ifndef DISPLAY_H
#define DISPLAY_H

#define NONE 0
#define SOLID 1
#define DOTTED 2

#define CIRCLE 1
#define SQUARE 2

#define CENTRAL 0
#define PARALLEL 1

#define GL_SILENCE_DEPRECATION
#include <QTime>
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>

extern "C" {
#include "../Backend/back.h"
}

class display : public QOpenGLWidget {
  Q_OBJECT
 private:
  double xRot = 0, yRot = 0, zRot = 0;
  double scale = 0;
  QPoint mPos;
  QTimer tmr;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

  void resizeGL(int w, int h) override;
  void paintGL() override;
  void drawCoordinateAxes();

 public:
  res syst = {0};

  double back_r = 0, back_g = 0, back_b = 0;
  double edge_r = 255, edge_g = 255, edge_b = 255;
  double vert_r = 255, vert_g = 255, vert_b = 255;
  int lineType = 0;
  double lineSize = 0.5;
  double verticles = 0;  // тип точки
  double vertSize = 0.5;
  int projection = PARALLEL;

  void initializeGL() override;
  int flag;
  display(QWidget *parent = nullptr);
  void openFile(char *filename, int fileStatus);
  void move_model(double a, char axis);
  void rot_model(double angle, char axis);
  void scale_model(double a);
};

#endif  // DISPLAY_H

#include "display.h"

#include "mainwindow.h"

display::display(QWidget *parent) : QOpenGLWidget(parent) {}

/* При создании окна */
void display::initializeGL() { glEnable(GL_DEPTH_TEST); }

/* При изменении размеров окна */
void display::resizeGL(int w, int h) {
  /* Область видимости окна, где будет отрисовка */
  glViewport(0, 0, w, h);
}

void display::paintGL() {
  glLoadIdentity();

  if (projection == PARALLEL) {
    /* Работа с матрицей проекций */
    glMatrixMode(GL_PROJECTION);
    /* Задаем параллельную проецию */
    glOrtho(-1, 1, -1, 1, -10, 10);

  } else if (projection == CENTRAL) {
    /* Работа с матрицей проекций */
    glMatrixMode(GL_PROJECTION);
    /* Задаем центральную проецию */
    glFrustum(-1, 1, -1, 1, 2, 12.5);
    glTranslated(0, 0, -2.5);
  }
  if (flag == 0) {
    /* Цвет фона */
    glClearColor(back_r / 255, back_g / 255, back_b / 255, 0);
    /* Очистка буфера цвета в каждом прогоне */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  glRotated(xRot, 1, 0, 0);
    //  glRotated(yRot, 0, 1, 0);

    if (lineType == DOTTED) {
      /* пунктир */
      glEnable(GL_LINE_STIPPLE);
      /* Первый параметр - фактор повторения, второй - паттерн */
      glLineStipple(10, 0xAAAA);
    } else if (lineType == SOLID) {
      glDisable(GL_LINE_STIPPLE);
    }
    glLineWidth(lineSize);
    drawCoordinateAxes();
    glColor3d(edge_r / 255, edge_g / 255, edge_b / 255);

    for (int i = 0; i < syst.amountFacets; ++i) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < syst.face[i].count; ++j) {
        int n = syst.face[i].f[j];
        glVertex3d(syst.vert.coord[n].x, syst.vert.coord[n].y,
                   syst.vert.coord[n].z);
      }
      glEnd();
    }

    if (verticles >= 1) {
      if (verticles == CIRCLE)
        glEnable(GL_POINT_SMOOTH);
      else
        glDisable(GL_POINT_SMOOTH);

      glColor3d(vert_r / 255, vert_g / 255, vert_b / 255);
      glPointSize(vertSize);  //размер элементов

      for (int i = 0; i < syst.amountFacets; ++i) {
        glBegin(GL_POINTS);
        //  glColor3f(1.0f, 0.0f, 0.0f); //цвет отображения
        for (int j = 0; j < syst.face[i].count; ++j) {
          int n = syst.face[i].f[j];
          glVertex3d(syst.vert.coord[n].x, syst.vert.coord[n].y,
                     syst.vert.coord[n].z);
        }
        glEnd();
      }
    }
  }
}

void display::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void display::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 0.005 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 0.005 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void display::drawCoordinateAxes() {
  /* Ось X - Красная */
  glColor3d(2.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3d(-2.0, 0.0, 0.0);
  glVertex3d(2.0, 0.0, 0.0);
  glEnd();

  /* Ось Y - Зеленая */
  glColor3d(0.0, 2.0, 0.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, -2.0, 0.0);
  glVertex3d(0.0, 2.0, 0.0);
  glEnd();

  /* Ось Z - Синяя */
  glColor3d(0.0, 0.0, 2.0);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, -2.0);
  glVertex3d(0.0, 0.0, 2.0);
  glEnd();
}

void display::openFile(char *filename, int fileStatus) {
  if (fileStatus != 0) res_free(&syst);
  flag = obj_counter(filename, &syst);
  flag = matrix_fill(filename, &syst);
  if (syst.vert.amountVert == 0) flag = -1;
  if (flag == 0) {
    center_frames(&syst);
    resize_frames(&syst, 0.5);
    update();
  }
}

void display::move_model(double a, char axis) {
  movement(&syst, a, axis);
  update();
}

void display::rot_model(double angle, char axis) {
  rot(&syst, angle, axis);
  update();
}

void display::scale_model(double a) {
  if (a < 0) {
    a = -a;
    a = 1.0 / a;
  }
  resize_frames(&syst, a);
  update();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMovie>
#include <QSettings>
#include <QTimer>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

#include "display.h"
#include "gifimage/qgifimage.h"
#include "giflib/gif_lib.h"
#include "giflib/gif_lib_private.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  char *result_path = NULL;
  QString file = 0;
  int fileStatus = 0;

 public slots:
  void openFile();

 private slots:
  void on_pushButton_screen_clicked();
  void move();
  void rot();
  void scale();
  void on_pushButton_gif_clicked();
  void makeGIF();
  void timerRun();
  void save_settings();
  void load_settings();

  void on_Change_back_clicked();

  void on_ChangeEdges_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void change_color();

  void on_horizontalSlider_scale_valueChanged(int value);
  void change_projection(int value);

 private:
  Ui::MainWindow *ui;
  QString file_name = "";
  QTimer *timer;
  QVector<QImage> gif;
  float count = 0;
  QMessageBox errorBox;
  QSettings *settings;

 signals:
  void pushButton_openFile_clicked();
};
#endif  // MAINWINDOW_H

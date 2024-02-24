#include "mainwindow.h"

#include "./ui_mainwindow.h"

int file_status_main = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  settings = new QSettings("school21", "TechnoTeam", this);
  load_settings();

  timer = new QTimer(0);
  connect(ui->pushButton_openFile, SIGNAL(clicked()), this, SLOT(openFile()));
  connect(ui->pushButton_move, SIGNAL(clicked()), this, SLOT(move()));
  connect(ui->pushButton_rotate, &QPushButton::clicked, this, &MainWindow::rot);
  connect(ui->pushButton_scale, &QPushButton::clicked, this,
          &MainWindow::scale);
  connect(timer, SIGNAL(timeout()), this, SLOT(timerRun()));
  connect(ui->comboBox_colorVert, &QComboBox::currentIndexChanged, this,
          &MainWindow::change_color);
  connect(ui->comboBox_colorEdge, &QComboBox::currentIndexChanged, this,
          &MainWindow::change_color);
  connect(ui->comboBox_colorBack, &QComboBox::currentIndexChanged, this,
          &MainWindow::change_color);
  connect(ui->doubleSpinBox_scale, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::scale);
  connect(ui->comboBox_projection, &QComboBox::currentIndexChanged, this,
          &MainWindow::change_projection);
  ui->widget->openFile(result_path, fileStatus);
}

MainWindow::~MainWindow() {
  save_settings();
  delete settings;
  delete ui;
}

void MainWindow::save_settings() {
  // init
  settings->setValue("settings_exist", 1);

  // for verticles
  settings->setValue("vert_r", ui->widget->vert_r);
  settings->setValue("vert_g", ui->widget->vert_g);
  settings->setValue("vert_b", ui->widget->vert_b);
  settings->setValue("verticles type", ui->widget->verticles);
  settings->setValue("verticles size", ui->widget->vertSize);

  // for edges
  settings->setValue("edge_r", ui->widget->edge_r);
  settings->setValue("edge_g", ui->widget->edge_g);
  settings->setValue("edge_b", ui->widget->edge_b);
  settings->setValue("line type", ui->widget->lineType);
  settings->setValue("line size", ui->widget->lineSize);

  // for background
  settings->setValue("background_color_red", ui->widget->back_r);
  settings->setValue("background_color_green", ui->widget->back_g);
  settings->setValue("background_color_blue", ui->widget->back_b);

  // for projection type
  settings->setValue("projection_type", ui->widget->projection);
  // for file
  settings->setValue("baseFile", file);
}

void MainWindow::load_settings() {
  // if where was init of settings before else nothing
  if (settings->value("settings_exist").toInt()) {
    // For Verticles
    int vert_type = settings->value("verticles type").toInt();
    switch (vert_type) {
      case 0:
        ui->radioButton_typeVert_none->setChecked(true);
        ui->widget->verticles = 0;
        break;
      case 1:
        ui->radioButton_typeVert_circle->setChecked(true);
        ui->widget->verticles = CIRCLE;
        break;
      case 2:
        ui->radioButton_typeVert_square->setChecked(true);
        ui->widget->verticles = SQUARE;
        break;
    }
    ui->widget->vertSize = settings->value("verticles size").toDouble();
    ui->doubleSpinBox_vertSize->setValue(ui->widget->vertSize);
    ui->widget->vert_r = settings->value("vert_r").toDouble();
    ui->widget->vert_g = settings->value("vert_g").toDouble();
    ui->widget->vert_b = settings->value("vert_b").toDouble();

    ui->spinBox_redVert->setValue(ui->widget->vert_r);
    ui->spinBox_greenVert->setValue(ui->widget->vert_g);
    ui->spinBox_blueVert->setValue(ui->widget->vert_b);
    // for file

    // For EDGES
    int edges_type = settings->value("line type").toInt();
    switch (edges_type) {
      case 1:
        ui->radioButton_typeEdge_solid->setChecked(true);
        ui->widget->lineType = SOLID;
        break;
      case 2:
        ui->radioButton_typeEdge_dotted->setChecked(true);
        ui->widget->lineType = DOTTED;
        break;
    }
    ui->widget->lineSize = settings->value("line size").toInt();
    ui->doubleSpinBox_edgeSize->setValue(ui->widget->lineSize);
    ui->widget->edge_r = settings->value("edge_r").toDouble();
    ui->widget->edge_g = settings->value("edge_g").toDouble();
    ui->widget->edge_b = settings->value("edge_b").toDouble();

    ui->spinBox_redEdge->setValue(ui->widget->edge_r);
    ui->spinBox_greenEdge->setValue(ui->widget->edge_g);
    ui->spinBox_blueEdge->setValue(ui->widget->edge_b);

    // For BACKGROUND
    ui->widget->back_r = settings->value("background_color_red").toDouble();
    ui->widget->back_g = settings->value("background_color_green").toDouble();
    ui->widget->back_b = settings->value("background_color_blue").toDouble();

    ui->spinBox_redBack->setValue(ui->widget->back_r);
    ui->spinBox_greenBack->setValue(ui->widget->back_g);
    ui->spinBox_blueBack->setValue(ui->widget->back_b);

    // For projection type
    ui->widget->projection = settings->value("projection_type").toInt();
    ui->comboBox_projection->setCurrentIndex(!ui->widget->projection);
    ui->widget->update();
  }
}

void MainWindow::openFile() {
  file = QFileDialog::getOpenFileName(0, "Выберите файл", ".", tr("(*.obj)"));
  QString f = NULL;
  char *name = NULL;
  char *buff = NULL;
  if (file != "") {
    ui->doubleSpinBox_scale->setValue(0.5);
    fileStatus = 1;
    QByteArray q_path = file.toLocal8Bit();
    result_path = q_path.data();
    buff = q_path.data();
    ui->widget->openFile(result_path, fileStatus);
    if (ui->widget->flag == 0) {
      ui->label_vert->setText(
          QString::number(ui->widget->syst.vert.amountVert));
      ui->label_face->setText(QString::number(ui->widget->syst.amountFacets));
      name = strtok(buff, "/");
      while (name != NULL) {
        f = QString::fromUtf8(name);
        name = strtok(NULL, "/");
      }
      ui->label_filename->setText(f);
    } else if (ui->widget->flag == -1)
      errorBox.critical(0, "Error", "File error!");
    else if (ui->widget->flag == -2)
      errorBox.critical(0, "Error", "Facets error!");
  } else {
    ui->label_filename->setText("File not valid");
  }
}

void MainWindow::on_pushButton_screen_clicked() {
  QString screen_name =
      QFileDialog::getSaveFileName(this, "Save screen", "", "*.jpeg *.bmp");
  if (!screen_name.isEmpty()) {
    ui->widget->grab().save(screen_name);
  }
}

void MainWindow::move() {
  char axis;
  if (ui->radioButton_moveX->isChecked()) axis = 'x';
  if (ui->radioButton_moveY->isChecked()) axis = 'y';
  if (ui->radioButton_moveZ->isChecked()) axis = 'z';
  ui->widget->move_model(ui->doubleSpinBox_move->value(), axis);
}

void MainWindow::rot() {
  char axis;
  if (ui->radioButton_rotateX->isChecked()) axis = 'x';
  if (ui->radioButton_rotateY->isChecked()) axis = 'y';
  if (ui->radioButton_rotateZ->isChecked()) axis = 'z';
  ui->widget->rot_model(ui->spinBox_rotate->value(), axis);
}

void MainWindow::scale() {
  if (fileStatus) ui->widget->scale_model(ui->doubleSpinBox_scale->value());
}

void MainWindow::on_pushButton_gif_clicked() {
  timer->start(100);
  timerRun();
  count = 0.0;
}

void MainWindow::timerRun() {
  ui->horizontalSlider_timer->setSliderPosition(count * 10);
  if (count <= 10.0) {
    gif.push_back(ui->widget->grab().toImage());
    count += 0.1;
  } else {
    makeGIF();
    timer->stop();
  }
}

void MainWindow::makeGIF() {
  QString gif_name =
      QFileDialog::getSaveFileName(this, "Save gif", "", tr("(*.gif)"));
  QGifImage gif_image(QSize(1200, 1200));
  gif_image.setDefaultDelay(100);

  for (QVector<QImage>::Iterator screen = gif.begin(); screen != gif.end();
       ++screen) {
    gif_image.addFrame(*screen);
  }
  gif_image.save(gif_name);
  gif.clear();
  count = 0.0;
}

void MainWindow::on_Change_back_clicked() {
  ui->widget->back_r = ui->spinBox_redBack->value();
  ui->widget->back_g = ui->spinBox_greenBack->value();
  ui->widget->back_b = ui->spinBox_blueBack->value();
  ui->widget->update();
}

void MainWindow::on_ChangeEdges_clicked() {
  if (ui->radioButton_typeEdge_dotted->isChecked())
    ui->widget->lineType = DOTTED;
  if (ui->radioButton_typeEdge_solid->isChecked()) ui->widget->lineType = SOLID;

  ui->widget->lineSize = ui->doubleSpinBox_edgeSize->value();

  ui->widget->edge_r = ui->spinBox_redEdge->value();
  ui->widget->edge_g = ui->spinBox_greenEdge->value();
  ui->widget->edge_b = ui->spinBox_blueEdge->value();

  ui->widget->update();
}

void MainWindow::on_pushButton_2_clicked()  // reload
{
  QByteArray q_path = file.toLocal8Bit();
  result_path = q_path.data();
  ui->widget->openFile(result_path, fileStatus);
  ui->doubleSpinBox_scale->setValue(0.5);
  ui->horizontalSlider_scale->setValue(50);
}

void MainWindow::on_pushButton_clicked() {
  if (ui->radioButton_typeVert_circle->isChecked())
    ui->widget->verticles = CIRCLE;
  if (ui->radioButton_typeVert_square->isChecked())
    ui->widget->verticles = SQUARE;
  if (ui->radioButton_typeVert_none->isChecked()) ui->widget->verticles = 0;

  ui->widget->vertSize = ui->doubleSpinBox_vertSize->value();

  ui->widget->vert_r = ui->spinBox_redVert->value();
  ui->widget->vert_g = ui->spinBox_greenVert->value();
  ui->widget->vert_b = ui->spinBox_blueVert->value();

  ui->widget->update();
}

void MainWindow::change_color() {
  if (ui->tabWidget_settings->isTabEnabled(0)) {
    if (ui->comboBox_colorVert->currentIndex() == 0) {
      ui->spinBox_redVert->setValue(255);
      ui->spinBox_greenVert->setValue(255);
      ui->spinBox_blueVert->setValue(255);
    }
    if (ui->comboBox_colorVert->currentIndex() == 1) {
      ui->spinBox_redVert->setValue(0);
      ui->spinBox_greenVert->setValue(0);
      ui->spinBox_blueVert->setValue(0);
    }
    if (ui->comboBox_colorVert->currentIndex() == 2) {
      ui->spinBox_redVert->setValue(255);
      ui->spinBox_greenVert->setValue(0);
      ui->spinBox_blueVert->setValue(0);
    }
    if (ui->comboBox_colorVert->currentIndex() == 3) {
      ui->spinBox_redVert->setValue(0);
      ui->spinBox_greenVert->setValue(255);
      ui->spinBox_blueVert->setValue(0);
    }
    if (ui->comboBox_colorVert->currentIndex() == 4) {
      ui->spinBox_redVert->setValue(0);
      ui->spinBox_greenVert->setValue(0);
      ui->spinBox_blueVert->setValue(255);
    }
  }
  if (ui->tabWidget_settings->isTabEnabled(1)) {
    if (ui->comboBox_colorEdge->currentIndex() == 0) {
      ui->spinBox_redEdge->setValue(255);
      ui->spinBox_greenEdge->setValue(255);
      ui->spinBox_blueEdge->setValue(255);
    }
    if (ui->comboBox_colorEdge->currentIndex() == 1) {
      ui->spinBox_redEdge->setValue(0);
      ui->spinBox_greenEdge->setValue(0);
      ui->spinBox_blueEdge->setValue(0);
    }
    if (ui->comboBox_colorEdge->currentIndex() == 2) {
      ui->spinBox_redEdge->setValue(255);
      ui->spinBox_greenEdge->setValue(0);
      ui->spinBox_blueEdge->setValue(0);
    }
    if (ui->comboBox_colorEdge->currentIndex() == 3) {
      ui->spinBox_redEdge->setValue(0);
      ui->spinBox_greenEdge->setValue(255);
      ui->spinBox_blueEdge->setValue(0);
    }
    if (ui->comboBox_colorEdge->currentIndex() == 4) {
      ui->spinBox_redEdge->setValue(0);
      ui->spinBox_greenEdge->setValue(0);
      ui->spinBox_blueEdge->setValue(255);
    }
  }
  if (ui->tabWidget_settings->isTabEnabled(2)) {
    if (ui->comboBox_colorBack->currentIndex() == 0) {
      ui->spinBox_redBack->setValue(0);
      ui->spinBox_greenBack->setValue(0);
      ui->spinBox_blueBack->setValue(0);
    }
    if (ui->comboBox_colorBack->currentIndex() == 1) {
      ui->spinBox_redBack->setValue(255);
      ui->spinBox_greenBack->setValue(255);
      ui->spinBox_blueBack->setValue(255);
    }
    if (ui->comboBox_colorBack->currentIndex() == 2) {
      ui->spinBox_redBack->setValue(255);
      ui->spinBox_greenBack->setValue(0);
      ui->spinBox_blueBack->setValue(0);
    }
    if (ui->comboBox_colorBack->currentIndex() == 3) {
      ui->spinBox_redBack->setValue(0);
      ui->spinBox_greenBack->setValue(255);
      ui->spinBox_blueBack->setValue(0);
    }
    if (ui->comboBox_colorBack->currentIndex() == 4) {
      ui->spinBox_redBack->setValue(0);
      ui->spinBox_greenBack->setValue(0);
      ui->spinBox_blueBack->setValue(255);
    }
  }
}

void MainWindow::on_horizontalSlider_scale_valueChanged(int value) {
  ui->doubleSpinBox_scale->setValue(
      (double)ui->horizontalSlider_scale->value() / 100.0);
}

void MainWindow::change_projection(int value) {
  if (ui->comboBox_projection->currentIndex() == 0) {
    ui->widget->projection = PARALLEL;
  }
  if (ui->comboBox_projection->currentIndex() == 1) {
    ui->widget->projection = CENTRAL;
  }
  ui->widget->update();
}

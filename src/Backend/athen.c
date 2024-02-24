#include "back.h"

/*!
    \brief Сдвиг модели на а по оси координат  
*/
void movement(res *syst, double a, char flag) {  // сдвиг на a по оси flag
  switch (flag) {
    case 'x':
      for (int i = 0; i < syst->vert.amountVert; i++)
        syst->vert.coord[i].x += a;
      break;
    case 'y':
      for (int i = 0; i < syst->vert.amountVert; i++)
        syst->vert.coord[i].y += a;
      break;
    case 'z':
      for (int i = 0; i < syst->vert.amountVert; i++)
        syst->vert.coord[i].z += a;
      break;
  }
}

/*!
    \brief Масштабирование в а раз 
*/
void mult(res *syst, double a) {  // масштаб (умножение в a раз)
  for (int i = 0; i < syst->vert.amountVert; i++) {
    syst->vert.coord[i].x *= a;
    syst->vert.coord[i].y *= a;
    syst->vert.coord[i].z *= a;
  }
}

/*!
    \brief В рамки f 
*/
void resize_frames(res *syst, double f) {
  double max = fabs(*syst->vert.rangeX[1] - *syst->vert.rangeX[0]);
  if (fabs(*syst->vert.rangeY[1] - *syst->vert.rangeY[0]) > max)
    max = fabs(*syst->vert.rangeY[1] - *syst->vert.rangeY[0]);
  if (fabs(*syst->vert.rangeZ[1] - *syst->vert.rangeZ[0]) > max)
    max = fabs(*syst->vert.rangeZ[1] - *syst->vert.rangeZ[0]);

  double scale = (f - (f * (-1))) / max;
  mult(syst, scale);
}  // в рамки f

/*!
    \brief Центрирование 
*/
void center_frames(res *syst) {
  double centerX = *syst->vert.rangeX[0] +
                   (*syst->vert.rangeX[1] - *syst->vert.rangeX[0]) / 2;
  double centerY = *syst->vert.rangeY[0] +
                   (*syst->vert.rangeY[1] - *syst->vert.rangeY[0]) / 2;
  double centerZ = *syst->vert.rangeZ[0] +
                   (*syst->vert.rangeZ[1] - *syst->vert.rangeZ[0]) / 2;

  for (int i = 0; i < syst->vert.amountVert; ++i) {
    syst->vert.coord[i].x -= centerX;
    syst->vert.coord[i].y -= centerY;
    syst->vert.coord[i].z -= centerZ;
  }
}  // центрирование координат

/*!
    \brief Поворот на угол по вокруг оси координат 
*/
void rot(res *syst, double angle, char flag) {  // поворот по оси flag
  angle = angle * M_PI / 180;
  for (int i = 0; i < syst->vert.amountVert; i++) {
    double tmp_x = syst->vert.coord[i].x;
    double tmp_y = syst->vert.coord[i].y;
    double tmp_z = syst->vert.coord[i].z;
    switch (flag) {
      case 'x':
        syst->vert.coord[i].y = cos(angle) * tmp_y - sin(angle) * tmp_z;
        syst->vert.coord[i].z = sin(angle) * tmp_y + cos(angle) * tmp_z;
        break;
      case 'y':
        syst->vert.coord[i].x = cos(angle) * tmp_x + sin(angle) * tmp_z;
        syst->vert.coord[i].z = -sin(angle) * tmp_x + cos(angle) * tmp_z;
        break;
      case 'z':
        syst->vert.coord[i].x = cos(angle) * tmp_x - sin(angle) * tmp_y;
        syst->vert.coord[i].y = sin(angle) * tmp_x + cos(angle) * tmp_y;
        break;
    }
  }
}

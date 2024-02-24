#include "back.h"

/*!
    \brief Считает количество вершин и граней в файле
*/
int obj_counter(const char *filename, res *syst) {
  int flag = 0;
  FILE *file = fopen(filename, "r");
  if (!file) return FILE_ERROR;
  char *str = NULL;
  size_t len = 0;
  int v_c = 0;
  int f_c = 0;
  while (getline(&str, &len, file) != -1) {
    if (*str == 'v' && *(str + 1) == ' ') v_c++;
    if (*str == 'f' && *(str + 1) == ' ') f_c++;
  }
  fclose(file);
  if (str) free(str);
  syst->vert.amountVert = v_c;
  syst->amountFacets = f_c;
  if (v_c == 0) flag = FILE_ERROR;
  return flag;
}

/*!
    \brief Ищет минимальное и максимальное значение по всем осям координат
*/
int minmax(res *syst, int v_c) {
  if (syst->vert.rangeX[0] == NULL && syst->vert.rangeX[1] == NULL) {
    syst->vert.rangeX[0] = &syst->vert.coord[v_c].x;
    syst->vert.rangeX[1] = &syst->vert.coord[v_c].x;
  }
  if (syst->vert.rangeY[0] == NULL && syst->vert.rangeY[1] == NULL) {
    syst->vert.rangeY[0] = &syst->vert.coord[v_c].y;
    syst->vert.rangeY[1] = &syst->vert.coord[v_c].y;
  }
  if (syst->vert.rangeZ[0] == NULL && syst->vert.rangeZ[1] == NULL) {
    syst->vert.rangeZ[0] = &syst->vert.coord[v_c].z;
    syst->vert.rangeZ[1] = &syst->vert.coord[v_c].z;
  }
  if (syst->vert.coord[v_c].x < *syst->vert.rangeX[0])
    syst->vert.rangeX[0] = &syst->vert.coord[v_c].x;
  if (syst->vert.coord[v_c].x > *syst->vert.rangeX[1])
    syst->vert.rangeX[1] = &syst->vert.coord[v_c].x;

  if (syst->vert.coord[v_c].y < *syst->vert.rangeY[0])
    syst->vert.rangeY[0] = &syst->vert.coord[v_c].y;
  if (syst->vert.coord[v_c].y > *syst->vert.rangeY[1])
    syst->vert.rangeY[1] = &syst->vert.coord[v_c].y;

  if (syst->vert.coord[v_c].z < *syst->vert.rangeZ[0])
    syst->vert.rangeZ[0] = &syst->vert.coord[v_c].z;
  if (syst->vert.coord[v_c].z > *syst->vert.rangeZ[1])
    syst->vert.rangeZ[1] = &syst->vert.coord[v_c].z;
  return 0;
}

/*!
    \brief Заполняет структуру данными из файла
*/
int matrix_fill(const char *filename, res *syst) {
  int flag = 0;
  FILE *file = fopen(filename, "r");
  if (!file) return FILE_ERROR;
  char *str = NULL;
  size_t len = 0;
  int v_c = 0, f_c = 0;  // counters
  char *istr;
  syst->vert.coord = calloc(syst->vert.amountVert, sizeof(points));
  syst->face = calloc(syst->amountFacets, sizeof(facet));
  while (getline(&str, &len, file) != -1 && flag == 0) {
    if (*str == 'v' && *(str + 1) == ' ') {
      strtok(str, " \n");
      istr = strtok(NULL, " \n");
      syst->vert.coord[v_c].x = atof(istr);
      istr = strtok(NULL, " \n");
      syst->vert.coord[v_c].y = atof(istr);
      istr = strtok(NULL, " \n");
      syst->vert.coord[v_c].z = atof(istr);
      istr = NULL;
      minmax(syst, v_c);
      v_c++;
    }
    if (*str == 'f' && *(str + 1) == ' ') {
      int tmp = 0;
      for (int i = 0; *(str + i) != '\n'; i++)
        if (*(str + i) == ' ') tmp++;
      syst->face[f_c].count = tmp;
      syst->face[f_c].f = calloc(tmp, sizeof(int));
      tmp = 0;
      strtok(str, " \n");
      istr = strtok(NULL, " \n");
      while (istr != NULL && flag == 0) {
        if (!sscanf(istr, "%d", &syst->face[f_c].f[tmp])) flag = FILE_ERROR;
        if (syst->face[f_c].f[tmp] > syst->vert.amountVert ||
            syst->face[f_c].f[tmp] < 0)
          flag = FACET_ERROR;
        else
          syst->face[f_c].f[tmp] -= 1;
        tmp++;
        istr = strtok(NULL, " \n");
      }
      f_c++;
    }
  }
  fclose(file);
  if (str) free(str);
  return flag;
}

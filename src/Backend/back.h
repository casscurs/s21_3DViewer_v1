#ifndef _BACK_H_
#define _BACK_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ERROR -1
#define FACET_ERROR -2

typedef struct coords {  // структура с координатами точек
  double x, y, z;
} points;

typedef struct vertexes {
  int amountVert;  // количество вершин
  points *coord;
  double *rangeX[2];
  double *rangeY[2];
  double *rangeZ[2];
} vertex;

typedef struct facets {
  int count;  // количество вершин в facet
  int *f;     // массив с вершинами
} facet;

typedef struct result {
  vertex vert;       // вершины
  facet *face;       // грани
  int amountFacets;  // количество структур facet
} res;

// PARSER
int obj_counter(const char *filename, res *syst);
int matrix_fill(const char *filename, res *syst);

// ATHENIAN TRANSFORMATIONS
void movement(res *syst, double a, char flag);
void mult(res *syst, double a);
void resize_frames(res *syst, double f);
void center_frames(res *syst);
void rot(res *syst, double angle, char flag);

// MEM FREE
void res_free(res *syst);

#endif

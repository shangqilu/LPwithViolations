#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include "headers.h"
#include "geometry.h"
void LoadDataLibSVMFormat(int n, int dimension, char* filename, PointSet &points);
void LoadDataCSVFormat(int n, int dimension, char* filename, PointSet &points);


#endif // FILEIO_H_INCLUDED

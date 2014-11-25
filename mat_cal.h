#ifndef MAT_CAL_H_INCLUDED
#define MAT_CAL_H_INCLUDED

#define DIM 1

void mxm(double a[2*DIM][2*DIM],double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]);
void mxv(double	a[2*DIM][2*DIM],double b[2*DIM],double c[2*DIM]);
void kxv(double a,double b[2*DIM],double c[2*DIM]);
void vxm(double	a[2*DIM],double b[2*DIM][2*DIM],double c[2*DIM]);
double vxv(double a[2*DIM],double b[2*DIM]);
void kxm(double a,double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]);
void mpm(double a[2*DIM][2*DIM],double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]);
void mmm(double a[2*DIM][2*DIM],double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]);
void vpv(double a[2*DIM],double b[2*DIM],double c[2*DIM]);
void mvxv(double a[2*DIM],double b[2*DIM],double c[2*DIM][2*DIM]);
void mupdate(double	a[2*DIM][2*DIM],double b[2*DIM][2*DIM]);
void vupdate(double	a[2*DIM],double b[2*DIM]);

#endif // MAT_CAL_H_INCLUDED

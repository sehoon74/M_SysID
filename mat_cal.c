#include "mat_cal.h"

/**********************************************/
/*            行列の掛け算  (mxm)             */
/**********************************************/

void mxm(double a[2*DIM][2*DIM],double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]){
	int 	i,j,k;
	double 	s;
	for ( i=0 ; i<2*DIM ; ++i )
	{
		for ( j=0 ; j<2*DIM ; ++j )
		{
			s=0.0;
			for ( k=0 ; k<2*DIM ; ++k ) {
				s+=a[i][k]*b[k][j];
			}
			c[i][j]=s;
		}
	}
}

/**********************************************/
/*            行列 × ベクトル (mxv)          */
/**********************************************/

void mxv(double	a[2*DIM][2*DIM],double b[2*DIM],double c[2*DIM]){
	int 	i,k;
	double 	s;
	for ( i=0 ; i<2*DIM ; ++i )
	{
		s=0.0;
		for ( k=0 ; k<2*DIM ; ++k ) {
			s+=a[i][k]*b[k];
		}
		c[i]=s;
	}
}

/**********************************************/
/*          スカラー × ベクトル (kxv)        */
/**********************************************/

void kxv(double a,double b[2*DIM],double c[2*DIM]){
	int k;

	for (k=0;k<2*DIM;++k){
		c[k]=a*b[k];
	}
}

/**********************************************/
/*       	printf("\n");
    ベクトル × 行列 (vxm)           */
/**********************************************/

void vxm(double	a[2*DIM],double b[2*DIM][2*DIM],double c[2*DIM]){
	int 	i,k;
	double 	s;
	for ( i=0 ; i<2*DIM ; ++i )
	{
		s=0.0;
		for ( k=0 ; k<2*DIM ; ++k ) {
			s+=a[k]*b[i][k];
		}
		c[i]=s;
	}
}

/**********************************************/
/*      ベクトルの内積 → スカラー (vxv)      */
/**********************************************/

double vxv(double a[2*DIM],double b[2*DIM]){
	int 	k;
	double 	s;

	s=0.0;
	for ( k=0 ; k<2*DIM ; ++k ) {
		s+=a[k]*b[k];
	}
	return(s);
}

/**********************************************/
/*       配列型の関数はないとのことか         */
/**********************************************/

/*
double vpv[2*DIM](a,b)
double a[2*DIM],b[2*DIM];
{
	int k;
	double c[2*DIM];

	for (k=0;k<2*DIM;k++){
		c[k]=a[k]+b[k];
	}
	return(c);
}
*/

/**********************************************/
/*         スカラー × 行列 (kxm)             */
/**********************************************/

void kxm(double a,double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]){
	int i,j;

	for ( i=0;i<2*DIM;i++ ){
		for ( j=0;j<2*DIM;j++ ){
			c[i][j]=a*b[i][j];
		}
	}
}

/**********************************************/
/*         行列同士の足し算 (mpm)             */
/**********************************************/

void mpm(double a[2*DIM][2*DIM],double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]){
	int i,j;

	for ( i=0;i<2*DIM;i++ ){
		for ( j=0;j<2*DIM;j++ ){
			c[i][j]=a[i][j]+b[i][j];
		}
	}
}


/**********************************************/
/*         行列同士の足し算 (mpm)             */
/**********************************************/

void mmm(double a[2*DIM][2*DIM],double b[2*DIM][2*DIM],double c[2*DIM][2*DIM]){
	int i,j;

	for ( i=0;i<2*DIM;i++ ){
		for ( j=0;j<2*DIM;j++ ){
			c[i][j]=a[i][j]-b[i][j];
		}
	}
}

/**********************************************/
/*       ベクトルどうしの足し算 (vpv)         */
/**********************************************/

void vpv(double a[2*DIM],double b[2*DIM],double c[2*DIM]){
	int k;

	for (k=0;k<2*DIM;k++){
		c[k]=a[k]+b[k];
	}
}

/**********************************************/
/*     ベクトルの掛け算 → 行列 (mvxv)        */
/**********************************************/


void mvxv(double a[2*DIM],double b[2*DIM],double c[2*DIM][2*DIM]){
	int 	i,j;

	for ( i=0 ; i<2*DIM ; ++i ) {
		for (j=0;j<2*DIM;++j) {
			c[i][j]=a[i]*b[j];
		}
	}
}

/**********************************************/
/*     行列の入力(入れ替え) (mupdate)        */
/**********************************************/

void mupdate(double	a[2*DIM][2*DIM],double b[2*DIM][2*DIM]){
	int 	i,j;

	for ( i=0 ; i<2*DIM ; ++i ) {
		for (j=0;j<2*DIM;++j) {
			b[i][j]=a[i][j];
		}
	}
}

/**********************************************/
/*     ベクトルの入力(入れ替え) (mupdate)     */
/**********************************************/

void vupdate(double	a[2*DIM],double b[2*DIM]){
	int 	i;

	for ( i=0 ; i<2*DIM ; ++i ) {
		b[i]=a[i];
	}
}

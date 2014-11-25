/*
オフラインの再帰型推定
*/

#include <stdio.h>
#include <math.h>
#include "mat_cal.h"

int main(void) {
	unsigned int i,j,k = 0;
	int t = 0;
	int	n=DIM;
	int fgt_cf;
	double theta[2*n],tmp[4],input,output,reg[2*n],vec_gain[2*n],tmp_vec2[2*n],diff_theta[2*n],theta_up[2*n],id_gain[n];
	double cov[2*n][2*n],tmp_mtrx[2*n][2*n],cov_up[2*n][2*n],diff_cov[2*n][2*n];
	double lambda,lambda2,scr_gain,innov,init_conv;
	double dummy[20];
	FILE *fp, *fp2;

	/* file open */

	fp=fopen("SV_ID.dat","r");
	if(fp == NULL) {
		printf("Cannot open log.dat. \n");
		return(-1);
	}

	if((fp2 = fopen("theta.dat", "w")) == NULL) {
		printf("Cannot save theta file\n");
		return -1;
	}
	init_conv=1000000.0;
	for (i=0;i<n;++i){
		reg[i]=0.0;
		reg[n+i]=0.0;
		theta[i]=0.0;
		theta[n+i]=0.0;
		for (j=0;j<n;++j){
			if ( i==j ) {
				cov[i][j]=init_conv;
				cov[n+i][n+j]=init_conv;
			}
			else {
				cov[i][j]=0;
				cov[n+i][n+j]=0;
			}
			cov[i][n+j]=0;
			cov[n+i][j]=0;
		}
	}

	tmp[2]=0.0;
	tmp[3]=0.0;
	fgt_cf=1;

/***********************************
	When using forgetting coeff.
************************************/

/*
	lambda=1-reg'*cov*cov*reg/(for_cof+reg'*cov*reg)/tr0;
	lambda2=lambda/fgt_cf;
*/

/***********************************
	When not using forgetting coeff.
************************************/

	lambda=1;

	while(feof(fp) ==0) {
		/* 入出力データの読み込み */
		fscanf (fp,"%lf %lf %lf %lf %lf %lf %lf",&dummy[0],&input,&output,&dummy[1],&dummy[2],&dummy[3]);	/** ファイルからのデータ読み込み  **/

		/** 係数や共分散行列の更新  **/
		/* cov = P(covariance matrix) in text */
		/* reg = xi(regressor) in text */
		for ( i=0;i<n; ++i ){
				tmp[0]=reg[i];
				reg[i]=tmp[2];
				tmp[2]=tmp[0];
		}
		reg[0]=input;


		/* vector adaptive gain = cov(matrix)*reg(vector) */
		mxv(cov,reg,vec_gain);

		/* scalar gain = 1/(1+reg'*cov*reg) */
		vxm(reg,cov,tmp_vec2);
		scr_gain=1/(1.0+vxv(reg,vec_gain));

		/* for covariance matrxi update cov*reg*reg'*cov  */
		mvxv(vec_gain,tmp_vec2,tmp_mtrx);

		/* innovation = measured y(output) - calculated y(reg*theta) */
		innov=output-vxv(reg,theta);

		/****************************************************
		 if this file is for the identification of STR
		innov must be defined as follows.
		******************************************************/

		/*
		innov = output - ctr_input - vxv(reg,theta);
		*/

		/* and ctr_input is last control input. so we must have a variable
		which holds one step last control input */

		/* adaptive gain = scalar gain * vector gain */
		kxv(scr_gain,vec_gain,tmp_vec2);

		/* increase of covariance = scalar gain * (cov*reg*reg'*cov) */
		kxm(scr_gain,tmp_mtrx,diff_cov);

		/* covariance update = old cov + increase of covariance */
		mmm(cov,diff_cov,cov_up);

		/* coefficient of update = cov * regressor */
		mxv(cov_up,reg,id_gain);

		/* increse of theta = adaptive gain * innovation */
		kxv(innov,id_gain,diff_theta);

		/* theta_new = theta_old + increase of theta */
		vpv(theta,diff_theta,theta_up);

		/* DEBUGGIN
		for (i=0;i<2*n;i++){
			printf("%lf ",cov[i][i]);
		}
		printf("\n");
		for (i=0;i<2*n;i++){
			printf("%lf ",diff_cov[i][i]);
		}
		printf("\n");
		*/

		/*	直接の代入は不可能だった	*/
		/* theta=theta_up; */
		/*  DEBUGGING
		for (i=0;i<2*n;i++){
			printf("%lf ",cov_up[i][i]);
		}
		printf("\n");
		*/

		/* REAL UPDATE ---> variable updating */
		mupdate(cov_up,cov);
		vupdate(theta_up,theta);

		/* DEBUGGING
		for (i=0;i<2*n;i++){
			printf("%lf ",cov[i][i]);
		}
		printf("\n");
		*/

		/* update of regressor */
		for ( i=0;i<n; ++i ){
				tmp[1]=reg[n+i];
				reg[n+i]=tmp[3];
				tmp[3]=tmp[1];
		}
		reg[n]=output;

		/********* for log ********/
		fprintf (fp2,"%lf ",(float)t++/1000.0);
		fprintf (fp2,"%lf ",input);
		for ( i=0; i<2*n;i++){
			fprintf (fp2,"%lf ",theta_up[i]);
		}
		fprintf (fp2,"\n");
		/********* for log ********/
	}
	fclose(fp);
	fclose(fp2);
	return 0;
}

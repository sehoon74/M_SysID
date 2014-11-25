// rt_skelet.c -- Contains the main() function, where the magic starts.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "globals.h"
#include "mseq.h"

void set_seed(void){
    int RSeed;
	time_t tt;
	int i;

	tt=time(NULL);
	RSeed=(0xFFFFFFFF & tt);
	for(i=0;i<5;i++)
		RSeed=1664525L*RSeed+1013904223L;
	RSeed &= 0x7FFFFFFF;
	RSeed=RSeed%60000;
	srand(RSeed);
}

int mseq(double *seq_out) {
    int downN = 16.0;
    double lpf_m;
    double old_lpf_m = 0.0;
    double t_lpf = 0.5/(double)downN;
    double sample_Time = 0.001;
    double lpf_a = (2.0*t_lpf-sample_Time)/(2.0*t_lpf+sample_Time);
    double lpf_b1 = sample_Time/(2.0*t_lpf+sample_Time);
    double lpf_b2 = lpf_b1;
    double newM_buf = 0.0;
    double M_in[RUNNING_T];
    double m;
    int Mseq[NUM_M];
    int i,i_m,i_down;;

	set_seed();
	for (i=0;i<NUM_M;i++) {
		while((m=(double)rand()/RAND_MAX)==0.0 || m==1.0);
		if (m<0.5) Mseq[i] = 1;
		else Mseq[i] = 0;
	}

	for (i = 0;  i < (int)(RUNNING_T/(int)downN) ; i++) {
		for (i_m = 0; i_m < NUM_M ;i_m++) {
			if (i_m==0) newM_buf = (Mseq[NUM_M-1])^(Mseq[NUM_M-2]);
			if (i_m !=(NUM_M-1)) Mseq[NUM_M-1- i_m]=Mseq[NUM_M-2- i_m];
			else Mseq[0] = newM_buf;
		}
		lpf_m = old_lpf_m + lpf_b1*((double)newM_buf*2.0-1.0);
		for ( i_down = 0; i_down < (int)downN; i_down++)
			seq_out[downN*i+i_down]=lpf_m;
		old_lpf_m = lpf_a*lpf_m + lpf_b2*((double)newM_buf*2.0-1.0);
	}

    FILE *mseq_file;
    mseq_file=fopen("mseq.csv","w+");
    for(i=0;i<RUNNING_T;i++){
        fprintf(mseq_file,"%f \n",M_in[i]);
	}
	fclose(mseq_file);

    return( 0 );
}

// rt_skelet.c -- Contains the main() function, where the magic starts.
//
#include "globals.h"
#include "encoder.h"
#include "dac.h"
#include "adc.h"
#include "mseq.h"
#include <rtai_lxrt.h>
#include <math.h>


int main(int argc, char *argv[]) {
// Local Main Declarations
    int i=0;

    double time_now;
//  double time_prv = 0.0;
    int data_length = DATANUMBER*RUNNING_T;
    double data[data_length];
    double con_input[RUNNING_T];
    float scaling =3.3;

    double thetaR[2];
    double thetaL[2];

    FILE *res_file;
    if (mseq(con_input)) {
        printf("Error in setting M sequence input.\n");
    } else {
        printf("M sequence input properly set.\n");
    }

    keep_on_running = 1;
    if ( (hard_timer_running == rt_is_hard_timer_running() ))    {
        printf(" Skip Hard Real Time Setting\n");
        sampling_interval = nano2count(NS_PER_mSEC * SAMPLE_TIME_mSEC);
    }
    else    {
        printf("Starting Real Time Timer...\n");
        rt_set_oneshot_mode();
        start_rt_timer(0);
        sampling_interval = nano2count(NS_PER_mSEC * SAMPLE_TIME_mSEC); // Sets the period of the concurrent task
    }
    if (!(loop_Task = rt_task_init_schmod(nam2num( "RTAI01" ), // Name
                2, // Priority
                0, // Stack Size
                0, // max_msg_size
                SCHED_FIFO, // Policy
                0 ) ) ) {// cpus_allowed
        printf("ERROR: Cannot initialize main task\n");
        exit(1);
    }

    mlockall(MCL_CURRENT | MCL_FUTURE);
    rt_make_hard_real_time();
    rt_task_make_periodic(loop_Task, rt_get_time() + sampling_interval, sampling_interval); //period in counts
    printf("rt_setting done.\n \n");

    enc_init();
    DA_on();

    while(keep_on_running)    {
        if (i == RUNNING_T) {
            keep_on_running = 0;
            break;
        }

        DA_out_set(0,0.0);
        DA_out_set(1,scaling*con_input[i]);
        DA_out_set(2,0.0);
        DA_out_set(3,0.0);
        DA_out();
    ////////// START: MEASUREMENT  ////////////////
    //// getting encoder information
		thetaR[0]= read_angle_rad(1);
		thetaR[1]= read_angle_rad(2);
        thetaL[0]= read_angle_rad(3);
		thetaL[1]= read_angle_rad(4);

    //// Data saving
		time_now = (double)rt_get_time_ns()/1E9;
		data[i*DATANUMBER]= time_now;
		data[i*DATANUMBER+1]=scaling*con_input[i];
		data[i*DATANUMBER+2]=thetaR[0];
		data[i*DATANUMBER+3]=thetaR[1];
		data[i*DATANUMBER+4]=thetaL[0];
		data[i*DATANUMBER+5]=thetaL[1];

		i++; // Count Loops.
		rt_task_wait_period(); // And waits until the end of the period.
    }
    // Program termination
    rt_task_delete(loop_Task);
    rt_make_soft_real_time();
    if ( hard_timer_running ){
        printf("stopping timer\n");
        stop_rt_timer();
    }

    DA_out_set(0,0.0);
    DA_out_set(1,0.0);
    DA_out_set(2,0.0);
    DA_out_set(3,0.0);
    DA_out();
    ctlstop();

    res_file=fopen("mseqout.csv","w+");
    for(i=0;i<RUNNING_T;i++){
        fprintf(res_file,"%f %f %f %f %f %f\n",data[i*DATANUMBER],data[i*DATANUMBER+1],data[i*DATANUMBER+2],data[i*DATANUMBER+3],data[i*DATANUMBER+4],data[i*DATANUMBER+5]);
	}
	fclose(res_file);
    return( 0 );
}

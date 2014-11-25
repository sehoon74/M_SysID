// rt_skelet.c -- Contains the main() function, where the magic starts.
//
#include "globals.h"
#include "encoder.h"
#include "dac.h"
#include "adc.h"
#include <rtai_lxrt.h>
#include <math.h>

int main(int argc, char *argv[]) {
    // Local Main Declarations
    int i=0;

    double time_now;
//    double time_prv = 0.0;
    double datas[DATALOOP];
    double ref_signal;

/// variables for encoder measurement
    double thetaR[2];
    double thetaL[2];

    FILE *res_file;

    keep_on_running = 1; // This flag will have the power of terminating the app!
    // Initialize the timer
    if ( (hard_timer_running == rt_is_hard_timer_running() ))    {
        printf(" Skip Hard Real Time Setting\n");
        sampling_interval = nano2count(NS_PER_mSEC * SAMPLE_TIME_mSEC); //Converts a value from
        //nanoseconds to internal
        // count units.
    }
    else    {
        printf("Starting Real Time Timer...\n");
        rt_set_oneshot_mode();
        start_rt_timer(0);
        sampling_interval = nano2count(NS_PER_mSEC * SAMPLE_TIME_mSEC); // Sets the period of the concurrent task
        // that will be launched later.
    }
    printf("timer done.\n");
    // Make the main process schedulable by the RTAI kernel layer
    if (!(loop_Task = rt_task_init_schmod(nam2num( "RTAI01" ), // Name
                2, // Priority
                0, // Stack Size
                0, // max_msg_size
                SCHED_FIFO, // Policy
                0 ) ) ) {// cpus_allowed
        printf("ERROR: Cannot initialize main task\n");
        exit(1);
    }
    printf("loop_task init done.\n");
    //pthread_create(&main_thread,NULL,main_loop, (void *)sampling_interval);
    //printf("pthread created.\n");
    //keep_on_running = 0;

    mlockall(MCL_CURRENT | MCL_FUTURE);
    printf("rt_initialization done.\n");
    // And now it will become hard real time.
    rt_make_hard_real_time();
    // ..with start time imposed by the variable expected.
    rt_task_make_periodic(loop_Task, rt_get_time() + sampling_interval, sampling_interval); //period in counts
    // Concurrent function Loop

    printf("rt_setting done.\n");

    enc_init();
    DA_on();
 //   time_prv = (double)rt_get_time_ns()/1E9;

    while(keep_on_running)    {
        if (i == DATALOOP/DATANUMBER) {
            keep_on_running = 0;
            break;
        }

        //ref_signal = 5.0*(1-cos(SAMPLE_TIME_mSEC*i*0.001*2.0*M_PI*1.0));
        ref_signal = 0.5*sin(SAMPLE_TIME_mSEC*i*0.001*2.0*M_PI*0.75);
        DA_out_set(0,ref_signal);
        DA_out_set(1,ref_signal);
        DA_out_set(2,ref_signal);
        DA_out_set(3,0.0);
        DA_out();
    ////////// START: MEASUREMENT  ////////////////
    //// getting encoder information
		thetaR[0]= read_angle_rad(1);
		thetaR[1]= read_angle_rad(2);
        thetaL[0]= read_angle_rad(3);
		thetaL[1]=-read_angle_rad(4);

    //// Data saving
		time_now = (double)rt_get_time_ns()/1E9;
		datas[i*DATANUMBER]= time_now;
		datas[i*DATANUMBER+1]=ref_signal;
		datas[i*DATANUMBER+2]=thetaR[0];
		datas[i*DATANUMBER+3]=thetaR[1];
		datas[i*DATANUMBER+4]=thetaL[0];
		datas[i*DATANUMBER+5]=thetaL[1];

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

    ctlstop();

    res_file=fopen("output.csv","w+");
    for(i=0;i<DATALOOP/DATANUMBER;i++){
        fprintf(res_file,"%f %f %f %f %f %f\n",datas[i*DATANUMBER],datas[i*DATANUMBER+1],datas[i*DATANUMBER+2],datas[i*DATANUMBER+3],datas[i*DATANUMBER+4],datas[i*DATANUMBER+5]);
	}
	fclose(res_file);
    return( 0 );
}

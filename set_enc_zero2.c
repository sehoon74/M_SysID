// rt_skelet.c -- Contains the main() function, where the magic starts.
//
#include "globals.h"
#include "encoder.h"
#include <rtai_lxrt.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Local Main Declarations

    int i=0;
    double data[4];
    FILE *enc_zero;

    keep_on_running = 1; // This flag will have the power of terminating the app!
    if ( (hard_timer_running == rt_is_hard_timer_running() ))    {
        printf(" Skip Hard Real Time Setting\n");
        sampling_interval = nano2count(NS_PER_mSEC * SAMPLE_TIME_mSEC); //Converts a value from
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
    enc_init();

    rt_make_hard_real_time();
    rt_task_make_periodic(loop_Task, rt_get_time() + sampling_interval, sampling_interval); //period in counts

    while(keep_on_running)    {
        if (i == 5000) {
            keep_on_running = 0;
            break;
        }
		i++; // Count Loops.
		rt_task_wait_period(); // And waits until the end of the period.
    }
    rt_task_delete(loop_Task);
    rt_make_soft_real_time();
    if ( hard_timer_running ){
        printf("Timer stopped.\n");
        stop_rt_timer();
    }

    printf("The present position will be the home position.\n");

    data[0]=read_angle_rad(1);
    data[1]=read_angle_rad(2);
    data[2]=read_angle_rad(3);
    data[3]=read_angle_rad(4);

    enc_zero=fopen("enc_zero.dat","w+");
    fprintf(enc_zero,"%f %f %f %f\n",data[0],data[1],data[2],data[3]);
	fclose(enc_zero);
    return( 0 );
}

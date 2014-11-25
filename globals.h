// globals.h file -- Contains the global declarations and necessary header includes.
//
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <rtai_lxrt.h>
#include <pthread.h>
#include <stdio.h>

#define TICK_TIME 3E9 // Three seconds
#define NS_PER_SEC 1E9
#define NS_PER_mSEC 1E6
#define SAMPLE_TIME_mSEC 1
#define RUNNING_T 10000

#define DATALOOP 24000 /*Running Time 10000(ms) X (time 1 + number of data 4 )*/
#define DATANUMBER 6

static RT_TASK *loop_Task; // Concurrent task
int hard_timer_running = 1;
int keep_on_running;
static RTIME sampling_interval;

#endif // GLOBAL_H_INCLUDED

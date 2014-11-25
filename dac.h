#ifndef DAC_H_INCLUDED
#define DAC_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>
#include <sys/signal.h>

#define DA_IO 0xd000

int DA_out_set(int ch,double Vout);
int DA_on();
int DA_out();
void ctlstop();


#endif // DAC_H_INCLUDED

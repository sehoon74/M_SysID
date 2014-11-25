#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>
#include <sys/signal.h>

#define AD_IO 0xd020

int AD_set();
double AD_msrm(int ch);

#endif // ADC_H_INCLUDED

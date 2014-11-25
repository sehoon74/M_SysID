//
//   2014 11/05 Sehoon OH,
//   PCI measurement test
//
// ********************************************
// must be in su mode for ioperm to work
// ********************************************
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/io.h>
#include <sys/signal.h>
#include <math.h>

#define ENCO_IO 0xd040

#define PI 3.141592

int enc_init();
double read_angle_rad(int ch);

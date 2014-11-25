#include "dac.h"

int DA_on() {
    outb(0x03,DA_IO+0x05);
    outb(0xff,DA_IO+0x1b);
	return 0;
}

int DA_out_set(int ch,double Vout) {
    unsigned short DAout;
    float Vmax=5.0;
    float Vmin=-5.0;
    unsigned char lmb,hmb;

	switch(ch){
        case 1:
        if(Vout >= Vmax)DAout=4095;
        else{
        if(Vout <= Vmin)DAout=0;
        else DAout = (short) ((Vout-Vmin)*4096.0/(Vmax-Vmin));
        }
        lmb=DAout;
        hmb=DAout/256;
        outb(ch,DA_IO+0x02);
        outb(lmb,DA_IO+0x00);
        outb(hmb,DA_IO+0x01);
	break;

	case 2:
        if(Vout >= Vmax)DAout=4095;
        else{
        if(Vout <= Vmin)DAout=0;
        else DAout = (short) ((Vout-Vmin)*4096.0/(Vmax-Vmin));
        }
        lmb=DAout;
        hmb=DAout/256;
        outb(ch,DA_IO+0x02);
        outb(lmb,DA_IO+0x00);
        outb(hmb,DA_IO+0x01);
	break;

	case 3:
        if(Vout >= Vmax)DAout=4095;
        else{
        if(Vout <= Vmin)DAout=0;
        else DAout = (short) ((Vout-Vmin)*4096.0/(Vmax-Vmin));
        }
        lmb=DAout;
        hmb=DAout/256;
        outb(ch,DA_IO+0x02);
        outb(lmb,DA_IO+0x00);
        outb(hmb,DA_IO+0x01);
	break;

	case 4:
        if(Vout >= Vmax)DAout=4095;
        else{
        if(Vout <= Vmin)DAout=0;
        else DAout = (short) ((Vout-Vmin)*4096.0/(Vmax-Vmin));
        }
        lmb=DAout;
        hmb=DAout/256;
        outb(ch,DA_IO+0x02);
        outb(lmb,DA_IO+0x00);
        outb(hmb,DA_IO+0x01);
	break;

	default:
	break;
	}
	return 0;
}

int DA_out() {
    outb(0x01,DA_IO+0x05);
	return 0;
}


void ctlstop(){
    unsigned char 	OutChar;
	OutChar=0;
    outb(0x00,DA_IO+0x1b);

	fprintf(stderr,"motor-stop : OutChar=%d\n",OutChar);

	return;
}

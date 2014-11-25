//
//   2014 11/05 Sehoon OH,
//   PCI measurement test
//
// ********************************************
// must be in su mode for ioperm to work
// ********************************************
//

#include "encoder.h"

int enc_init(){
	fprintf(stderr,"Encoder ADRESS: %4x\n",ENCO_IO);
	outb(0x0a,ENCO_IO+0x8);//1ch synchronous x4 Mode
	outb(0x0a,ENCO_IO+0x9);//2ch synchronous x4 Mode
	outb(0x0a,ENCO_IO+0xa);//3ch synchronous x4 Mode
	outb(0x0a,ENCO_IO+0xb);//4ch synchronous x4 Mode
	return 0;
}

// encoder reading

double read_angle_rad(int ch) {
	int cnt;
	double rad;
	unsigned int lbyt,mbyt,hbyt;
	unsigned int adr;
	unsigned int cpr = 950;

	switch(ch){
        case 1:
            adr = ENCO_IO;
            outb(0x02,ENCO_IO+0xc);
        break;

        case 2:
            adr = ENCO_IO+0x01;
            outb(0x08,ENCO_IO+0xc);
        break;

        case 3:
            adr = ENCO_IO+0x02;
            outb(0x20,ENCO_IO+0xc);
        break;

        case 4:
            adr = ENCO_IO+0x03;
            outb(0x80,ENCO_IO+0xc);
        break;

        default:
            adr=ENCO_IO;
        break;
	}

	lbyt=inb(adr);
	mbyt=inb(adr);
	hbyt=inb(adr);
	cnt = ((unsigned long)hbyt<<16)+((unsigned long)mbyt<<8)+lbyt;
	if((cnt & 0x800000) != 0) cnt=(cnt | 0xff000000);
	rad=(double)cnt*2.0*M_PI/(double)cpr/4.0;
	return(rad);
}

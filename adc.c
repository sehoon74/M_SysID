#include "adc.h" 

int AD_set() {
    outb(0x00,AD_IO+0x01); // single end input
//	outb(0x01,AD_IO+0x01); // differential input
	return 0;
}

double AD_msrm(int ch) { //input: 0~5V,2.5v ave
    double ADout;
    double Amax = 5.0;  // maximum input
    double Amin = -5.0; // minimum input
    unsigned short lmb,hmb;

	switch(ch){

        case 1:
            outb(0x00,AD_IO);
            while((inb(AD_IO+0x01) & 0x80)==0){;}
            lmb=inb(AD_IO);
            hmb=inb(AD_IO+0x01) & 0x0f;
            ADout=(double)((hmb<<8)+lmb)*(Amax-Amin)/4096.0+(Amax+Amin)/2.0;
        break;

        case 2:
            outb(0x01,AD_IO);
            while((inb(AD_IO+0x01) & 0x80)==0){;}
            lmb=inb(AD_IO);
            hmb=inb(AD_IO+0x01) & 0x0f;
            ADout=(double)((hmb<<8)+lmb)*(Amax-Amin)/4096.0+(Amax+Amin)/2.0;
        break;

        case 3:
            outb(0x02,AD_IO);
            while((inb(AD_IO+0x01) & 0x80)==0){;}
            lmb=inb(AD_IO);
            hmb=inb(AD_IO+0x01) & 0x0f;
            ADout=(double)((hmb<<8)+lmb)*(Amax-Amin)/4096.0+(Amax+Amin)/2.0;
        break;

        case 4:
            outb(0x03,AD_IO);
            while((inb(AD_IO+0x01) & 0x80)==0){;}
            lmb=inb(AD_IO);
            hmb=inb(AD_IO+0x01) & 0x0f;
            ADout=(double)((hmb<<8)+lmb)*(Amax-Amin)/4096.0+(Amax+Amin)/2.0;
        break;

        default:
            ADout=(Amax+Amin)/2.0;
        break;

	}
	return(ADout);
}

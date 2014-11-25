// rt_skelet.c -- Contains the main() function, where the magic starts.
//
#include "encoder.h"
#include <unistd.h>


int main(int argc, char *argv[]) {
    // Local Main Declarations
    float startCountDown = 5.0;
    double data[4];
    FILE *enc_zero;

 //   printf("The present position will be the home position.\n");
    enc_init();
 //   printf("The present position will be the home position2.\n");

    while(startCountDown > 0.0){
        printf("%0.0f seconds to end\n",startCountDown);
        startCountDown -= 1.0;
        sleep(1);
    }
    printf("The present position will be the home position.\n");

    data[0]= read_angle_rad(1);
    data[1]= read_angle_rad(2);
    data[2]= read_angle_rad(3);
    data[3]=-read_angle_rad(4);

    enc_zero=fopen("enc_home.dat","w+");
    fprintf(enc_zero,"%f %f %f %f\n",data[0],data[1],data[2],data[3]);
	fclose(enc_zero);
    return( 0 );
}

LXRT_LIBLAGS = $(shell /usr/realtime/bin/rtai-config --lxrt-ldflags)
LXRT_CFLAGS = $(shell /usr/realtime/bin/rtai-config --lxrt-cflags)
CC=g++
CFLAGS=-c -Wall

all: output_test

param_id: id_batch.c mat_cal.o
	$(CC) -o param_id id_batch.c mat_cal.o -lm

mat_cal.o: mat_cal.c mat_cal.h
	$(CC) $(CFLAGS) mat_cal.c

swept_id: ID_swept.c encoder.o dac.o adc.o
	$(CC) -o swept_id ID_swept.c encoder.o adc.o dac.o $(LXRT_CFLAGS) $(LXRT_LIBLAGS)

mseq_id: ID_mseq.c mseq.c mseq.h encoder.o dac.o adc.o
	$(CC) -o mseq_id ID_mseq.c mseq.o encoder.o adc.o dac.o $(LXRT_CFLAGS) $(LXRT_LIBLAGS)

mseq.o: mseq.c mseq.h
	$(CC) $(CFLAGS) mseq.c

enc_zero: set_enc_zero.o encoder.o
	$(CC) set_enc_zero.o encoder.o -o enc_zero

set_enc_zero.o: set_enc_zero.c encoder.c encoder.h
	$(CC) $(CFLAGS) $(LXRT_CFLAGS) $(LXRT_LIBLAGS) set_enc_zero.c

output_test: main.o encoder.o adc.o dac.o
	$(CC) main.o encoder.o adc.o dac.o $(LXRT_LIBLAGS) -o output_test

main.o: main.c encoder.c dac.c adc.c encoder.h adc.h dac.h globals.h
	$(CC) $(CFLAGS) $(LXRT_CFLAGS) $(LXRT_LIBLAGS) main.c

adc.o: adc.c adc.h
	$(CC) $(CFLAGS) $(LXRT_LIBLAGS) $(LXRT_CFLAGS) adc.c

dac.o: dac.c dac.h
	$(CC) $(CFLAGS) $(LXRT_LIBLAGS) $(LXRT_CFLAGS) dac.c

encoder.o: encoder.c encoder.h
	$(CC) $(CFLAGS) $(LXRT_LIBLAGS) $(LXRT_CFLAGS) encoder.c

clean:
	rm *.o

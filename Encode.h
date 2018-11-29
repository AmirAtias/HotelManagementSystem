#ifndef __ENCODE_H
#define __ENCODE_H

#include "Hotel.h"
#define ENCODING_NUM 255
#define MIN_SIZE_RAND 0
#define MAX_SIZE_RAND 7
#define SIZE_OF_BYTE 8
#define SIZE_OF_BIT 1
#define FILE_NAME "hotel.bin"
#define FILE_RANDON_NUM "randomNum.txt"


void encodingBits(void *, int, int);
void unEncodingBits(void *, int, int);
void swapBits(unsigned char*, int);
void WriteToFile(Hotel *, char*, char *);
void readFromFile(Hotel *, char*, char *);
int checkIfOpen(FILE *);
int readRandomFromText(char *);
int writeRandomToText(int, char *);
void printErrorClose();
#endif
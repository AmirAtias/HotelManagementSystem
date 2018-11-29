
#ifndef __ROOM_H
#define _ROOM_H

#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#define ACCESS_SIZE 7
#define IS_FULL 6
#define MASK_VAL 1
#define MIN_CHOICE 0
#define MAX_CHOICE 6

typedef struct {
	int numOfBeds;
	unsigned char roomInclude;
}Room;

void startRandom();
void getRoomDetails(Room *);
void setRoom(Room *);
int getBitFromRight(unsigned char *, int);
void setBitFromRight(unsigned char *, int, int);
int ChooseAccessory();
int searchAccessory(Room *, int);
void searchAllRooms(int, Room*, ...);
#endif
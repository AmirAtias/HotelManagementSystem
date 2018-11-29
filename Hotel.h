#ifndef __HOTEL_H
#define _HOTEL_H

#include <stdlib.h>
#include "Room.h"
#define MAX_SIZE_FLOOR 100
#define MIN_SIZE 1

typedef struct {
	int NumOfRooms;
	int NumOfFloors;
	Room** building;
}Hotel;

void setHotel(Hotel*);
void readHotel(const Hotel*);
void searchAccessoryHotel(const Hotel*, int);

#endif
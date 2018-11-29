#include "Room.h"

void setBitFromRight(unsigned char * ch, int index, int value)
{
	unsigned char mask = MASK_VAL;
	mask <<= index;

	if (value == 1)
		*ch |= mask;
	else
	{
		mask = ~mask;
		*ch &= mask;
	}
}


int getBitFromRight(unsigned char *ch, int index)
{
	unsigned char mask = MASK_VAL; // 00000001
	mask = mask << index;
	if ((*ch&mask) == 0)
		return 0;
	else
		return 1;

}


void startRandom() {
	srand((unsigned)time(NULL)); // should only be called once
}


void setRoom(Room * room) {
	printf("create a new room!\n");

	unsigned char randValue = (unsigned char)(rand() % 128);
	printf("enter the amount of beds\n");
	scanf("%d", &room->numOfBeds);
	room->roomInclude = randValue;
}


void getRoomDetails(Room *room) {
	int i;
	//make a list of accessories with similar size .
	char* accessories[ACCESS_SIZE] = { "view to pool","balcony     ","kettle      ","wifi        ","couch       ","TV          ","is full     " };
	printf("there is %d beds in the room\n", room->numOfBeds);
	printf("the room include:\n");
	for (i = 0; i < ACCESS_SIZE; i++) {
		printf("%s :", accessories[i]);
		if (getBitFromRight(&(room->roomInclude), i))
			printf("yes\n");
		else
			printf("no\n");

	}

}


int searchAccessory(Room *room, int index) {
	return getBitFromRight(&(room->roomInclude), index);
}


int ChooseAccessory() {
	int choice;
	do {
		printf("please enter number between 0-6\n");
		printf("for check if the room include view to pool press 0\n");
		printf("for check if the room include balcony press 1 \n");
		printf("for check if the room include kettle press 2 \n");
		printf("for check if the room include  wifi press 3  \n");
		printf("for check if the room include couch press 4\n");
		printf("for check if the room include TV press  5 \n");
		printf("for check if the room is full press 6\n");
		scanf("%d", &choice);
	} while (choice < MIN_CHOICE || choice>MAX_CHOICE);
	return choice;
}


void searchAllRooms(int index, Room* room, ...) {
	va_list allRooms;
	Room* currentRoom;
	int roomIndex = 1;
	va_start(allRooms, room);
	currentRoom = room;
	while (currentRoom != NULL) {
		printf("the %d room from the list\n", roomIndex);
		if (searchAccessory(currentRoom, index))
			getRoomDetails(currentRoom);
		else
			printf("the room is not include this accessory\n");
		roomIndex++;
		currentRoom = va_arg(allRooms, Room*);
	}
	va_end(allRooms);
}

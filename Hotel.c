#include "Hotel.h"


void setHotel(Hotel *casaBenjamin) {
	int i, j;
	do {
		printf("please enter how many floors do you want(bigger then 0)?\n");
		scanf("%d", &casaBenjamin->NumOfFloors);
	} while (casaBenjamin->NumOfFloors < MIN_SIZE);
	do {
		printf("please enter how many rooms do you want for each floor(1-100)?\n");
		scanf("%d", &casaBenjamin->NumOfRooms);
	} while (casaBenjamin->NumOfRooms < MIN_SIZE || casaBenjamin->NumOfRooms > MAX_SIZE_FLOOR);
	casaBenjamin->building = (Room**)malloc(casaBenjamin->NumOfFloors * sizeof(Room*));
	for (i = 0; i < casaBenjamin->NumOfFloors; i++) {
		casaBenjamin->building[i] = (Room*)malloc(casaBenjamin->NumOfRooms * sizeof(Room));
		//set room
		for (j = 0; j < casaBenjamin->NumOfRooms; j++) {
			setRoom(&(casaBenjamin->building[i][j]));
		}
	}

}


void readHotel(const Hotel *casaBenjamin) {
	int i, j;
	for (i = 0; i < casaBenjamin->NumOfFloors; i++) {

		printf("\n\nfloor number: %d \n", (i + 1));
		for (j = 0; j < casaBenjamin->NumOfRooms; j++) {
			printf("\nroom number: %d\n", (i + 1) * MAX_SIZE_FLOOR + j);
			getRoomDetails(&(casaBenjamin->building[i][j]));
		}
	}
}


void searchAccessoryHotel(const Hotel *casaBenjamin, int accessory) {
	int i, j;
	for (i = 0; i < casaBenjamin->NumOfFloors; i++) {
		for (j = 0; j < casaBenjamin->NumOfRooms; j++) {
			if (searchAccessory(&(casaBenjamin->building[i][j]), accessory)//check if the room include accessory and if the room is empty
				&& !(getBitFromRight(&(casaBenjamin->building[i][j].roomInclude), IS_FULL))) {
				printf("room number %d\n", (i + 1) * MAX_SIZE_FLOOR + j);
				getRoomDetails(&(casaBenjamin->building[i][j]));
			}
		}
	}
}

#include "Encode.h"
freeHotel(Hotel *casaBenjamin) {
	int i;
	//free hotel
	for (i = 0; i < casaBenjamin->NumOfFloors; i++) {
		free(casaBenjamin->building[i]);
	}
	free(casaBenjamin->building);
}


void main(int argc, char*  argv[]) {
	printf("wellcome to casa benjamin!\n");
	Hotel casaBenjamin;
	startRandom();//use random numbers
	if (argc == 2) {
		readFromFile(&casaBenjamin, argv[1], FILE_RANDON_NUM);
	}
	else {
		setHotel(&casaBenjamin);
	}
	if (casaBenjamin.NumOfRooms > 2)
		searchAllRooms(1, &(casaBenjamin.building[0][0]), &(casaBenjamin.building[0][1]), &(casaBenjamin.building[0][2]), NULL);
	int choice, flag = 1;
	printf("\n\n");

	//create a menu
	do {
		printf("would you like to see hotel status? press 1\n");
		printf("would you like to see all the empty rooms which include specific accessory? press 2\n");
		printf("for exit press 3\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
			readHotel(&casaBenjamin);
			break; }
		case 2: {
			int accessChoice = ChooseAccessory();
			searchAccessoryHotel(&casaBenjamin, accessChoice);
			break;
		}
		case 3: {
			printf("hope you enjoy visit casa benjamin,GoodBye!!\n");
			flag = 0;
			break;
		}
		default: {
			printf("you should enter a number between 1-3");
			break;
		}
		}

	} while (flag);


	WriteToFile(&casaBenjamin, FILE_NAME, FILE_RANDON_NUM);
	freeHotel(&casaBenjamin);
	system("pause");
}

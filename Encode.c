#include "Encode.h"

int writeRandomToText(int randValue, char * numberFile) {
	FILE* f = fopen(numberFile, "w");
	if (!checkIfOpen(f))
		return 0;
	fprintf(f, "%d", randValue);
	if (fclose(f) == EOF) {//check if the succes close the file
		printErrorClose();
		return 0;
	}
	return 1;
}

int readRandomFromText(char * numberFile) {
	FILE* f = fopen(numberFile, "r");
	if (!checkIfOpen(f))
		return -1;
	int randValue;
	fscanf(f, "%d", &randValue);
	if (fclose(f) == EOF) {//check if the succes close the file
		printErrorClose();
		randValue = -1;
	}
	return randValue;
}

void WriteToFile(Hotel * casaBenjamin, char* HotelFile, char *numberFile) {
	int randValue = (rand() % SIZE_OF_BYTE), Numfloors, numOfRooms, i, j;
	if (!writeRandomToText(randValue, numberFile))// try to write for a text file
		return;
	FILE* f = fopen(HotelFile, "wb");
	if (!checkIfOpen(f))
		return;
	//write hotel
	Numfloors = casaBenjamin->NumOfFloors;
	numOfRooms = casaBenjamin->NumOfRooms;
	encodingBits(&(casaBenjamin->NumOfFloors), sizeof(int), randValue);
	fwrite(&(casaBenjamin->NumOfFloors), sizeof(int), 1, f);
	encodingBits(&(casaBenjamin->NumOfRooms), sizeof(int), randValue);
	fwrite(&(casaBenjamin->NumOfRooms), sizeof(int), 1, f);
	for (i = 0; i < Numfloors; i++) {
		for (j = 0; j < numOfRooms; j++) {
			encodingBits(&(casaBenjamin->building[i][j]), sizeof(Room), randValue);
		}  //encoding each room
		fwrite((casaBenjamin->building[i]), sizeof(Room), numOfRooms, f);  //write all the floor
	}
	if (fclose(f) == EOF)//check if the succes close the file
		printErrorClose();
}

int checkIfOpen(FILE *f) {
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return 0;
	}
	else
		return 1;
}

void printErrorClose() {
	printf("can not close this file!");
}

void readFromFile(Hotel *casaBenjamin, char* HotelFile, char *numberFile) {
	int randValue, i, j;
	randValue = readRandomFromText(numberFile);
	if (randValue == EOF)//check if success read from file text
		return;
	FILE* f = fopen(HotelFile, "rb");
	if (!checkIfOpen(f))
		return;
	fread(&(casaBenjamin->NumOfFloors), sizeof(int), 1, f);
	unEncodingBits(&(casaBenjamin->NumOfFloors), sizeof(int), randValue);
	fread(&(casaBenjamin->NumOfRooms), sizeof(int), 1, f);
	unEncodingBits(&(casaBenjamin->NumOfRooms), sizeof(int), randValue);
	casaBenjamin->building = (Room**)malloc(casaBenjamin->NumOfFloors * sizeof(Room*));
	for (i = 0; i < casaBenjamin->NumOfFloors; i++) {
		casaBenjamin->building[i] = (Room*)malloc(casaBenjamin->NumOfRooms * sizeof(Room));
		fread((casaBenjamin->building[i]), sizeof(Room), casaBenjamin->NumOfRooms, f);
		for (j = 0; j < casaBenjamin->NumOfRooms; j++) {
			unEncodingBits(&(casaBenjamin->building[i][j]), sizeof(Room), randValue);
		}
	}
	if (fclose(f) == EOF)//check if the succes close the file
		printErrorClose();
}

void encodingBits(void *address, int typeSize, int randValue) {
	unsigned char* val = (char*)address;
	int i;
	for (i = 0; i < typeSize; i++) {
		//3.a
		swapBits((val + i), randValue);
		//3.b
		(*(val + i)) ^= ENCODING_NUM;
		//3.c
		unsigned char temp = *(val + i);
		temp = (temp) >> randValue;
		*(val + i) = *(val + i) << (SIZE_OF_BYTE - randValue);
		*(val + i) |= temp;

	}
}


void unEncodingBits(void *address, int typeSize, int randValue) {
	// reverse
	unsigned char* val = (char*)address;
	int i;
	for (i = 0; i < typeSize; i++) {
		//c
		unsigned char temp = *(val + i);
		temp = (temp) << randValue;
		*(val + i) = *(val + i) >> (SIZE_OF_BYTE - randValue);
		*(val + i) |= temp;
		//b
		(*(val + i)) ^= ENCODING_NUM;
		//a
		swapBits((val + i), randValue);

	}
}


void swapBits(unsigned char* val, int randValue) {
	int tempval = getBitFromRight((val), randValue);
	if (randValue == MAX_SIZE_RAND) {
		setBitFromRight((val), randValue, (getBitFromRight(val, MIN_SIZE_RAND)));
		setBitFromRight(val, MIN_SIZE_RAND, tempval);
	}
	else {
		setBitFromRight(val, randValue, (getBitFromRight(val, (randValue + SIZE_OF_BIT))));
		setBitFromRight(val, (randValue + SIZE_OF_BIT), tempval);
	}
}
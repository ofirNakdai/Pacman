#include "Random.h"

int generateRandomNumber(int lowestValue, int highestValue)
{
	int randomNumber = 0;
	randomNumber = (rand() % (highestValue - lowestValue + 1)) + lowestValue;
	return randomNumber;
}

void printRandomNumber(int lowestValue, int highestValue)
{
	int randomNumber = 0;
	randomNumber = (rand() % (highestValue - lowestValue + 1)) + lowestValue;
	printf("%d ", randomNumber);
}
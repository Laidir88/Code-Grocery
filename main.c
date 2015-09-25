/****************************************************************************************************
* Programmer: Tovah Kerr																			*
* Date: 2/22/12																						*
* Class: CptS 122 Spring 2012 Sec. 01																*
*																									*
* Program Description: This pgrogram simulates two grocerty store lines by using queues.			*
*					   Two queues are created, an express lane queue, and a standard lane queue		*
*                      Each is seeded with random numbers.											*
****************************************************************************************************/

#include "pa4.h"

int main(void)
{
	Queue pQueueExpress = {NULL, NULL}, pQueueStd = {NULL, NULL};
	int userTime = 25;


	srand((unsigned)(time(NULL))); //Seed the program for random numbers
		
	printf("Express Lane Sim:\n");
	expressLaneQueue(&pQueueExpress, userTime); //Run Express Lan simulation
	

	printf("Standard Lane Sim:\n");
	standardLaneQueue(&pQueueStd, userTime); //Run Standard Lan Simulation
	return 0;
}

#ifndef PA4_H
#define PA4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define XPRESS_MIN 1
#define XPRESS_MAX 5
#define STD_MIN 1
#define STD_MAX 8
#define XPRESS_SRV_MIN 1
#define XPRESS_SRV_MAX 5
#define STD_SRV_MIN 3
#define STD_SRV_MAX 8


typedef struct queueNode

{

     int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
     int serviceTime;   // Random time; varies between express and normal lanes; units in minutes
     int totalTime;     // totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes
	 struct queueNode *pNext;

} QueueNode;

typedef struct queue
{
	QueueNode *pHead;
	QueueNode *pTail;
}Queue;


int isEmpty(Queue queue);
void initQueue(Queue  *pQueue);
QueueNode *makeQueueNode(QueueNode data);
void enqueue(Queue *pQueue, QueueNode data);
void dequeue(Queue *pQueue);
void printQueueRecursive(Queue queue);
void expressLaneQueue(Queue *pQueue, int userTime); //Different pointers for each queue remember!!!
void standardLaneQueue(Queue *pQueue, int userTime);


#endif
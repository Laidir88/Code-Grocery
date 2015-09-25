#include "pa4.h"

/**************************************************************************************************
* Function Name: isEmpty																		  *
* Date Created: 2/16/12																			  *
* Date Last Modified:2/16/12																	  *
* Description: function checks if queue is empty											      *
* Input Parameters: queue																	      *
* Returns: 1 if empty 0 if not																	  *
* Preconditions: queue is initilized in main													  *
* Post Conditions: queue head pointer is checked if null, return 1 if yes						  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
int isEmpty(Queue queue)
{
	int status = 0; //False is 0 True is 1

	if (queue.pHead == NULL)
	{
		status = 1;
	}

	return status;
}

/**************************************************************************************************
* Function Name: initQueue																		  *
* Date Created: 2/16/12																			  *
* Date Last Modified:2/16/12																	  *
* Description: function initializes queue node												      *
* Input Parameters: pointer to queue														      *
* Returns: NONE																					  *
* Preconditions: address to queue is passed in													  *
* Post Conditions: queue head and tail pointer is initialized to NULL							  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
void initQueue(Queue  *pQueue)
{
	pQueue ->pHead = NULL;
	pQueue ->pTail = NULL;
}
/**************************************************************************************************
* Function Name: makeQueueNode																	  *
* Date Created: 2/16/12																			  *
* Date Last Modified:2/16/12																	  *
* Description: function makes a new queue node based on data passed in						      *
* Input Parameters: data in queue node														      *
* Returns: pointer to queue node																  *
* Preconditions: data is passed in																  *
* Post Conditions: a node in queue is populated													  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
QueueNode *makeQueueNode(QueueNode data)
{
	QueueNode *pTMem = NULL;

	pTMem = (QueueNode *) malloc (sizeof(QueueNode));

	if (pTMem != NULL) //Memory allocated
	{
		pTMem -> customerNumber = data.customerNumber;
		pTMem -> serviceTime = data.serviceTime;
		pTMem -> totalTime = data.totalTime;
		pTMem -> pNext = NULL;
	}

	return pTMem;
}
/**************************************************************************************************
* Function Name: enqueue																		  *
* Date Created: 2/16/12																			  *
* Date Last Modified:2/16/12																	  *
* Description: function adds new queue to tail of queue/back of queue						      *
* Input Parameters: pointer to queue and data in queue										      *
* Returns: NONE																					  *
* Preconditions: address to queue is passed in along with data									  *
* Post Conditions: new queue node is added	to tail end											  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
void enqueue(Queue *pQueue, QueueNode data)
{
	QueueNode *pTMem = NULL;

	pTMem = makeQueueNode(data);

	if (isEmpty(*pQueue))
	{
		pQueue ->pHead = pTMem;
	}
	else //not empty
	{
		pQueue ->pTail ->pNext = pTMem;
	}

	pQueue ->pTail = pTMem;
	
}
/**************************************************************************************************
* Function Name: dequeue																		  *
* Date Created: 2/16/12																			  *
* Date Last Modified:2/16/12																	  *
* Description: function takes off queue node form head of queue								      *
* Input Parameters: pointer to queue														      *
* Returns: NONE																					  *
* Preconditions: address to queue is passed in													  *
* Post Conditions: head node is freed from memory												  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
void dequeue(Queue *pQueue)
{
	QueueNode *pTMem = NULL;

	if (!isEmpty(*pQueue) && (pQueue->pHead == pQueue->pTail)) //Populated Queue with one node
	{
		pTMem = pQueue ->pHead;
		pQueue ->pHead = pQueue ->pHead ->pNext;
		pQueue->pTail = NULL;
		free(pTMem);
	}
	else if (!isEmpty(*pQueue)) //More than one node in queue
	{
		pTMem = pQueue ->pHead;
		pQueue ->pHead = pQueue ->pHead ->pNext;
		free(pTMem);
	}
	
}
/**************************************************************************************************
* Function Name: printQueueRecursive															  *
* Date Created: 2/16/12																			  *
* Date Last Modified:2/16/12																	  *
* Description: function prints queue														      *
* Input Parameters: queue																	      *
* Returns: NONE																					  *
* Preconditions: queue is passed in																  *
* Post Conditions: queue is printed in order													  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
void printQueueRecursive(Queue queue)
{

	if (!isEmpty(queue))
	{
		printf("Customer: %d \n", (queue.pHead)->customerNumber);
		printf("ServiceTimeLeft: %d min \n", (queue.pHead) ->serviceTime);
		printf("TotalTime so far: %d min\n", (queue.pHead) ->totalTime);
		queue.pHead = queue.pHead ->pNext;
		printQueueRecursive(queue);
	}

}
/**************************************************************************************************
* Function Name: expressLaneQueue																  *
* Date Created: 2/18/12																			  *
* Date Last Modified:2/18/12																	  *
* Description: function simiulates queue based on express lane random numbers. It prints the queue*
*			   after each new node or loss of node.												  *
* Input Parameters: pointer to queue, simulated time scale by user in min					      *
* Returns: NONE																					  *
* Preconditions: address to queue is passed in along with user time								  *
* Post Conditions: queue is added to and subtracted from until user time is reached				  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
void expressLaneQueue(Queue *pQueue, int userTime)
{
	int randArrivalTime = 0, serviceTime= 0, totalTime = 0;
	int timePassed = 0, custNum = 0, addCount = 0; //addcount = 0 is FALSE
	QueueNode data = {0, 0, 0, NULL};
	
	
	while (timePassed <= userTime) 
	{
		addCount = 0; //Reset each add
		randArrivalTime = (rand() % (XPRESS_MAX - XPRESS_MIN + 1) + XPRESS_MIN);
		timePassed = randArrivalTime + timePassed; //Keeps track of customer number based on available service time.
		custNum ++;
		serviceTime = (rand() % (XPRESS_SRV_MAX - XPRESS_SRV_MIN + 1) + XPRESS_SRV_MIN);
		totalTime = serviceTime + totalTime;

		data.customerNumber = custNum;
		data.serviceTime = serviceTime;
		data.totalTime = totalTime;
		
		 if(!isEmpty(*pQueue))
		 {
				
			if (pQueue->pHead->serviceTime > randArrivalTime) //Person in front not standing long enough to leave yet
			{
				enqueue(pQueue, data);
				addCount = 1; //Node was added
				pQueue->pHead->serviceTime = pQueue->pHead->serviceTime - randArrivalTime; //denotes timepassed while being serviced but not done
			}
			else //Person in front serviced before next addition
			{
				while (pQueue->pHead != NULL && pQueue->pHead->serviceTime <= randArrivalTime) //Keep servicing guy in front till new guy arrives
				{
					randArrivalTime = randArrivalTime - (pQueue->pHead->serviceTime); //Time less guy already served
					dequeue(pQueue);
				}
			}

			if (addCount != 1) //No Node added so add next guy
			{
				enqueue(pQueue, data);
			}
		 }
		 else
		 {
			enqueue(pQueue, data);
		 }
		printQueueRecursive(*pQueue);		
		system("PAUSE");
		system("cls");
	}
	
}
/**************************************************************************************************
* Function Name: standardLaneQueue																  *
* Date Created: 2/18/12																			  *
* Date Last Modified:2/18/12																	  *
* Description: function simiulates queue based on standard lane random numbers. It prints the	  *
*			   queue after each new node or loss of node.										  *
* Input Parameters: pointer to queue, simulated time scale by user in min					      *
* Returns: NONE																					  *
* Preconditions: address to queue is passed in along with user time								  *
* Post Conditions: queue is added to and subtracted from until user time is reached				  *
* Test Conditions: NOT TESTED																	  *
**************************************************************************************************/
void standardLaneQueue(Queue *pQueue, int userTime)
{
	int randArrivalTime = 0, serviceTime= 0, totalTime = 0;
	int timePassed = 0, custNum = 0, addCount = 0; //addcount = 0 is FALSE
	QueueNode data = {0, 0, 0, NULL};
	
	
	while (timePassed <= userTime) 
	{
		addCount = 0; //Reset each add
		randArrivalTime = (rand() % (STD_MAX - STD_MIN + 1) + STD_MIN);
		timePassed = randArrivalTime + timePassed; //Keeps track of customer number based on available service time.
		custNum ++;
		serviceTime = (rand() % (STD_SRV_MAX - STD_SRV_MIN + 1) + STD_SRV_MIN);
		totalTime = serviceTime + totalTime;

		data.customerNumber = custNum;
		data.serviceTime = serviceTime;
		data.totalTime = totalTime;
		
		 if(!isEmpty(*pQueue))
		 {
				
			if (pQueue->pHead->serviceTime > randArrivalTime) //Person in front not standing long enough to leave yet
			{
				enqueue(pQueue, data);
				addCount = 1; //Node was added
				pQueue->pHead->serviceTime = pQueue->pHead->serviceTime - randArrivalTime; //denotes time passed while being serviced but not done
			}
			else //Person in front serviced before next addition
			{
				while (pQueue->pHead != NULL && pQueue->pHead->serviceTime <= randArrivalTime) //Keep servicing guy in front till new guy arrives
				{
					randArrivalTime = randArrivalTime - (pQueue->pHead->serviceTime); //Time less guy already served
					dequeue(pQueue);
				}
			}

			if (addCount != 1) //No Node added so add next guy
			{
				enqueue(pQueue, data);
			}
		 }
		 else
		 {
			enqueue(pQueue, data);
		 }
		printQueueRecursive(*pQueue);		
		system("PAUSE");
		system("cls");
	}


	
}
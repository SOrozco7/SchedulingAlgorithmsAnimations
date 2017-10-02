// algorithm3_SRTF.c
// to compile, do this: gcc -lncurses algorithm3_SRTF.c
// To compile this, you need to have ncurses installed

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "schedulingAlgorithmAnimation.h"

#define DELAY 30000
#define TOT_PROCESSES 4

int main() {

	int max_y = 0, max_x = 0;
	char* toDraw = "*";
	int totalWaitingTime = 0;
	int remainingProcessesCounter = TOT_PROCESSES;

	int arrLoY[TOT_PROCESSES], arrLoX[TOT_PROCESSES], arrHiY[TOT_PROCESSES], arrHiX[TOT_PROCESSES];
	int arrNext_x[TOT_PROCESSES];
	int arrDirection[TOT_PROCESSES];

	int cpuLoY, cpuLoX, cpuHiY, cpuHiX;
	cpuLoY = 0;
	cpuLoX = 70;
	cpuHiY = 20;
	cpuHiX = 90;

	char arrProcessesNames[TOT_PROCESSES][10];
	strcpy(arrProcessesNames[0], "A");
	strcpy(arrProcessesNames[1], "B");
	strcpy(arrProcessesNames[2], "C");
	strcpy(arrProcessesNames[3], "D");

	int arrProcessTotalTime[TOT_PROCESSES] = {9,5,7,1};
	int arrProcessCurrentTime[TOT_PROCESSES] = {0, 0, 0, 0};
	int flagBack[TOT_PROCESSES] = {0,0,0,0};
    int arrProcessArriva[TOT_PROCESSES] = {0,2,3,5};

	char intToStr[10];
	char arrProcessesBurstTimes[TOT_PROCESSES][10];
	char arrArrival[TOT_PROCESSES][10];
	
	sprintf(intToStr, "%d", arrProcessTotalTime[0]);
	strcpy(arrProcessesBurstTimes[0], intToStr);
	
	sprintf(intToStr, "%d", arrProcessTotalTime[1]);
	strcpy(arrProcessesBurstTimes[1], intToStr);
		
	sprintf(intToStr, "%d", arrProcessTotalTime[2]);
	strcpy(arrProcessesBurstTimes[2], intToStr);
		
	sprintf(intToStr, "%d", arrProcessTotalTime[3]);
	strcpy(arrProcessesBurstTimes[3], intToStr);

	sprintf(intToStr, "%d", arrProcessArriva[0]);
	strcpy(arrArrival[0], intToStr);

	sprintf(intToStr, "%d", arrProcessArriva[1]);
	strcpy(arrArrival[1], intToStr);

	sprintf(intToStr, "%d", arrProcessArriva[2]);
	strcpy(arrArrival[2], intToStr);

	sprintf(intToStr, "%d", arrProcessArriva[3]);
	strcpy(arrArrival[3], intToStr);

	int processIsFinished[TOT_PROCESSES] = {0, 0, 0, 0};

	arrLoY[3] = 8;
	arrLoX[3] = 0;
	arrHiY[3] = 12;
	arrHiX[3] = 8;
	arrNext_x[3] = 0;
	arrDirection[3] = 1;

	arrLoY[2] = 8;
	arrLoX[2] = 12;
	arrHiY[2] = 12;
	arrHiX[2] = 20;
	arrNext_x[2] = 0;
	arrDirection[2] = 1;

	arrLoY[1] = 8;
	arrLoX[1] = 24;
	arrHiY[1] = 12;
	arrHiX[1] = 32;
	arrNext_x[1] = 0;
	arrDirection[1] = 1;

	arrLoY[0] = 8;
	arrLoX[0] = 36;
	arrHiY[0] = 12;
	arrHiX[0] = 44;
	arrNext_x[0] = 0;
	arrDirection[0] = 1;

	initscr();
	noecho();
	curs_set(FALSE);
	int z = 0;
	int tempMayor = 100;
	int j =0;

	// Global var `stdscr` is created by the call to `initscr()`
	getmaxyx(stdscr, max_y, max_x);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	int counter = 0;
	int turno = 0;

	while(remainingProcessesCounter > 0) {

		clear();
		drawCPU(cpuLoY, cpuLoX, cpuHiY, cpuHiX);
		mvprintw(0, 0, "First-come-first-serve algorithm");
		drawRemainingProcessesCounter(2, 20, remainingProcessesCounter);
		drawTotalWaitingTime(3, 12, totalWaitingTime);

		for(int i = 0; i < TOT_PROCESSES; i++){

			if(arrProcessArriva[i] <= totalWaitingTime){

				if(processIsFinished[i] == 1)
					continue;

				draw2(arrLoY[i], arrLoX[i], arrHiY[i], arrHiX[i], toDraw, counter, arrProcessesNames[i], arrProcessesBurstTimes[i], arrArrival[i]);
				
				if(tempMayor < arrProcessTotalTime[i]){

					tempMayor = arrProcessTotalTime[i];
				}
			}
			
			if(i != turno){
		
				continue;
			}
	 			
			if(arrLoX[i] < cpuLoX + (cpuHiX - cpuLoX)/2 - 4)
	 			advanceCoordinates(&arrNext_x[i], &arrLoX[i], &arrHiX[i], &arrDirection[i], max_x);

	 		if(arrLoX[i] == cpuLoX + (cpuHiX - cpuLoX)/2 - 4){
	 		
	 		    if(arrProcessTotalTime[i] == 0){

	 				remainingProcessesCounter--;
	 				processIsFinished[i] = 1;


	 				while(z != 4){

	 					if(processIsFinished[z] == 0 && arrProcessTotalTime[z] < tempMayor)
	 						turno = z;
	 					
	 					z++;
	 				}
	 				
	 				z = 0; 
	 			}

	 			else{

	 				totalWaitingTime++;
	 				arrProcessCurrentTime[i]++;
	 				arrProcessTotalTime[i]--;
	 			}
	 		}

	 		while(z != 4){

	 			if(arrProcessArriva[z] <= totalWaitingTime){

	 				if(arrProcessTotalTime[z] < arrProcessTotalTime[i] && processIsFinished[z] == 0)
	 				{		
	 					switch(i){
							
							case 3:
							arrLoY[3] = 8;
							arrLoX[3] = 0;
							arrHiY[3] = 12;
							arrHiX[3] = 8;
							arrNext_x[3] = 0;
							arrDirection[3] = 1;
							break;

							case 2:

							arrLoY[2] = 8;
							arrLoX[2] = 12;
							arrHiY[2] = 12;
							arrHiX[2] = 20;
							arrNext_x[2] = 0;
							arrDirection[2] = 1;
							break;

							case 1:

							arrLoY[1] = 8;
							arrLoX[1] = 24;
							arrHiY[1] = 12;
							arrHiX[1] = 32;
							arrNext_x[1] = 0;
							arrDirection[1] = 1;
							break;

							case 0:

							arrLoY[0] = 8;
							arrLoX[0] = 36;
							arrHiY[0] = 12;
							arrHiX[0] = 44;
							arrNext_x[0] = 0;
							arrDirection[0] = 1;
							break;
						}

	 					turno = z;
	 				}
	 			}

	 			z++;
	 		}

	 		z = 0;
	 	}
	 
		sprintf(intToStr, "%d", arrProcessTotalTime[0]);
		strcpy(arrProcessesBurstTimes[0], intToStr);
		
		sprintf(intToStr, "%d", arrProcessTotalTime[1]);
		strcpy(arrProcessesBurstTimes[1], intToStr);
			
		sprintf(intToStr, "%d", arrProcessTotalTime[2]);
		strcpy(arrProcessesBurstTimes[2], intToStr);
			
		sprintf(intToStr, "%d", arrProcessTotalTime[3]);
		strcpy(arrProcessesBurstTimes[3], intToStr);

	 	refresh();
	 	usleep(5*DELAY);
	 	counter++;
	}

	usleep(10*DELAY);
	endwin();

	return 0;
}
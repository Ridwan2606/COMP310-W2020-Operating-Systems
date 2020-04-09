#include <string.h>
#include <stdio.h>
#include<math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "pcb.h"
#include "ram.h"
#include "interpreter.h"

int no_process=1;

int countTotalPages(FILE* fp){
	int no_lines=0;
    char buffer[1000];

    while (!feof(fp)){
        fgets(buffer,999,fp);
        no_lines++;
    }
    rewind(fp);

    int no_pages = no_lines/4;
    if (no_lines%4 != 0) no_pages++;
    return no_pages;
}

void loadPage(int pageNumber, FILE* fp, int frameNumber){
    //Moves file pointer to the required page
    fseek(fp, pageNumber*4, SEEK_SET); 
    // Adds that page to the required frame in RAM
    addFrameToRAM(fp,frameNumber);
    //Reset file pointer to the beginning of the while
    rewind(fp);
}

/*
void loadPage2(int pageNumber, FILE* fp, int frameNumber){
	rewind(fp);//reset file pointer just in case
	//move the fp to the proper page
	int currentPage=0;
	char line[256];
	for(currentPage;currentPage!=pageNumber;currentPage++){//while currentpage != desired page number
		int count=0;
		while(fgets(line, sizeof(line), fp)!=NULL && count<3){
			count++;
		}
	}
	//we are at the correct page.
	//load next 4 (or less) instructions into RAM
	int cell = frameNumber*4;
	int offset=0;;
	char* tmp;
	while(fgets(line, sizeof(line), fp)!=NULL && offset<=3){
		tmp = &line[0];
		loadInstruction(tmp, cell+offset);
		offset++;
	}
	rewind(fp);
	//page is loaded into desired frame and fp is reset to beginning
}
*/

int findFrame(){
    int found = FALSE;
    int frame = -1;

    //For each consecutive frame
    for (int i=0; i< 10; i++){

        // If 1st cell in that frame is null, examine the 3 other cells
        if (ram[i*4]==NULL){
            int found = TRUE;
            //examining other 3 cells
            for (int j = i*4+1; j < i*4+4; j++)
            {
                if (ram[j] != NULL){
                    found = FALSE;
                    break;
                }
            }

            // If found, initialise frame
            if (found) {
                frame = i*4;
                break;
            }
        }
    }

    return frame;

    /*
	int frame = -1;
	for(int i=0;i<10;i++){
		if(getInstruction(i*4)=='\0'){
			frame=i;
			break;
		}
	}
	return frame;
    */
}

/*
Returns the frame number that will be allocated to that PCB passed.
This frame will be taken from another PCB
*/
int findVictim(struct PCB* p){
	int final_frameNum = 0;
	int frameNum = rand()%10;
	if(isAPageOf(p,frameNum)==-1){ 
		final_frameNum = frameNum;
	}else{
		while(isAPageOf(p,frameNum)==0){
			frameNum=(frameNum+1)%10;
		}
		final_frameNum = frameNum;
	}

    /*
	//NEED TO CATCH THIS
	if(findFrameOwner(toReturn)==NULL){//if victim owner is not in ready list, then VICTIM PCB IS STILL RUNNING ABORT TAKING FRAME.
		//try a different frame.
		toReturn = findVictim(p);
	}
    */
	return final_frameNum;
}

/*
int findVictim2(struct PCB* p){
	int toReturn = 0;
	int ran = rand()%10;
	if(hasFrame(p,ran)==1){//if the pcb does not have the random frame
		toReturn = ran;
	}else{
		while(hasFrame(p,ran)==0){
			ran=(ran+1)%10;
		}
		toReturn = ran;
	}
	//NEED TO CATCH THIS
	if(findFrameOwner(toReturn)==NULL){//if victim owner is not in ready list, then VICTIM PCB IS STILL RUNNING ABORT TAKING FRAME.
		//try a different frame.
		toReturn = findVictim(p);
	}

	return toReturn;
}
*/

// WE CAN USE HIS BUT CHANGED THE findFrameOwner NAME....
// WE CAN USE HIS BUT CHANGED THE findFrameOwner NAME....
// WE CAN USE HIS BUT CHANGED THE findFrameOwner NAME....
// WE CAN USE HIS BUT CHANGED THE findFrameOwner NAME....
int updatePageTable(struct PCB* p, int pageNumber, int frameNumber, int victimFrame){
    // If we have a victim
	if(victimFrame != -1){
        // Find the victim pcb
		struct PCB* victim = getFrameOwner(victimFrame);
        // Find which page lost its frame and set its value to -1 
		for(int i=0;i<10;i++){
			if(victim->pageTable[i]==victimFrame){ 
				victim->pageTable[i]=-1; 
			}
		}
	}
	//Update to which frame the page of the current pcb will now point to
	p->pageTable[pageNumber]=frameNumber;
	return 0;
}

/*
Returns 1 for success, 0 for error
*/
int launcher(FILE* fp1){
	//Creating the file in the backing store
	char newProcess[50] = "BackingStore/file";
	char* extension = ".txt";
	char buffer[8];
	sprintf(buffer,"%d",no_process);
	strcat(newProcess,buffer);
	strcat(newProcess,extension);
	no_process++;

	//Opening the newly created file
	FILE* fp2 = fopen(newProcess,"w+");

	//If file cannot be opened, return error 0
	if (fp2 == NULL){
		return 0;
	}

	//Copying content of file passed into the newly created file in the backing store
	char c;
	c = fgetc(fp1);
	while(c != EOF){
		fputc(c,fp2);
		c = fgetc(fp1);
	}

	//Close file opened for reading
	fclose(fp1);
	//Resets pointer to the backing store file
	rewind(fp2);

	// Getting the max pages for that program and creates a PCB for it
	int no_page = countTotalPages(fp2);
	struct PCB* pcb = makePCB(no_page);

	// Finding a frame for 1st page
	int frame = findFrame();
	int victimFrame = -1;
	if(frame == -1){//if so, we need to find victim
		victimFrame = findVictim(pcb);
		frame = victimFrame;
	}
	
	//Clear memory at that frame
	removeFrameFromRAM(frame);
	//loads first page at that frame
	loadPage(0, fp2, frame);
	//Update pageTable
	updatePageTable(pcb,0,frame,victimFrame);//updates pcb's page table
	// Sets PC to first line in RAM of that frame
	pcb->PC = frame*4;
	
	// If program requires more than 1 page, load the 2nd page.
	if(no_page>1){

		//Finding a frame for the 2nd page
		frame = findFrame();
		victimFrame = -1;
		if(frame == -1){
			victimFrame = findVictim(pcb);
			frame = victimFrame;
		}
		//Clear memory at that frame
		removeFrameFromRAM(frame);
		//loads first page at that frame
		loadPage(1, fp2, frame);
		//Update pageTable
		updatePageTable(pcb,1,frame,victimFrame);//updates pcb's page table
	}
	//This pcb is now added into the ready queue as its first 2 pages are loaded in RAM.
	addToReady(pcb);

	return 1;
}
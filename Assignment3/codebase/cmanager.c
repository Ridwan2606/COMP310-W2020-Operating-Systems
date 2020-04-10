#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "pcb.h"
#include "ram.h"

int processCounter=0;

int countTotalPages(FILE* fp){
	int lines=0;
	for(char c = getc(fp); c != EOF ;c = getc(fp)){
		if(c == '\n'){
			lines++;
		}
	}
	rewind(fp);
	int numPages = lines/4;
	if((lines%4) > 0){
		numPages++;
	}
	return numPages;
}

void loadPage(int pageNumber, FILE* fp, int frameNumber){
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

int findFrame(){
	int frame = -1;
	for(int i=0;i<10;i++){
		if(getInstruction(i*4)=='\0'){
			frame=i;
			break;
		}
	}
	return frame;
}

int findVictim(struct PCB* p){
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

int updatePageTable(struct PCB* p, int pageNumber, int frameNumber, int victimFrame){
	//if victim is selected, then victimFrame != -1
	if(victimFrame != -1){//if we have victim frame
		struct PCB* victim = findFrameOwner(victimFrame);
		for(int i=0;i<10;i++){
			if(victim->pageTable[i]==victimFrame){ //find the page
				victim->pageTable[i]=-1; //set to -1
			}
		}
	}
	//Now tell the new pcb the frame is theirs
	p->pageTable[pageNumber]=frameNumber;
	return 0;
}

int launcher(FILE* fp1){
	int success = 0;

	//open new file
	char newProcess[50] = "BackingStore/process";
	char* suffix = ".txt";
	char buffer[8];
	sprintf(buffer,"%d",processCounter);
	strcat(newProcess,buffer);
	strcat(newProcess,suffix);
	processCounter++;
	FILE* fp2 = fopen(newProcess,"w+");

	//copy file to backing store
	char c;
	c = fgetc(fp1);
	while(c != EOF){
		fputc(c,fp2);
		c = fgetc(fp1);
	}
	fclose(fp1);
	rewind(fp2);//reset fp2 in backing_store
	//BackingStore is prepped, file has been copied into it.
	//We can now load file's instruction into memory.
	//but before we do that, we need to create the pcb.
	//construct the new pcb - Still need to define PC = frame*4 and pageTable[0] = frame
	int numPages = countTotalPages(fp2);
	struct PCB* pcb = constructPCB(numPages, fp2);

	int frame = findFrame();
	int victimFrame = -1;
	if(frame == -1){//if so, we need to find victim
		victimFrame = findVictim(pcb);
		frame = victimFrame;
	}
	//Found frame. Now load page 0 into RAM
	clearFrame(frame);
	loadPage(0, fp2, frame);
	updatePageTable(pcb,0,frame,victimFrame);//updates pcb's page table
	pcb->PC = frame*4;//PC is now set
	//now load second page (if necessary
	if(numPages>1){
		frame = findFrame();
		victimFrame = -1;
		if(frame == -1){//if so, we need to find victim
			victimFrame = findVictim(pcb);
			frame = victimFrame;
		}
		//Found frame. Now load page 1 into RAM
		clearFrame(frame);
		loadPage(1, fp2, frame);
		updatePageTable(pcb,1,frame,victimFrame);//updates pcb's page table
	}
	//The first two pages of the process have now been loaded into memory.
	//now add pcb to ready list
	addToReady(pcb);

	return success;
}
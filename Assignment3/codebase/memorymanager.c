#include <string.h>
#include <stdio.h>
#include<math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "pcb.h"
#include "ram.h"


int countTotalPages(FILE* fp){
	double no_lines=0;
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
}

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
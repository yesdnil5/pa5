//
//  SearchIndexer.c
//  
//
//  Created by Advait Shukla on 11/5/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Indexer.h"

int sizeArray(char* size){
	int i = 0;
	int len = strlen(size);
	char temp[len-2];
	
	while(i<(len-2)){
		if(isdigit(size[i]))
			temp[i]=size[i];
		else
			return 0;
		i++;
	}
	int s = atoi(temp);
	if(size[len-1]!='B')
		return 0;
	if(size[len-2]=='K')
		return (1024*s);
	if(size[len-2]=='M')
		return (1048576*s);
	if(size[len-2]=='G')
		return (1073741824*s);
	return 0;
}



int main(int argc, char **argv){
	int m;
	int p;
	int i;
	char* temp;
    if(argc > 4){
        printf("Incorrect number of arguments. Closing program...\n");
        return 1;
    }
    FILE *invertedList;
	invertedList = fopen(argv[argc-1],"r");
	if(!invertedList){
		fprintf(stderr, "File could not be opened. Program will close.\n");
		return 1;
	}
	
	if(argc==4){
		if(strcmp("-m", argv[1])==0){
			m = sizeArray(argv[2]);
			if(m == 0){
				printf("Incorrect size for memory.\n");
				return 1;
			}
			p = 0;
		}
		else{
			printf("Incorrect format.\n");
			return 1;
		}		
	}

    int searchOp = 0;
    Node head = NULL;
    
	do{
		char* token;
		char* win; //input
		char c;
		int count = 0;
		Node ptr;
		char *str;
		p=0;
		searchOp = 0;
		
		printf("Search> ");
		
		while(( c = fgetc( stdin )) != '\n'){
			p++; 
			if(p == 1){
				win = (char *)malloc(sizeof(char));
				win[0] = c;
			}
			else{
				char *temp = win;
				win = (char *)malloc((p+1)*sizeof(char));
				strcpy(win,temp);
				win[p-1] = c;
				win[p] = '\0';
				free(temp);
			}
		}
		
		if(win[0] == '\n'){ 
			printf("Invalid input. Enter: 'q' to quit. \n \t 'sa' for and search \n \t 'so' for or search\n");
			continue;
		}
		if(win[0] == 'q'){
			searchOp = 1;
		}
			
		if(searchOp!=1){
			str = win;
			token = strtok(str," ");
			
			if(strcmp(token, "sa")==0)
				searchOp = 2;
			else if(strcmp(token, "so")==0)
				searchOp = 3;
			else{
				printf("Invalid input. Enter: 'q' to quit. \n \t 'sa' for and search \n \t 'so' for or search\n");
				continue;
			}
			
			token = strtok(NULL," ");
			
			printf("%s\n", token);
			
			while(token != NULL){
				count++;
				ptr = searchFile(token, invertedList);
				head = searchLL(ptr, head);
				token = strtok(NULL," ");
			}
		}
		fclose(invertedList);
		invertedList = fopen(argv[argc-1],"r");
		free(win);
	}while(searchOp != 1);
	
	fclose(invertedList);
}

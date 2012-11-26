//
//  Indexer.c
//  
//
//  Created by Advait Shukla on 10/19/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "Indexer.h"
#include "tokenizer.h"

fileP newscantxt(char* tok, FILE* inFile){
    int i = 0;
	char line[200];
	char* token;
	char word[200];
	char* file;
	int wordnum = 1;
	int occ;
	const char delimList[] = " <>";
	int match = 0;
	fileP head = NULL;
	
	while(fscanf(inFile, "%s", line)!= EOF){ //scans inFile line by line
		TokenizerT tnize = TKCreate((char*)delimList,line);
		
		while((token = TKGetNextToken(tnize))!=0){
		
			if(wordnum==2){
				for(i = 0; token[i]; i++){
  					word[i] = tolower(token[i]);
				}
				word[i]='\0';
				
				if(strcmp(word, tok)==0){
					match = 1;
				}
				else
					match = 0;
			}
			
			else if(strcmp(token, "/list\0")==0){
				wordnum=0;
			}
			
			else if(strcmp(token, "list\0")==0){
				wordnum=1;
			}
			
			else if(wordnum%2==1){
				if(match == 1){
					fileP fp = (fileP)(malloc(sizeof(struct fileInfo)));
					fp->nextFile = NULL;
					fp->path = token;
					
					if(head==NULL){
						head = fp;
						head->nextFile = NULL;
					}
					
					else{
						fileP tem = head;
						while(tem->nextFile!=NULL){
							tem=tem->nextFile;
						}
						tem->nextFile = fp;
					}
				}
			}
			
		}
		wordnum++;
	}
	
	return head;
}

Node searchFile(char* token, FILE *infile){
	
	Node ptr = (Node)malloc(sizeof(struct hashNode));
	ptr->files = newscantxt(token, infile);
	return ptr;
}

void NodeDestroy(Node nd){
	fileP node = nd->files;
	while(node!=NULL){
		fileP temp = node;
		node = node->nextFile;
		free(temp);
	}
	free(nd->files);
	free(nd->word);
	free(nd->nextHash);
	free(nd->nextWord);
	free(nd->prevHash);
	free(nd);
}


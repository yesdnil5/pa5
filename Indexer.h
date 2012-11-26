//
//  Indexer.h
//  
//
//  Created by Advait Shukla on 10/20/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _Indexer_h
#define _Indexer_h

struct fileInfo{ 
    char *path;
    int occurence;
    struct fileInfo *nextFile;
    struct fileInfo *last;
};
typedef struct fileInfo *fileP;

struct hashNode{
	char *word;
	int occurance;
	fileP files;
	struct hashNode *prevHash;
	struct hashNode *nextHash;
	struct hashNode *nextWord;
};
typedef struct hashNode *Node;

fileP newscantxt(char* tok, FILE* inFile);
Node searchFile(char* token, FILE *infile);
void NodeDestroy(Node nd);

#endif

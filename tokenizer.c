/*Lindsey Crocker and Advait Shukla
 * tokenizer.c
 */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

/* seps is a character array that holds the separator characters
 * stream is a character array that holds that string that needs to be split
 * segment is a character array that will hold a part of the string that is split
 * curr is the index where the program should start looking for delimeters.
 * delim is the index where the next delimeter is
 */
struct TokenizerT_ {
    char *seps;
    char *stream;
    char *segment;
    int curr;
    int delim;
};

typedef struct TokenizerT_ TokenizerT;


//this sends the correct character value
char asciiValue(char ch){
	if(ch=='n')
		return '\n';
	if(ch=='t')
		return '\t';
	if(ch=='v')
		return '\v';
	if(ch=='b')
		return '\b';
	if(ch=='r')
		return '\r';
	if(ch=='f')
		return '\f';
	if(ch=='a')
		return '\a';
	if(ch=='\\')
		return '\\';
	if(ch=='?')
		return '\?';
	if(ch==(char)39)
		return (char)39;
	if(ch=='"')
		return '\"';
	if(ch=='0')
		return '\000';
	return ch;
}

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
	//the character arrays are malloced
	TokenizerT *temp = (malloc(sizeof(struct TokenizerT_)));
    temp->seps = (char*)(malloc(sizeof(char)*(strlen(separators)+1)));
    temp->stream = (char*)(malloc(sizeof(char)*(strlen(ts)+1)));
    temp->segment = (char*)(malloc(sizeof(char)*(strlen(ts)+1))); 
    
    //the separator characters are copied over to the TokenizerT seps character array
    int i = 0;
    int p;
    int is = 0;
    char tempc;
    for(; separators[i] != '\0'; i++){
    	if(separators[i]=='\\'){
    		p = i+1;
    		tempc = asciiValue(separators[p]);
    		temp->seps[is]= tempc;
    		i=1+i;
    		is++;
    	}
    	else{
        	temp->seps[is] = separators[i];
        	is++;
        }
    }
    temp->seps[is] = '\0';
    
    
    i = 0;
    is = 0;
    p=0;
    //the string that needs to seperated is copied over to the character array stream
    for(; ts[i] != '\0'; i++){
        if(ts[i]=='\\'){
        	p = i+1;
        	tempc = asciiValue(ts[p]);
    		temp->stream[is]= tempc;
    		i++;
    		is++; 
    	}
    	else{
        	temp->stream[is] = ts[i];
        	is++;
        }
    }
    
    temp->stream[is] = '\0';
    
    temp->curr = -1;
    temp->delim = -1;
    
  return temp;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
    free(tk->seps);
    free(tk->stream);
    free(tk->segment);
    free(tk);
}

/*
 * Separate takes the TokenizerT and is able to find the next segment.
 * It does not separate the string, but changes the delim int to where the next 
 * delimeter is.
 * The method also sets the delim to -2 if there is no delim left.
 */
 
void Separate(TokenizerT *tk){
    int p1 = 0;
    int p2 = 0;
    int bpoint = 0;
    if(tk->curr != -1){
        p1 = tk->curr;
    }
    //This goes through each character in the string starting with curr and checks to see if it matches any of the characters in the seperator character array. If it does match, delim is the index where the match is.
    while(tk->stream[p1] != '\0'){
        while(tk->seps[p2] != '\0'){
            char c1 = tk->stream[p1];
            char c2 = tk->seps[p2];
            if(c1 == c2){
                //printf("%i/n",p1);
                tk->delim = p1;
                bpoint = 1;
                break;
            }
            else{
                p2++;
            }
        }
        if(bpoint == 1){
            break;
        }
        else{
            p1++;
            p2 = 0;
        }
    }
    if(bpoint == 0){
        tk->delim = strlen(tk->stream);
    }
    if(tk->curr==-1){
        tk->curr = 0;
    }
    if(tk->curr > strlen(tk->stream)){
        tk->delim = -2;
    }

}






/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
	//This makes sure there is anything to check in the string to split
    if(tk->delim == strlen(tk->stream)){
        return 0;
    }
    Separate(tk);
    //This checks for multiple delims in a row
    while(tk->curr == tk->delim){
        tk->curr = tk->delim +1;
        Separate(tk);

    }
    //This means there is no more delims left in string
    if(tk->delim == -2){
        return 0;
    }
    
    int start = tk->curr;
    int end = tk->delim;
    int i = 0;
    char token[(end - start) + 1];
    //This takes the segment found in from the separate method and copies only one segment to print.
    for(;start<end;start++){
        token[i] = tk->stream[start];
        i++;
    }
    token[i] = '\0';
    i = 0;
    while(i <=strlen(token)){
        tk->segment[i] = token[i];
        //printf("%c", tk->segment[i]);
        i++;
    }
    tk->curr = tk->delim + 1;
    //printf("%s\n", tk->segment);
    //printf("%s\n", token);
  return tk->segment;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */



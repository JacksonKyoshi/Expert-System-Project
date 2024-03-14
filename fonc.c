#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"


//first commit


Facts* initFacts() {
    Facts* lst = malloc(sizeof(Facts));
    lst->name =malloc(20*sizeof(char));
    lst ->next= NULL;
    return lst;
}

Rules* initRules() {
    Rules* lst=malloc(sizeof(Rules));
    lst->name=malloc(20*sizeof(char));
    lst -> next=NULL;
    return lst; 
}

char * readRulesFile(char * name){
    FILE * file = fopen(name,"r");
    char * result = malloc(sizeof(char)*1000);
    char character;
    while(character != -1){
        character = fgetc(file);
        if(strcmp(&character,"\n")!=32){
            //strncat(result,&character,1);
            sprintf(result + strlen(result), "%c", character);
        }
    }
    fclose(file);
    return result;
}

void saveRulesFile(char * name, char * data){
    FILE * file = fopen(name, "w");
    int cpt = 0;
    char character;
    char pointVirgule = ';';
    while(character!=EOF){
        character = data[cpt];
        if(character == pointVirgule){
            fputc(character,file);
            fputs("\n",file);
            cpt +=1;
        }
        else{
            fputc(character,file);
            cpt +=1;
        }
    }
}
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
    FILE * file = fopen(name, "r");
    char * result = malloc(sizeof(char)*100);
    char character;

    while(character != EOF){
        //printf("%s => %d \n",&character,strcmp(&character,"\n"));
        character = fgetc(file);
        if(strcmp(&character,"\n")!=32){
            strncat(result,&character,1);
        }
    }
    printf("le retour : %s",result);
    return result;
}

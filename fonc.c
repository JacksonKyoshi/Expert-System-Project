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
    lst->factList = initFacts();
    return lst; 
}

Rules * readInv(char * content) {
    Rules* Ruleliste =initRules();
    for(int i=strlen(content);i>=0;i--){
        printf("%c",content[i]);
    }
    return Ruleliste;
}

Facts * addFact(Facts* lst,Facts* elm) {
    Facts * copy = lst ;
    while(lst->next != NULL){
        lst=lst->next;
    }
    lst->next = elm;
    lst->next->next=NULL;
    return copy;
}

Rules * addRules(Rules* lst,Rules* elm) {
    Rules * copy = lst ;
    while(lst->next != NULL){
        lst=lst->next;
    }
    lst->next = elm;
    lst->next->next=NULL;
    return copy;
}

void showRules(Rules* lst) {
    while(lst != NULL) {
        printf("| %s | -->", lst->name);
        
        Facts* factPtr = lst->factList;
        while(factPtr != NULL) {
            printf("[%s]", factPtr->name);
            factPtr = factPtr->next;
        }
        
        lst = lst->next;
        printf("\n");
    }
}

Facts* createFact(char * name) {
    Facts* fact=initFacts();
    strcpy(fact->name,name);
    return fact;
}

Rules* createRule(Facts* facts,char* name) {
    Rules* rule=initRules();
    rule->factList=facts;
    strcpy(rule->name,name);
    return rule;
}


Facts* deleteFacts(Facts* lst) {
    Facts* copy = lst;
    while(copy != NULL) {
        printf("name : %s \n ", copy->name);
        Facts* nextFact = copy->next;
        free(copy);
        copy = nextFact;
    }
    return NULL; 
}




void writeRules(char* str) {
    int rule=0;
    Facts* lstFacts=initFacts();
    for(int i=0;i<strlen(str);i++){
        //point virgule
        if(str[i]==59){
            rule=0;
        }
        //reste
        if(str[i]!=45 && str[i]!=62 && rule==0){
            //on écris des faits
            if(str[i]!=32){ 
                lstFacts->name
            }
        }
    }
}
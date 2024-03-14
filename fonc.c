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
    while(lst != NULL){
        printf("| %s | -->",lst->name);
        while(lst->factList!= NULL) {
            printf("[%s]",lst->factList->name);
            lst->factList = lst->factList->next;
        }
        lst=lst->next;
        printf("\n");
    }
    return lst;
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


/*
Rules* writeRules(char* str) {
    

    return lst;
}*/
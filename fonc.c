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
        Facts* nextFact = copy->next;
        free(copy);
        copy = nextFact;
    }
    return NULL; 
}


void showFacts(Facts* factlist){
    while(factlist!=NULL){
        printf("| %s |",factlist->name);
        factlist=factlist->next;
    }
}


//str sera une seule ligne donc de la première lettre à un point virgule.
Facts* writeFacts(char* str) {

    char* name=malloc(20*sizeof(char));
    strcpy(name, "\0");
    Facts* factlist=initFacts();
    
    for(int i=0;i<strlen(str);i++){
        if(str[i]==59) {
            //showFacts(factlist);
            return factlist;
        }
        else{
            if(str[i] != 32) {
                name=strncat(name,&str[i],1);
            }
            else{
                if(strlen(factlist->name)==0){
                    strcpy(factlist->name,name);
                }
                else{


                   Facts* newFact= createFact(name);
                   factlist= addFact(factlist,newFact);
                }
                 strcpy(name,"");   
            }        
        }
    }
}

Rules* writeRules(char* content) {
    char* token=malloc(100*sizeof(char));
    char* factlist=malloc(100*sizeof(char));
    token = strtok(content, "->");
    if(token != NULL){
        //ici on va gérer les facts
        char* lst= malloc(sizeof(token)+2);
        strcpy(lst,token);
        strncat(lst,";",1);
        Facts* fact = writeFacts(lst);
        token = strtok(NULL, "->");
        if(token != NULL) {
            Rules* rule= malloc(sizeof(Rules));
            rule=createRule(fact,token);
           return rule;
        }
    }
    return NULL;
}
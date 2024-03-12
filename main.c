#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char ** argv) {
    Facts* lstF = malloc(sizeof(Facts*));
    lstF->name=malloc(20*sizeof(char));
    strcpy(lstF->name,"miam");

    Rules* lstR = initRules();
    Rules* elm=malloc(sizeof(Rules));
    elm->name=malloc(20*sizeof(char));
    elm->factList=malloc(sizeof(Facts*));
    strcpy(elm->name,"bite");


   char * testLecture= malloc(400*sizeof(char));
    strcpy(testLecture,"a b -> c;b c -> d;a d -> n;n e g ->a; c -> n;");
   /* printf("%s",testLecture);
    printf("\n");
    readInv(testLecture);*/
    elm->factList= addFact(elm->factList,lstF);
    lstR= addRules(lstR,elm);
    showRules(lstR);

    return 0;
}   

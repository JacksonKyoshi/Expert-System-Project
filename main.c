#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char ** argv) {

Facts* lstF=createFact("miam");
Facts* lstF2=createFact("leramadan");
lstF=addFact(lstF,lstF2);
Rules* lstR=createRule(lstF,"bite");


Facts* lstFV2=createFact("Cricri");
Facts* lstF2V2=createFact("lepaul");
lstFV2=addFact(lstFV2,lstF2V2);
Rules* lstRV2=createRule(lstFV2,"djafar");

Rules* lstRV3=createRule(NULL,"bazooka");

   char * testLecture= malloc(400*sizeof(char));
    strcpy(testLecture,"a b -> c;b c -> d;a d -> n;n e g ->a; c -> n;");
   /* printf("%s",testLecture);
    printf("\n");
    readInv(testLecture);*/
    lstR=addRules(lstR,lstRV2);
    lstR=addRules(lstR,lstRV3);
    showRules(lstR);
    return 0;
}   

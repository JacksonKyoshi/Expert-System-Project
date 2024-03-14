#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char ** argv) {

    Facts* lstF = initFacts();
    Rules* lstR = initRules();
    
    /*test max
    
    char * test = readRulesFile("rules.kbs");
    saveRulesFile("test.kbs",test);
    */

   char * test = readRulesFile("rules.kbs");
   Rules * list = charToRules(test);
   
   showRules(list);

    return 0;

}   

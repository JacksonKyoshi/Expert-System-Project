#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char ** argv) {
    Facts* lstF = initFacts();
    Rules* lstR = initRules();
    

    char * test = readRulesFile("rules.kbs");
    printf("%s",test);
    saveRulesFile("test.kbs",test);
    return 0;
}   

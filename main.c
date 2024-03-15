#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char ** argv) {

   char * test = readRulesFile("test.kbs");
   //printf("test : %s\n","disparition");
   Rules * list = charToRules(test);

 //  Rules* list=writeRules("a b c ->d");
   showRules(list);
    return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char ** argv) {
        char content[]= "a b c -> cul";
        Rules* rule  = writeRules(content);
        showRules(rule);
        return 0;
}   

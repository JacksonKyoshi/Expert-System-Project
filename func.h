#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Facts{
    char * name;
    struct Facts * next;
}Facts;

typedef struct Rules{
    char * name;
    struct Rules * next;
    struct Facts * factList;
}Rules;


Facts* initFacts();
Rules* initRules() ;
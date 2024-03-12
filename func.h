#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Facts{
    char * name;
    Facts * next;
}Facts;

typedef struct Rules{
    char * name;
    Rules * next;
    struct Facts * factList;
}Rules;
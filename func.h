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
Rules * readInv(char * content);
Rules * addRules(Rules* lst,Rules* elm);
Facts * addFact(Facts* lst,Facts* elm);
void showRules(Rules* lst);
Rules* createRule(Facts* facts,char* name);
Facts* createFact(char * name);
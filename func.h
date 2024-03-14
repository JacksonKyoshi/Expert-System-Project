#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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
char * readRulesFile(char *);
void saveRulesFile(char * name, char * data);
int backwardChain(char *but, Rules *baseRules, Facts *baseFacts);
Rules* forwardChain(Facts* factBase, Rules* ruleBase);
bool isInFactBase(Facts* factBase, Facts* fact);
Facts *findFact(Facts *base, char *name);
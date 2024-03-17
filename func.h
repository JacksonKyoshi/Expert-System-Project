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
//Rules* forwardChain(Facts* factBase, Rules* ruleBase);
bool isInFactBase(Facts* factBase, Facts* fact);
Facts *findFact(Facts *base, char *name);

Rules * addRules(Rules* lst,Rules* elm);
Facts * addFact(Facts* lst,Facts* elm);
void showRules(Rules* lst);
Rules* createRule(Facts* facts,char* name);
Facts* createFact(char * name);
Facts* deleteFacts(Facts* lst);
Facts* writeFacts(char* str);
void showFacts(Facts* factlist);
Rules* writeRules(char* data);

Rules * charToRules(char * data);
int verifFait(Facts* factBase, Facts* fact);
int verifRegles(Facts* factList, Rules* regle);
Rules* forwardChain(Rules* base_de_regles,Facts * base_de_faits);    

void tests();

Facts* createFactlist();
void menu();
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#include <stdbool.h>

//first commit


Facts* initFacts() {
    Facts* lst = malloc(sizeof(Facts));
    lst->name =malloc(20*sizeof(char));
    lst ->next= NULL;
    return lst;
}

Rules* initRules() {
    Rules* lst=malloc(sizeof(Rules));
    lst->name=malloc(20*sizeof(char));
    lst -> next=NULL;
    return lst; 
}

char * readRulesFile(char * name){
    FILE * file = fopen(name,"r");
    char * result = malloc(sizeof(char)*1000);
    char character;
    while(character != -1){
        character = fgetc(file);
        if(strcmp(&character,"\n")!=32){
            //strncat(result,&character,1);
            sprintf(result + strlen(result), "%c", character);
        }
    }
    fclose(file);
    return result;
}

void saveRulesFile(char * name, char * data){
    FILE * file = fopen(name, "w");
    int cpt = 0;
    char character;
    char pointVirgule = ';';
    while(character!=EOF){
        character = data[cpt];
        if(character == pointVirgule){
            fputc(character,file);
            fputs("\n",file);
            cpt +=1;
        }
        else{
            fputc(character,file);
            cpt +=1;
        }
    }
}

// Fonction pour chaîner en arrière
int backwardChain(char *but, Rules *baseRules, Facts *baseFacts) {
    int result = 0;

    // Si le but n'est pas dans la base de faits
    if (!findFact(baseFacts, but)) {
        Rules *rule = baseRules;

        // Tant qu'il y a des règles et que le résultat n'est pas trouvé
        while (rule != NULL && !result) {
            // Si la conclusion de la règle est le but
            if (strcmp(rule->name, but) == 0) {
                Facts *hypothesis = rule->factList;
                int continueFlag = 1;

                // Tant qu'il y a des hypothèses et que la boucle continue
                while (hypothesis != NULL && continueFlag) {
                    // On vérifie chaque hypothèse par chaînage arrière
                    continueFlag = backwardChain(hypothesis->name, baseRules, baseFacts);
                    hypothesis = hypothesis->next;
                }

                // Si toutes les hypothèses sont vraies, la conclusion est vraie
                result = continueFlag;
            }

            rule = rule->next;
        }
    } else {
        // Le but est dans la base de faits, donc la conclusion est vraie
        result = 1;
    }

    return result;
}

Rules* forwardChain(Facts* factBase, Rules* ruleBase) {
  Rules* applicableRules = NULL;
  Rules* tmpRule = ruleBase;

  while (tmpRule != NULL) {
    bool isApplicable = true;
    Facts* tmpFact = tmpRule->factList;

    while (tmpFact != NULL) {
      if (!isInFactBase(factBase, tmpFact)) {
        isApplicable = false;
        break;
      }
      tmpFact = tmpFact->next;
    }

    if (isApplicable) {
      // Ajout de la règle applicable à la liste
      Rules* newRule = (Rules*)malloc(sizeof(Rules));
      newRule->name = tmpRule->name;
      newRule->next = NULL;

      if (applicableRules == NULL) {
        applicableRules = newRule;
      } else {
        Rules* tmpApplicableRule = applicableRules;
        while (tmpApplicableRule->next != NULL) {
          tmpApplicableRule = tmpApplicableRule->next;
        }
        tmpApplicableRule->next = newRule;
      }
    } else {
      // **Suppression de la règle non applicable**
      Rules* prevRule = NULL;
      Rules* tmpDeleteRule = ruleBase;

      while (tmpDeleteRule != tmpRule) {
        prevRule = tmpDeleteRule;
        tmpDeleteRule = tmpDeleteRule->next;
      }

      if (prevRule == NULL) {
        ruleBase = ruleBase->next;  // rule is the head
      } else {
        prevRule->next = tmpRule->next;  // Remove the rule from the linked list
      }
      free(tmpRule);  // Free the memory allocated for the rule
    }

    tmpRule = tmpRule->next;
  }

  return applicableRules;
}

bool isInFactBase(Facts* factBase, Facts* fact) {
  while (factBase != NULL) {
    if (factBase == fact) {
      return true;
    }
    factBase = factBase->next;
  }
  return false;
}

Facts *findFact(Facts *base, char *name) {
    while (base != NULL) {
        if (strcmp(base->name, name) == 0) {
            return base;
        }
        base = base->next;
    }
    return NULL;
}
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

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    do{
         if(character != '\n'){
            //strncat(result ,&character,1);
            sprintf(result + strlen(result), "%c", character);
        }
        character = fgetc(file);
    }while(character != EOF);

    printf("%s\n",result);
    fclose(file);
    return result;
}

void saveRulesFile(char * name, char * data){
    FILE * file = fopen(name, "w");
    int cpt = 0;
    char character;
    char pointVirgule = ';';
    character = data[cpt];
    do{
        if(character == pointVirgule){
            fputc(character,file);
            fputs("\n",file);
            cpt +=1;
        }
        else{
            fputc(character,file);
            cpt +=1;
        }
        if(data[cpt]){
            character = data[cpt];
        }
        else{
            character = '?';
        }
    }while(character != '?');
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
    }

    // Avancer dans la liste des règles même si la règle n'est pas applicable
    Rules* prevRule = NULL;
    Rules* tmpDeleteRule = ruleBase;

    while (tmpDeleteRule != tmpRule) {
      prevRule = tmpDeleteRule;
      tmpDeleteRule = tmpDeleteRule->next;
    }

    if (isApplicable) {
      tmpRule = tmpRule->next;
    } else {
      if (prevRule == NULL) {
        ruleBase = ruleBase->next;  // rule is the head
      } else {
        prevRule->next = tmpRule->next;  // Remove the rule from the linked list
      }
      free(tmpRule);  // Free the memory allocated for the rule
      tmpRule = ruleBase; // Move to the next rule after deletion
    }
  }

  return applicableRules;
}

bool isInFactBase(Facts* factBase, Facts* fact) {
    if (factBase == NULL || fact == NULL) {
        return false;
    }

    while (factBase != NULL) {
        if (strcmp(factBase->name, fact->name) == 0) {
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
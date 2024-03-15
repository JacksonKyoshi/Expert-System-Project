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
    strcpy(lst->name,"temp");
    lst -> next=NULL;
    lst->factList = initFacts();
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
            sprintf(result + strlen(result), "%c", character);
        }
        character = fgetc(file);
    }while(character != EOF);
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

/*
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
*/

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

Facts * addFact(Facts* lst,Facts* elm) {
    Facts * copy = lst ;
    while(copy->next != NULL){
        copy=copy->next;
    }
    copy->next = elm;
    elm->next=NULL;
    return lst;
}

Rules * addRules(Rules* lst,Rules* elm) {
    Rules * copy = lst ;
     while(copy->next != NULL){
         copy=copy->next;
     }
     copy->next = elm;
     elm->next=NULL;
     return lst;
}

void showRules(Rules* lst) {
    Rules * copy = lst;
    while(copy != NULL) {
        printf("| %s | -->", copy->name);
        Facts* factPtr = copy->factList;
        while(factPtr != NULL) {
            printf("[%s]", factPtr->name);
            factPtr = factPtr->next;
        }
        copy = copy->next;
        printf("\n");
    }
}

Facts* createFact(char * name) {
    Facts* fact=initFacts();
    strcpy(fact->name,name);
    return fact;
}

Rules* createRule(Facts* facts,char* name) {
    Rules* rule=initRules();
    rule->factList=facts;
    strcpy(rule->name,name);
    return rule;
}

Facts* deleteFacts(Facts* lst) {
    Facts* copy = lst;
    while(copy != NULL) {
        Facts* nextFact = copy->next;
        free(copy);
        copy = nextFact;
    }
    return NULL; 
}

void showFacts(Facts* factlist){
    while(factlist!=NULL){
        printf("| %s |",factlist->name);
        factlist=factlist->next;
    }
}

//str sera une seule ligne donc de la première lettre à un point virgule.
Facts* writeFacts(char* str) {
    char* name=malloc(20*sizeof(char));
    strcpy(name, "\0");
    Facts* factlist=initFacts();
    for(int i=0;i<strlen(str);i++){
        if(str[i]==59) {
            //showFacts(factlist);
            return factlist;
        }
        else{
            if(str[i] != 32) {
                name=strncat(name,&str[i],1);
            }
            else{
                if(strlen(factlist->name)==0){
                    strcpy(factlist->name,name);
                }
                else{
                   Facts* newFact= createFact(name);
                   factlist= addFact(factlist,newFact);
                }
                 strcpy(name,"");   
            }        
        }
    }
    return NULL;
}

Rules* writeRules(char* data) {
    char* token=malloc(100*sizeof(char));
    char* content = malloc(100*sizeof(char));
    strcpy(content,data);
    token = strtok(content, "->");
    if(token != NULL){
        //printf("token : %s\n",token);
        //ici on va gérer les facts
        char* lst= malloc(sizeof(token)+2);
        strcpy(lst,token);
        strncat(lst,";",1);
        Facts* fact = writeFacts(lst);
        token = strtok(NULL, "->");
        if(token != NULL) {
            Rules* rule= malloc(sizeof(Rules));
            rule=createRule(fact,token);
           return rule;
        }
    }
    return NULL;
}

Rules * charToRules(char * data){
    Rules* lst=initRules();
    char* name=malloc(20*sizeof(char));
    strcpy(name, "\0");
    for(int i=0;i<=strlen(data);i++){
        if(strcmp(lst->name,"temp")==0 && data[i]==59){
            lst = writeRules(name);
            strcpy(name,"\0");  
        }
        else if(data[i]==59){
           lst=addRules(lst,writeRules(name));
           strcpy(name,"\0");  
        }
        else{
            strncat(name,&data[i],1);
        }
    }
    return lst;
}

/*
Rules * forwardChain(Rules* ruleBase, Facts* factBase){
	Rules* tmp = malloc(sizeof(Rules*)) ;
	Rules* trueList = malloc(sizeof(Rules*)) ;
	tmp = ruleBase ;
	while(tmp != NULL)
	{
        if(verifRegles(tmp->factList, factBase) == 1){
                ajouteRegle(trueList, tmp); //on ajoute la règle a la liste de règles qui sont vraies
            }
        else{
                tmp->next;
            }
    }
	return trueList;
}

int verifFait(Facts* factBase, Facts* fact){
    fact tmp = malloc(sizeof(fact)) ;
    tmp = factList ;
    int answer = 0 ;
    while(tmp != NULL){
	    if(strcmp(tmp->name,fact->name) == 0){
            result == 1
            tmp = tmp->next ;
        }
	    else{
            tmp= tmp->next ;
	    }
	}
return answer;
}


int verifRegles(Facts* factList, Rules* regle){
    int resultat;
    regle *tmp = regle ;
    fact *tmp2 = regle->factList
    while(tmp != NULL){
        while(tmp2 != NULL)
	    {
		if(verifFait(factList, tmp2) == 0)
		{
			resultat = 0 ;
			Return resultat ;
		}
		else{
			tmp2 = tmp2->next ;
		}
    }
    resultat = 1 ;
    tmp = tmp->next ;
}
return resultat;
}

*/
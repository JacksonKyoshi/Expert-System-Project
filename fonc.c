#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#include <stdbool.h>

//intialise a fact
Facts* initFacts() {
    Facts* lst = malloc(sizeof(Facts));
    lst->name =malloc(50*sizeof(char));
    lst ->next= NULL;
    return lst;
}
//initialise a rule
Rules* initRules() {
    Rules* lst=malloc(sizeof(Rules));
    lst->name=malloc(50*sizeof(char));
    lst -> next=NULL;
   lst->factList = initFacts();
    return lst; 
}

//read the rule file to return a char *
char * readRulesFile(char * name){
    FILE * file = fopen(name,"r");
    char * result = malloc(sizeof(char)*10000);
    char character;

    if (file == NULL) {//condition to manage errors when opening the file rule
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    do{//loop on each character to save the into the char * result
         if(character != '\n'){
            sprintf(result + strlen(result), "%c", character);
        }
        character = fgetc(file);
    }while(character != EOF);
    fclose(file);
    return result;
}

//function to save a rule file from char *
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
    if (!findFact(baseFacts, but)) {
        Rules *rule = baseRules;
        while (rule != NULL && !result) {
            if (strcmp(rule->name, but) == 0) {
                Facts *hypothesis = rule->factList;
                int continueFlag = 1;
                while (hypothesis != NULL && continueFlag) {
                    continueFlag = backwardChain(hypothesis->name, baseRules, baseFacts);
                    hypothesis = hypothesis->next;
                }
                result = continueFlag;
            }
            rule = rule->next;
        }
    } else {
        result = 1;
    }
    return result;
}

Rules* forwardChain(Rules* base_de_regles, Facts* base_de_faits) {
  Rules* tmp = base_de_regles;
  Rules* trueList = NULL;
  while (tmp != NULL) {
    if (verifRegles(base_de_faits, tmp) == 1) {
      // On appelle la fonction `ajouteRegle` pour ajouter la règle à la liste `trueList`
      //ajouteRegle(trueList, tmp);
      Rules* copy = initRules();
      strcpy(copy->name,tmp->name);
      copy->factList=tmp->factList;
      copy->next=NULL;
      trueList=addRules(trueList,copy);
      }

    tmp = tmp->next;
  }
  return trueList;
}



int verifFait(Facts* factList, Facts* fait) {
  Facts* tmp = factList;
  int answer = 0;

  while (tmp != NULL) {
    if (strcmp(tmp->name, fait->name) == 0) {
      answer = 1;
      break;
    }
    tmp = tmp->next;
  }
  return answer;
}
	
int verifRegles(Facts* factList, Rules* regle) {
  int resultat = 1;
  Rules* tmp = regle;
  Facts* tmp2 = regle->factList;

  while (tmp != NULL) {
    while (tmp2 != NULL) {
      if (verifFait(factList, tmp2) == 0) {
        resultat = 0;
        break;
      }
      tmp2 = tmp2->next;
    }

    if (resultat == 0) {
      break;
    }

    tmp2 = regle->factList;
    tmp = tmp->next;
  }

  return resultat;
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
    if(lst!=NULL){
    Rules * copy = lst ;
     while(copy->next != NULL){
         copy=copy->next;
     }
     copy->next = elm;
     elm->next=NULL;
    }else{
        lst=elm;
        lst->next=NULL;
    }
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


Facts* writeFacts(char* str) {
    char name[20]; 
    Facts* factlist = initFacts();
    int nameIndex = 0; 

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ';') {
            if (nameIndex > 0) {
                name[nameIndex] = '\0'; 
                Facts* newFact = createFact(name);
                factlist = addFact(factlist, newFact);
                nameIndex = 0;
            }
            return factlist;
        } else if (str[i] != ' ') {
            name[nameIndex++] = str[i];
        } else {
            if (nameIndex > 0) {
                name[nameIndex] = '\0'; 
                Facts* newFact = createFact(name);
                factlist = addFact(factlist, newFact);
                nameIndex = 0;
            }
        }
    }
    return factlist;
}

Rules* writeRules(char* data) {
    char token[50];
    char content[50];
    strcpy(content, data);
    strcpy(token, strtok(content, "->"));
    if (token != NULL) {
        char* lst = malloc(strlen(token) + 2);
        if (lst == NULL) {
            perror("Allocation error");
            exit(EXIT_FAILURE);
        }
        strcpy(lst, token);
        strncat(lst, ";", 1);
        Facts* fact = writeFacts(lst);
        free(lst); 
        strcpy(token, strtok(NULL, "->"));
        if (token != NULL) {
            Rules* rule = malloc(sizeof(Rules)); 
            if (rule == NULL) {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
            rule = createRule(fact, token);
            return rule;
        }
    }
    return NULL;
}

Rules * charToRules(char * data){
    Rules* lst = NULL;
    char* name = malloc(strlen(data) + 1); 
    if (name == NULL) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }
    strcpy(name, "");
    int cpt = 0;
    for(long i = 0; i <= strlen(data); i++){
        if(data[i] == 59){
            printf("%d\n", cpt);
            lst = addRules(lst, writeRules(name));
            strcpy(name, "");  
            cpt += 1;
        }
        else{
            strncat(name, &data[i], 1);
        }
    }
    free(name);
    return lst;
}

void tests(){
    //Test1
    char* data = readRulesFile("rules.kbs");
    if (data != NULL) {
        printf("Test readRulesFile: Passed\n");
        printf("Data read from file: %s\n", data);
    } else {
        printf("Test readRulesFile: Failed\n");
    }


    //TestForward
     // Création de quelques faits factices
    Facts* base_de_faits = initFacts();
    Facts* fact1 = createFact("Fact1");
    Facts* fact2 = createFact("Fact2");
    Facts* fact3 = createFact("Fact3");
    Facts* fact4 = createFact("Fact4");
    // Ajout des faits à la base de faits
    base_de_faits = addFact(base_de_faits, fact1);
    Rules* base_de_regles = NULL;
    Facts* rule1_facts = initFacts();
    Facts* rule2_facts = initFacts();

    Facts* rule1_fact1 = createFact("Fact1");
    Facts* rule1_fact2 = createFact("Fact2");
    Facts* rule2_fact3 = createFact("Fact3");
    Facts* rule2_fact4 = createFact("Fact4");

    rule1_facts = addFact(rule1_facts, rule1_fact1);
    rule1_facts = addFact(rule1_facts, rule1_fact2);
    rule2_facts = addFact(rule2_facts, rule2_fact3);
    rule2_facts = addFact(rule2_facts, rule2_fact4);
 
    Rules* rule1 = createRule(rule1_facts, "Rule1");
    Rules* rule2 = createRule(rule2_facts, "Rule2");

    base_de_regles = addRules(base_de_regles, rule1);
    base_de_regles = addRules(base_de_regles, rule2);
    printf("Forward chaining result:\n");
    Rules* trueList = forwardChain(base_de_regles, base_de_faits);
    showRules(trueList);


     base_de_faits = addFact(base_de_faits, fact2);
     trueList = forwardChain(base_de_regles, base_de_faits);
     showRules(trueList);

      base_de_faits = addFact(base_de_faits, fact3);
      trueList = forwardChain(base_de_regles, base_de_faits);
      showRules(trueList);

    printf("Test forwardChain: Passed\n");


    printf("backward test :\n");
    if(backwardChain("Fact3",base_de_regles,base_de_faits)==1) {
        printf("backward test 1 passed\n");
    }
     if(backwardChain("Cr",base_de_regles,base_de_faits)==0) {
        printf("backward test 2 passed\n");
    }


    free(base_de_faits);
    free(trueList);
    free(base_de_regles);
    free(fact1);
    free(fact2);
    free(fact3);
    free(fact4);

}


void menu() {
    int choix;
    bool quitter = false;
    char* Fact= malloc(200*sizeof(char));
    char * test = readRulesFile("test2.kbs");
    Rules * list = charToRules(test);
    free(test);
    printf("%s,\n",test);

    do {
        printf("\n------ Menu ------\n");
        printf("1. Tests\n");
        printf("2. Afficher les règles du fichier\n");
        printf("3. ForwardChain\n");
        printf("4. BackwardChain\n");
        printf("5. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                tests();
                break;
            case 2:
            showRules(list);
                break;
            case 3:
                printf("\nForward Chain \n");
                break;
            case 4 :
                printf("\nBackward Chain \n");
                break;
            case 5:
                quitter = true;
                break;
            default:
                printf("Choix invalide. Veuillez choisir une option valide.\n");
                break;
        }
    } while (!quitter);
}
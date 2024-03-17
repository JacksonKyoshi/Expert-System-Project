#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#include <stdbool.h>

/// @brief initialize a fact
/// @return list of facts (empty)
Facts* initFacts() {
    Facts* lst = malloc(sizeof(Facts));
    lst->name = malloc(50*sizeof(char));
    strcpy(lst->name,"?");
    lst->next = NULL;
    return lst;
}

/// @brief initialize a rule
/// @return list of rules (empty)
Rules* initRules() {
    Rules* lst = malloc(sizeof(Rules));
    lst->name = malloc(50*sizeof(char));
    lst->next = NULL;
    lst->factList = initFacts();
    return lst; 
}

/// @brief read the rule file 
/// @param name of the file
/// @return char * containing all rules
char * readRulesFile(char * name){
    FILE * file = fopen(name,"r");
    char * result = malloc(sizeof(char)*10000);
    char character;

    //condition to manage errors when opening the file rule
    if (file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    //loop on each character to save it into the char * result
    do{
         if(character != '\n'){
            sprintf(result + strlen(result), "%c", character);
        }
        character = fgetc(file);
    }while(character != EOF);
    fclose(file);
    return result;
}

/// @brief save a rule file from a char * with the rule base format
/// @param name of the file
/// @param data char * containing all rules 
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

/// @brief remove all the Spaces of a char list (char*)
/// @param str the char list
void removeSpaces(char *str) {
    char *dest = str; 
    while (*str) {
        if (*str != ' ') {
            *dest++ = *str;
        }
        str++; 
    }
    *dest = '\0';
}


/// @brief backward chaining function
/// @param but char * of the rule that must be tested
/// @param baseRules Rules * containing all rules
/// @param baseFacts Facts * containing all facts that are true (choosed by user)
/// @return result int 1 if true, 0 if false

int backwardChain(char *but, Rules *baseRules, Facts *baseFacts) {
    removeSpaces(but);
    if (findFact(baseFacts, but)) {
        return 1;
    }
    //
    Rules *rule = baseRules;
    while (rule != NULL) {
        removeSpaces(rule->name);
        if (strcmp(rule->name, but) == 0) {
            Facts *hypothesis = rule->factList;
            int continueFlag = 1;
            while (hypothesis != NULL && continueFlag) {
                if (continueFlag) {
                return 1;
                }
                hypothesis = hypothesis->next;
            }
            
        }
        rule = rule->next;
    }
    // Aucune règle trouvée pour prouver le but
    return 0;
}

/// @brief forward chaining function
/// @param base_de_regles char * containing all rules
/// @param base_de_faits char * containing all facts that are true (choosed by user)
/// @return trueList Rules * containing the correct rule 
/*
Rules* forwardChain(Rules* base_de_regles, Facts* base_de_faits) {
  Rules* tmp = base_de_regles;
  Rules* trueList = malloc(sizeof(Rules));
  while (tmp != NULL) {
    if (verifRegles(base_de_faits, tmp) == 1) {
      Rules* copy = initRules();
      strcpy(copy->name,tmp->name);
      copy->factList=tmp->factList;
      copy->next=NULL;
      trueList=addRules(trueList,copy);
      printf("%s\n",trueList->name);
      }

    tmp = tmp->next;
  }
  return trueList;
}
*/
Rules* forwardChain(Rules* base_de_regles, Facts* base_de_faits) {
  Rules* tmp = base_de_regles;
  Rules* trueList = NULL;
  while (tmp != NULL) {
    if (verifRegles(base_de_faits, tmp) == 1) {
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

/// @brief check if a fact is correct
/// @param factList Facts * containing all the facts 
/// @param fait Facts * containing the fact that must be tested 
/// @return answer int 1 if true, 0 if false
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
	
/// @brief check if a rule is correct
/// @param factList Facts * containing all the facts
/// @param regle Rules * containing the rule that must be tested
/// @return resultat int 1 if true, 0 if false
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

/// @brief test if a fact is in a fact list
/// @param list the factlist
/// @param name the name of the fact that must be tested
/// @return null or the factlist if it's true
int findFact(Facts *list, char *name) {
    while (list != NULL) {
        if (strcmp(list->name, name) == 0) {
            return 1; 
        }
        list = list->next;
    }
    return 0;
}

/// @brief add a fact in a fact list
/// @param lst the factlist
/// @param elm the new fact that we want to add
/// @return lst Facts * containing all the facts
Facts * addFact(Facts* lst,Facts* elm) {
    Facts * copy = lst ;
    if(strcmp(lst->name,"?")==0){
        lst = elm;
        return lst;
    }
    while(copy->next != NULL){
        copy=copy->next;
    }
    copy->next = elm;
    elm->next=NULL;
    return lst;
}


/// @brief add a new rule in the rule list
/// @param rule list
/// @param new rule
/// @return rule list
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

/// @brief display function to show the Rule list in terminal
/// @param rule list
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

/// @brief create a fact
/// @param name of the fact
/// @return the fact
Facts *createFact(char *name) {
    Facts *newFact = (Facts *)malloc(sizeof(Facts));
    if (newFact == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newFact->name = strdup(name);
    newFact->next = NULL;
    return newFact;
}

/// @brief create a rule
/// @param facts of the rule
/// @param name of the rule
/// @return the rule
Rules* createRule(Facts* facts,char* name) {
    Rules* rule=initRules();
    rule->factList=facts;
    strcpy(rule->name,name);
    return rule;
}

/// @brief delete fact
/// @param fact 
/// @return Null
Facts* deleteFacts(Facts* lst) {
    Facts* copy = lst;
    while(copy != NULL) {
        Facts* nextFact = copy->next;
        free(copy);
        copy = nextFact;
    }
    return NULL; 
}

/// @brief display function to see the factList
/// @param factlist 
/// @return void
void showFacts(Facts* factlist){
    while(factlist!=NULL){
        printf("| %s |",factlist->name);
        factlist=factlist->next;
    }
}

/// @brief write a fact from a char *
/// @param str 
/// @return factlist
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

/// @brief write rule from the char *
/// @param data
/// @return rule or Null
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

/// @brief transform the char * with all rules in a rules list
/// @param data 
/// @return rules list
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

/// @brief just a test function
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
    Facts* base_de_faits = initFacts();
    Facts* fact1 = createFact("Fact1");
    Facts* fact2 = createFact("Fact2");
    Facts* fact3 = createFact("Fact3");
    Facts* fact4 = createFact("Fact4");
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
}

/// @brief create a fact list
/// @return fact list
Facts* createFactlist() {
    bool quitter=false;
    Facts* factlist=initFacts();
    char* name=malloc(20*sizeof(char));
    do{
        printf("\nentrez le nom du fait (q pour quitter) :");
        scanf("%s",name);
        if(strcmp(name,"q")==0){
            quitter=true;
        }
        factlist=addFact(factlist,createFact(name));
    }while(!quitter);
    return factlist;
}


/// @brief menu in terminal
void menu() {
    system("clear");
    int choix;
    bool quitter = false;
    char* Fact= malloc(200*sizeof(char));
    char * test = readRulesFile("test2.kbs");
    Rules * list = charToRules(test);
    char * backward=malloc(20*sizeof(char));
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
            case 3 :
                printf("\nForward Chain \n");
                Facts * factlistForward  = createFactlist();
                Rules * gift = forwardChain(list,factlistForward);
                if(gift != NULL) {
                   printf("%s\n",gift->name);
                }
                else{
                    printf("Aucun résultat\n");
                }
                break;
            case 4 :
                printf("\nBackward Chain \n");
                Facts * factlistBack  = createFactlist();
                printf("\nentrez le name : ");
                scanf("%s",backward);
                if(backwardChain(backward,list,factlistBack)==1 ){
                    printf("\nBACKWARD : TRUE");
                    break;
                }
                else{
                    printf("\nBACKWARD : FALSE");
                }
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
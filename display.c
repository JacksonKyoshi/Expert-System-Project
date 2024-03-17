#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "func.h" 

// Function to initialize SDL
int initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Create window
    *window = SDL_CreateWindow("System KDO expert",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                1400, // Initial window width
                                600, // Initial window height
                                SDL_WINDOW_SHOWN);

    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

// Function to load font
TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* font = TTF_OpenFont(path, size);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    return font;
}

// Function to render text
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    return texture;
}

// Function to draw text on a rectangle
void drawTextOnRectangle(SDL_Renderer* renderer, const char* text, int x, int y, TTF_Font* font, SDL_Color color) {
    // Render text to texture
    SDL_Texture* textTexture = renderText(renderer, text, font, color);
    if (textTexture == NULL) {
        return;
    }

    // Get the width and height of the rendered text
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Render the rectangle
    SDL_Rect rect = {x, y, textWidth + 20, textHeight + 20};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Calculate position to render text in the center of the rectangle
    int textX = x + 10;
    int textY = y + 10;

    // Render text
    SDL_Rect textRect = {textX, textY, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Clean up
    SDL_DestroyTexture(textTexture);
}
void showRulesSDL(SDL_Renderer* renderer,Rules* lst, TTF_Font* font, SDL_Color color) {
    int x=80;
    int base=80;
    int cpt=0;
    int y=40;
    Rules * copy = lst;
    char * temp = malloc(sizeof(char)*100);
    strcpy(temp,"");
    while(copy != NULL) {
    strcat(temp, "|");
    strcat(temp, copy->name);
    strcat(temp, "| -->");
        drawTextOnRectangle(renderer, temp, x, y, font, color);
        //printf("| %s | -->", copy->name);
        Facts* factPtr = copy->factList;
        x+=100; 
        strcpy(temp,"");
        while(factPtr != NULL) {
            //strcat(temp, "[");
            strcat(temp, factPtr->name);
            //strcat(temp, "]");
            //printf("[%s]", factPtr->name);
            drawTextOnRectangle(renderer, temp, x, y, font, color);
            factPtr = factPtr->next;
            x+=40;
            strcpy(temp,"");
        }
        cpt++;
        x=base;
        if(cpt==10){
        cpt=0;
        base+=400;}
        y+=40;
        copy = copy->next;
    }
}
// Function to close SDL
void closeSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
SDL_Color testColor(int *cpt, int test, SDL_Color non, SDL_Color oui) {
    if (*cpt == test) {
        (*cpt)++;
        return oui;
    } else {
        (*cpt)++;
        return non;
    }
}

void menu2(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, int newWidth, int newHeight, int hobby, int age, int relation, int budget, int idee, int scroll){
		int c=1;
		int *cpt= &c;
            SDL_Color color2 = {0, 255, 0, 255};
            drawTextOnRectangle(renderer, "Hobbies :", newWidth/15, newHeight/10, font, textColor);
                        drawTextOnRectangle(renderer, "Lecture", newWidth/15*2.7, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Cinema", newWidth/15*4, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Plein air", newWidth/15*5.5, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Technologie", newWidth/15*7, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Cuisine", newWidth/15*9, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Musique", newWidth/15*10.5, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Voyage", newWidth/15*12, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Art", newWidth/15*13.4, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Vin", newWidth/15*14.1, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                       
            (*cpt)=1;            
            drawTextOnRectangle(renderer, "Age :", newWidth/15, newHeight/10*2.5, font, textColor);
            		drawTextOnRectangle(renderer, "-18 ans", newWidth/4, newHeight/10*2.5, font, testColor(cpt, age, textColor, color2));
                        drawTextOnRectangle(renderer, "adulte", newWidth/4*2, newHeight/10*2.5, font, testColor(cpt, age, textColor, color2));
                        drawTextOnRectangle(renderer, "senior", newWidth/4*3, newHeight/10*2.5, font, testColor(cpt, age, textColor, color2));
            	
            (*cpt)=1; 
            drawTextOnRectangle(renderer, "Relation :", newWidth/15, newHeight/10*4, font, textColor);
            		drawTextOnRectangle(renderer, "enfant", newWidth/4, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
                        drawTextOnRectangle(renderer, "famille", newWidth/4*2, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
                        drawTextOnRectangle(renderer, "couple", newWidth/4*3, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
                        drawTextOnRectangle(renderer, "ami", newWidth/4*3.5, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
            	
            (*cpt)=1; 
            drawTextOnRectangle(renderer, "Budget", newWidth/15, newHeight/10*5.5, font, textColor);
            		drawTextOnRectangle(renderer, "<20", newWidth/4, newHeight/10*5.5, font, testColor(cpt, budget, textColor, color2));
                        drawTextOnRectangle(renderer, "[20;10]", newWidth/4*2, newHeight/10*5.5, font, testColor(cpt, budget, textColor, color2));
                        drawTextOnRectangle(renderer, ">100", newWidth/4*3, newHeight/10*5.5, font, testColor(cpt, budget, textColor, color2));
            	 
            drawTextOnRectangle(renderer, "Idees cadeau :", newWidth/15, newHeight/10*7, font, textColor);
            		drawTextOnRectangle(renderer, "-", newWidth/15*3.5, newHeight/10*7, font, textColor);
            		drawTextOnRectangle(renderer, "+", newWidth/15*14, newHeight/10*7, font, textColor);
            		if(scroll==0){
            		(*cpt)=1;
                        drawTextOnRectangle(renderer, "livre", newWidth/15*4, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "kindle", newWidth/15*5, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "poster", newWidth/15*6.5, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "abonnement", newWidth/15*7.8, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "livre nature", newWidth/15*9.8, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "materiel rando", newWidth/15*11.8, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        }
                        if(scroll==1){
                        (*cpt)=7;
                        drawTextOnRectangle(renderer, "carte cadeau", newWidth/15*4, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "livres recettes", newWidth/15*6.07, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "repas resto", newWidth/15*8.2, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "CD", newWidth/15*10, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "concert", newWidth/15*10.8, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "instrument", newWidth/15*12.1, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        }
                        if(scroll==2){
                        (*cpt)=13;
                        drawTextOnRectangle(renderer, "guide", newWidth/15*4, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "voyage", newWidth/15*5, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "musee", newWidth/15*6.5, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "livre art", newWidth/15*7.8, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "cours", newWidth/15*9.3, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "vin", newWidth/15*10.3, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "degustation", newWidth/15*11, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        drawTextOnRectangle(renderer, "visite cave", newWidth/15*13, newHeight/10*7, font, testColor(cpt, idee, textColor, color2));
                        }
            	
            drawTextOnRectangle(renderer, "<-- retour", 0, newHeight*0.9, font, textColor);

}
void menu3(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, int newWidth, int newHeight, int hobby, int age, int relation, int budget){
		int c=1;
		int *cpt= &c;
            SDL_Color color2 = {0, 255, 0, 255};
            drawTextOnRectangle(renderer, "Hobbies :", newWidth/15, newHeight/10, font, textColor);
                        drawTextOnRectangle(renderer, "Lecture", newWidth/15*2.7, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Cinema", newWidth/15*4, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Plein air", newWidth/15*5.5, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Technologie", newWidth/15*7, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Cuisine", newWidth/15*9, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Musique", newWidth/15*10.5, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Voyage", newWidth/15*12, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Art", newWidth/15*13.4, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                        drawTextOnRectangle(renderer, "Vin", newWidth/15*14.1, newHeight/10, font, testColor(cpt, hobby, textColor, color2));
                       
            (*cpt)=1;            
            drawTextOnRectangle(renderer, "Age :", newWidth/15, newHeight/10*2.5, font, textColor);
            		drawTextOnRectangle(renderer, "-18 ans", newWidth/4, newHeight/10*2.5, font, testColor(cpt, age, textColor, color2));
                        drawTextOnRectangle(renderer, "adulte", newWidth/4*2, newHeight/10*2.5, font, testColor(cpt, age, textColor, color2));
                        drawTextOnRectangle(renderer, "senior", newWidth/4*3, newHeight/10*2.5, font, testColor(cpt, age, textColor, color2));
            	
            (*cpt)=1; 
            drawTextOnRectangle(renderer, "Relation :", newWidth/15, newHeight/10*4, font, textColor);
            		drawTextOnRectangle(renderer, "enfant", newWidth/4, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
                        drawTextOnRectangle(renderer, "famille", newWidth/4*2, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
                        drawTextOnRectangle(renderer, "couple", newWidth/4*3, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
                        drawTextOnRectangle(renderer, "ami", newWidth/4*3.5, newHeight/10*4, font, testColor(cpt, relation, textColor, color2));
            	
            (*cpt)=1; 
            drawTextOnRectangle(renderer, "Budget", newWidth/15, newHeight/10*5.5, font, textColor);
            		drawTextOnRectangle(renderer, "<20", newWidth/4, newHeight/10*5.5, font, testColor(cpt, budget, textColor, color2));
                        drawTextOnRectangle(renderer, "[20;10]", newWidth/4*2, newHeight/10*5.5, font, testColor(cpt, budget, textColor, color2));
                        drawTextOnRectangle(renderer, ">100", newWidth/4*3, newHeight/10*5.5, font, testColor(cpt, budget, textColor, color2));
                        
            	
            drawTextOnRectangle(renderer, "<-- retour", 0, newHeight*0.9, font, textColor);

}

int main(int argc, char* args[]) {
    char * test = readRulesFile("rules.kbs");
    int scroll=0;
    int hobby=0;
    int age=0;
    int relation=0;
    int budget=0;
    int idee=0;
    Rules * list = charToRules(test);
    int menu = 0;
    int newWidth = 1400;
    int newHeight = 600;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initSDL(&window, &renderer)) {
        return 1;
    }

    // Load font
    TTF_Font* font = loadFont("arial.ttf", 28);
    if (font == NULL) {
        return 1;
    }

    // Set color for text 
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color color = {0, 255, 0, 255};

    // Event loop
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw text on a rectangle
        if (menu == 0) {
            drawTextOnRectangle(renderer, "Afficher regles", newWidth/10*4, newHeight/10*2, font, textColor);
            drawTextOnRectangle(renderer, "Test cadeau", newWidth/10*4, newHeight/10*4, font, textColor);
            drawTextOnRectangle(renderer, "Trouve cadeau", newWidth/10*4, newHeight/10*6, font, textColor);
            drawTextOnRectangle(renderer, "quitter", newWidth/10*4, newHeight/10*8, font, textColor);
        } else if (menu == 1) {
            showRulesSDL(renderer, list, font, textColor); 
            drawTextOnRectangle(renderer, "<-- retour", 0, newHeight*0.9, font, color);
        } else if (menu == 2) {
        menu2(renderer, font, textColor, newWidth, newHeight, hobby, age, relation, budget, idee, scroll);
        }
         else if (menu == 3) {
            drawTextOnRectangle(renderer, "<-- retour", 0, newHeight*0.9, font, color);
            menu3(renderer, font, textColor, newWidth, newHeight, hobby, age, relation, budget);
        }
        

        // Update screen
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        printf("Mouse clicked at (%d, %d)\n", mouseX, mouseY);
                        if (menu == 0) {
                            if (mouseX > newWidth/10*4 && mouseX < newWidth/10*4 +200 && mouseY > newHeight/10*2 && mouseY < newHeight/10*2 + 50) {
                                menu = 1;
                            }
                            if (mouseX > newWidth/10*4 && mouseX < newWidth/10*4 +180 && mouseY > newHeight/10*4 && mouseY < newHeight/10*4 + 50) {
                                menu = 2;
                            }
                            if (mouseX > newWidth/10*4 && mouseX < newWidth/10*4 +200 && mouseY > newHeight/10*6 && mouseY < newHeight/10*6 + 50) {
                                menu = 3;
                            }
                        } 
                        else if (menu ==1) {
                            if (mouseX > 0 && mouseX < 140 && mouseY > newHeight*0.9 && mouseY < newHeight*0.9 + 50) {
                                menu = 0;
                            }
                        }
                        else if (menu ==2) {
                            if (mouseX > 0 && mouseX < 140 && mouseY > newHeight*0.9 && mouseY < newHeight*0.9 + 50) {
                                menu = 0;
                            }
                            if (mouseX > newWidth/15*3.5 && mouseX < newWidth/15*3.5 +30 && mouseY > newHeight/10*7 && mouseY < newHeight/10*7 + 40) {
                                if(scroll>0){
                                scroll--;}
                                }
                            if (mouseX > newWidth/15*14 && mouseX < newWidth/15*14 +30 && mouseY > newHeight/10*7 && mouseY < newHeight/10*7 + 40) {
                                if(scroll<2){
                                scroll++;}
                            }
                            if (mouseY > newHeight/10 && mouseY < newHeight/10 + 50){
                                if(mouseX > newWidth/15*2.7 && mouseX < newWidth/15*2.7+110 && (hobby==1 || hobby ==0)){
                                if(hobby==0){
                                hobby=1;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*4 && mouseX < newWidth/15*4+110 && (hobby==2 || hobby ==0)){
                                if(hobby==0){
                                	hobby=2;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*5.5 && mouseX < newWidth/15*5.5+110 && (hobby==3 || hobby ==0)){
                                if(hobby==0){
                                	hobby=3;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*7 && mouseX < newWidth/15*7+110 && (hobby==4 || hobby ==0)){
                                if(hobby==0){
                                	hobby=4;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*9 && mouseX < newWidth/15*9+170 && (hobby==5 || hobby ==0)){
                                if(hobby==0){
                                	hobby=5;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*10.5 && mouseX < newWidth/15*10.5+90 && (hobby==6 || hobby ==0)){
                                if(hobby==0){
                                	hobby=6;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*12 && mouseX < newWidth/15*12+100 && (hobby==7 || hobby ==0)){
                                if(hobby==0){
                                	hobby=7;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*13.4 && mouseX < newWidth/15*13.4+50 && (hobby==8 || hobby ==0)){
                                if(hobby==0){
                                	hobby=8;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*14.1 && mouseX < newWidth/15*14.1+50 && (hobby==9 || hobby ==0)){
                                if(hobby==0){
                                	hobby=9;}
                                else{hobby=0;}
                                }
                                
                            }
                            if (mouseY > newHeight/10*2.5 && mouseY < newHeight/10*2.5 + 60){
                                if(mouseX > newWidth/4 && mouseX < newWidth/4+110 && (age==1 || age ==0)){
                                if(age==0){
                                age=1;}
                                else{age=0;}
                                }
                                if(mouseX > newWidth/4*2 && mouseX < newWidth/4*2+110 && (age==2 || age ==0)){
                                if(age==0){
                                age=2;}
                                else{age=0;}
                                }if(mouseX > newWidth/4*3 && mouseX < newWidth/4*3+110 && (age==3 || age ==0)){
                                if(age==0){
                                age=3;}
                                else{age=0;}
                                }
                                }
                            if (mouseY > newHeight/10*4 && mouseY < newHeight/10*4 + 60){
                                if(mouseX > newWidth/4 && mouseX < newWidth/4+100 && (relation==1 || relation ==0)){
                                if(relation==0){
                                relation=1;}
                                else{relation=0;}
                                }
                                if(mouseX > newWidth/4*2 && mouseX < newWidth/4*2+110 && (relation==2 || relation ==0)){
                                if(relation==0){
                                relation=2;}
                                else{relation=0;}
                                }
                                if(mouseX > newWidth/4*3 && mouseX < newWidth/4*3+100 && (relation==3 || relation ==0)){
                                if(relation==0){
                                relation=3;}
                                else{relation=0;}
                                }
                                if(mouseX > newWidth/4*3.5 && mouseX < newWidth/4*3.5+70 && (relation==4 || relation ==0)){
                                if(relation==0){
                                relation=4;}
                                else{relation=0;}
                                }
                                }
                                if (mouseY > newHeight/10*5.5 && mouseY < newHeight/10*5.5 + 60){
                                if(mouseX > newWidth/4 && mouseX < newWidth/4+70 && (budget==1 || budget ==0)){
                                if(budget==0){
                                budget=1;}
                                else{budget=0;}
                                }
                                if(mouseX > newWidth/4*2 && mouseX < newWidth/4*2+100 && (budget==2 || budget ==0)){
                                if(budget==0){
                                budget=2;}
                                else{budget=0;}
                                }
                                if(mouseX > newWidth/4*3 && mouseX < newWidth/4*3+80 && (budget==3 || budget ==0)){
                                if(budget==0){
                                budget=3;}
                                else{budget=0;}
                                }
                                }
                                if (mouseY > newHeight/10*7 && mouseY < newHeight/10*7 + 60){
                                if(scroll==0){
                                if(mouseX > newWidth/15*4 && mouseX < newWidth/15*4+70 && (idee==1 || idee ==0)){
                                if(idee==0){
                                idee=1;}
                                else{idee=0;}
                                }
                                if(mouseX > newWidth/15*5 && mouseX < newWidth/15*5+100 && (idee==2 || idee ==0)){
                                if(idee==0){
                                idee=2;}
                                else{idee=0;}
                                }
                                if(mouseX > newWidth/15*6.5 && mouseX < newWidth/15*6.5+90 && (idee==3 || idee ==0)){
                                if(idee==0){
                                idee=3;}
                                else{idee=0;}
                                }
                                if(mouseX > newWidth/15*7.8 && mouseX < newWidth/15*7.8+180 && (idee==4 || idee ==0)){
                                if(idee==0){
                                idee=4;}
                                else{idee=0;}
                                }
                                if(mouseX > newWidth/15*9.8 && mouseX < newWidth/15*9.8+180 && (idee==5 || idee ==0)){
                                if(idee==0){
                                idee=5;}
                                else{idee=0;}
                                }
                                if(mouseX > newWidth/15*11.8 && mouseX < newWidth/15*11.8+200 && (idee==6 || idee ==0)){
                                if(idee==0){
                                idee=6;}
                                else{idee=0;}
                                }
                                
                                }
                                if(scroll==1){
		                        if(mouseX > newWidth/15*4 && mouseX < newWidth/15*4+150 && (idee==7 || idee ==0)){
		                        if(idee==0){
		                        idee=7;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*6.07 && mouseX < newWidth/15*6.07+190 && (idee==8 || idee ==0)){
		                        if(idee==0){
		                        idee=8;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*8.2 && mouseX < newWidth/15*8.2+160 && (idee==9 || idee ==0)){
		                        if(idee==0){
		                        idee=9;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*10 && mouseX < newWidth/15*10+60 && (idee==10 || idee ==0)){
		                        if(idee==0){
		                        idee=10;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*10.8 && mouseX < newWidth/15*10.8+120 && (idee==11 || idee ==0)){
		                        if(idee==0){
		                        idee=11;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*12.1 && mouseX < newWidth/15*12.1+150 && (idee==12 || idee ==0)){
		                        if(idee==0){
		                        idee=12;}
		                        else{idee=0;}
		                        }
		                        }
                                if(scroll==2){
		                        if(mouseX > newWidth/15*4 && mouseX < newWidth/15*4+100 && (idee==13 || idee ==0)){
		                        if(idee==0){
		                        idee=13;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*5 && mouseX < newWidth/15*5+100 && (idee==14 || idee ==0)){
		                        if(idee==0){
		                        idee=14;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*6.5 && mouseX < newWidth/15*6.5+100 && (idee==15 || idee ==0)){
		                        if(idee==0){
		                        idee=15;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*7.8 && mouseX < newWidth/15*7.8+130 && (idee==16 || idee ==0)){
		                        if(idee==0){
		                        idee=16;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*9.3 && mouseX < newWidth/15*9.3+100 && (idee==17 || idee ==0)){
		                        if(idee==0){
		                        idee=17;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*10.3 && mouseX < newWidth/15*10.3+70 && (idee==18 || idee ==0)){
		                        if(idee==0){
		                        idee=18;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*11 && mouseX < newWidth/15*11+120 && (idee==19 || idee ==0)){
		                        if(idee==0){
		                        idee=19;}
		                        else{idee=0;}
		                        }
		                        if(mouseX > newWidth/15*13 && mouseX < newWidth/15*13+120 && (idee==20 || idee ==0)){
		                        if(idee==0){
		                        idee=20;}
		                        else{idee=0;}
		                        }
                                }
                                
                               
                                
                                }
                        }
                        else if (menu ==3) {
                            if (mouseX > 0 && mouseX < 140 && mouseY > newHeight*0.9 && mouseY < newHeight*0.9 + 50) {
                                menu = 0;
                            }
                                                        if (mouseY > newHeight/10 && mouseY < newHeight/10 + 50){
                                if(mouseX > newWidth/15*2.7 && mouseX < newWidth/15*2.7+110 && (hobby==1 || hobby ==0)){
                                if(hobby==0){
                                hobby=1;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*4 && mouseX < newWidth/15*4+110 && (hobby==2 || hobby ==0)){
                                if(hobby==0){
                                	hobby=2;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*5.5 && mouseX < newWidth/15*5.5+110 && (hobby==3 || hobby ==0)){
                                if(hobby==0){
                                	hobby=3;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*7 && mouseX < newWidth/15*7+110 && (hobby==4 || hobby ==0)){
                                if(hobby==0){
                                	hobby=4;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*9 && mouseX < newWidth/15*9+170 && (hobby==5 || hobby ==0)){
                                if(hobby==0){
                                	hobby=5;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*10.5 && mouseX < newWidth/15*10.5+90 && (hobby==6 || hobby ==0)){
                                if(hobby==0){
                                	hobby=6;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*12 && mouseX < newWidth/15*12+100 && (hobby==7 || hobby ==0)){
                                if(hobby==0){
                                	hobby=7;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*13.4 && mouseX < newWidth/15*13.4+50 && (hobby==8 || hobby ==0)){
                                if(hobby==0){
                                	hobby=8;}
                                else{hobby=0;}
                                }
                                if(mouseX > newWidth/15*14.1 && mouseX < newWidth/15*14.1+50 && (hobby==9 || hobby ==0)){
                                if(hobby==0){
                                	hobby=9;}
                                else{hobby=0;}
                                }
                                
                            }
                            if (mouseY > newHeight/10*2.5 && mouseY < newHeight/10*2.5 + 60){
                                if(mouseX > newWidth/4 && mouseX < newWidth/4+110 && (age==1 || age ==0)){
                                if(age==0){
                                age=1;}
                                else{age=0;}
                                }
                                if(mouseX > newWidth/4*2 && mouseX < newWidth/4*2+110 && (age==2 || age ==0)){
                                if(age==0){
                                age=2;}
                                else{age=0;}
                                }if(mouseX > newWidth/4*3 && mouseX < newWidth/4*3+110 && (age==3 || age ==0)){
                                if(age==0){
                                age=3;}
                                else{age=0;}
                                }
                                }
                            if (mouseY > newHeight/10*4 && mouseY < newHeight/10*4 + 60){
                                if(mouseX > newWidth/4 && mouseX < newWidth/4+100 && (relation==1 || relation ==0)){
                                if(relation==0){
                                relation=1;}
                                else{relation=0;}
                                }
                                if(mouseX > newWidth/4*2 && mouseX < newWidth/4*2+110 && (relation==2 || relation ==0)){
                                if(relation==0){
                                relation=2;}
                                else{relation=0;}
                                }
                                if(mouseX > newWidth/4*3 && mouseX < newWidth/4*3+100 && (relation==3 || relation ==0)){
                                if(relation==0){
                                relation=3;}
                                else{relation=0;}
                                }
                                if(mouseX > newWidth/4*3.5 && mouseX < newWidth/4*3.5+70 && (relation==4 || relation ==0)){
                                if(relation==0){
                                relation=4;}
                                else{relation=0;}
                                }
                                }
                                if (mouseY > newHeight/10*5.5 && mouseY < newHeight/10*5.5 + 60){
                                if(mouseX > newWidth/4 && mouseX < newWidth/4+70 && (budget==1 || budget ==0)){
                                if(budget==0){
                                budget=1;}
                                else{budget=0;}
                                }
                                if(mouseX > newWidth/4*2 && mouseX < newWidth/4*2+100 && (budget==2 || budget ==0)){
                                if(budget==0){
                                budget=2;}
                                else{budget=0;}
                                }
                                if(mouseX > newWidth/4*3 && mouseX < newWidth/4*3+80 && (budget==3 || budget ==0)){
                                if(budget==0){
                                budget=3;}
                                else{budget=0;}
                                }
                        }
                            
                        }
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        // Update the window dimensions
                        newWidth = event.window.data1;
                        newHeight = event.window.data2;
                        printf("Window size changed to (%d, %d)\n", newWidth, newHeight);
                        SDL_SetWindowSize(window, newWidth, newHeight);
                    }
                    break;
            }
        }
    }

    // Clean up
    TTF_CloseFont(font);
    closeSDL(window, renderer);

    return 0;
}

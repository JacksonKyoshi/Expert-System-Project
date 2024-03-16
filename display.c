#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// Window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// Function to initialize SDL
int initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Create window
    *window = SDL_CreateWindow("SDL Rectangle with Text",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                WINDOW_WIDTH,
                                WINDOW_HEIGHT,
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

// Function to close SDL
void closeSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    int menu = 0;
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

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Event loop
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw text on a rectangle
        if (menu == 0) {
            drawTextOnRectangle(renderer, "Rectangle", 100, 100, font, textColor);
            drawTextOnRectangle(renderer, "Salut", 300, 100, font, textColor);
        } else if (menu == 1) {
            drawTextOnRectangle(renderer, "Bastient fils de", 200, 200, font, color);
        }
        else if (menu == 2) {
            drawTextOnRectangle(renderer, "Tu preferes le chocolat ou", 200, 200, font, color);
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
                            if (mouseX > 100 && mouseX < 240 && mouseY > 100 && mouseY < 150) {
                                menu = 1;
                            }
                            if (mouseX > 300 && mouseX < 380 && mouseY > 100 && mouseY < 150) {
                                
                                menu = 2;
                            }
                        } else if (menu == 1 ||menu == 2) {
                            menu = 0;
                        }
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

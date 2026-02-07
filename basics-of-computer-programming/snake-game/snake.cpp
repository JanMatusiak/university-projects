// program is based on a template provided in the instruction to the project

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define BOARD_HEIGHT 800 // pixels
#define BOARD_WIDTH 800
#define STATUS_HEIGHT 50
#define SNAKE_INIT_POS_Y 500
#define SNAKE_INIT_POS_X 400
#define SNAKE_HEAD_SIZE 25
#define INIT_SNAKE_LENGTH 10  // number of nodes 
#define INITIAL_SNAKE_SPEED 10  // this value is used to calculate the frame refresh delay in ms (units: frames per second, FPS)
#define DELAY_INTERVAL 20   // after how many seconds (so how often) the delay decreases (so the speed increases) 
#define SPEEDUP_FACTOR 10 // in %, by how much will the snake's delay decrease after DELAY_INTERVAL seconds (which will lead to speed's increase)
#define MIN_DELAY 20    // the minimum delay that the snake may have 
#define RED_DOT_DURATION 10 // for how many second the red dot appears
#define RED_DOT_PROBABILITY 1 // in %, what is a probability that in a given frame the red dot will appear
#define NODES_TO_SHORTEN 3  // by how many nodes will the snake shorten its length when the red dot is consumed
#define DELAY_INCREASE_FACTOR 5 // in %, by how much will the snake's delay increase when the red dot is consumed (which will lead to the reduction in snake's speed)
#define BLUE_DOT_POINTS 1
#define RED_DOT_POINTS 2
#define MAX_NAME_LENGTH 20

typedef struct { // struct that holds the parameters of the game
    int t1, t2, rc, direction; // t1 stores the starting time of the game, t2 current time, rc is the window and direction is the direction in which the snake moves 
    double delta, worldTime, delay, speed; // delta is t2-t1, so the time that has passed since the last iteration of the game loop, worldTime adds subsequent deltas to store time since the beginning of the game,  
    bool running; // flag to check whether the game is running
    int score; // store the number of points
} Parameters;

enum direction { // enumeration that represents the possible directions for a snake's movement
    UP,
    DOWN, 
    LEFT, 
    RIGHT 
};

typedef struct snakeNode {  // struct representing the node in a linked list
	int x, y; // coordinates of the snake's head
	struct snakeNode* next; // pointer to the next node in a linked list
} snakeNode;

typedef struct { 
    int x, y; // coordinates of a blue dot
} BlueDot;

typedef struct {
    int x, y; // coordinates of a red dot
    bool isActive; // flag that checks whether the red dot is shown
} RedDot;

typedef struct { // hold info to manage the ranking
    char name[MAX_NAME_LENGTH]; // store the player's name
    int highScore; // store the player's score
} Ranking;

typedef struct { // hold the colors used throughout the game
    Uint32 black, blue, red, green, white;
} Colors;

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void initColors(SDL_Surface *screen, Colors *colors); // initialize colors used throughout the game
void loadRanking(Ranking scores[3]); // open the file with the ranking and read the data
void saveRanking(Ranking scores[3]); // write new data into the file with the ranking
void updateRanking(Ranking scores[3], int currentScore, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Renderer *renderer, SDL_Event event); // update the data in the ranking
BlueDot* createBlueDot(snakeNode** head); // allocate memory for a blue dot
void drawBlueDot(SDL_Surface* screen, BlueDot* dot, Colors *colors); // draw a blue dot
void checkBlueDotCollision(snakeNode** head, BlueDot* dot, SDL_Surface* screen, Parameters* parameters); // handle collision with a blue dot
RedDot* createRedDot(snakeNode** head); // allocate memory for a red dot
void drawRedDot(SDL_Surface* screen, BlueDot* dot, Colors *colors); // draw a red dot
void removeRedDot(SDL_Surface* screen, RedDot* dot, Parameters* parameters, snakeNode** head, Colors *colors); // handle the removal of a red dot when time elapses
void checkRedDotCollision(snakeNode** head, BlueDot* dot, SDL_Surface* screen, Parameters* parameters, Colors *colors); // handle collision with a red dot and apply bonuses
void createProgressBar(SDL_Surface* screen, RedDot* dot, Parameters* parameters, Colors *colors); // create and handle a progress bar
snakeNode* createNode(int x, int y); // create a snake node
snakeNode* createSnake(int length, int startX, int startY); // handle the creation of a snake
void handleKeys(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, snakeNode *head, Ranking scores[3], Colors *colors); 
void moveSnake(snakeNode** head, Parameters *parameters, SDL_Surface* screen, Colors *colors); // handle snake's movement - the tail node is removed, a new node for a head is created
void drawSnake(SDL_Surface* screen, snakeNode* head, Colors *colors); // draw a snake
void initBorder(SDL_Surface *screen, Colors *colors); // create borders
void hitBorder(snakeNode **head, Parameters *parameters); // handle snake's movement after hitting the border
int checkCollision(snakeNode* head); // check for a snake's collision with itself
void calculateTime(Parameters *parameters); 
void displayStatus(SDL_Surface *screen, SDL_Surface *charset, Parameters *parameters, RedDot* reddot, Colors *colors); // create a status window at the top
void initParameters(Parameters *parameters); // initialize the necessary parameters
void resetGame(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, snakeNode *head, Ranking scores[3], Colors *colors); //reset the parameters, to start over
void speedUp(Parameters* parameters); // handle the delay's decrease as the game progresses
void startGame(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, Ranking scores[3], Colors *colors); // handle the events of a game loop
void youLost(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, snakeNode *snakeHead, Parameters *parameters, Ranking scores[3], Colors *colors); // handle game over window and events
void showMenu(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, Ranking scores[3], Colors *colors); // show the initial menu

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset){ // draw a text txt on surface screen, starting from the point (x, y)
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
	}

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y){ // draw a surface sprite on a surface screen in point (x, y), where (x, y) is the center of sprite on screen
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color){ // draw a single pixel
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
	}

void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color){ // draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	}

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor){ // draw a rectangle of size l by k
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}

void initColors(SDL_Surface *screen, Colors *colors){
    colors->black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    colors->blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
    colors->red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
    colors->green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
    colors->white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
}

void loadRanking(Ranking scores[3]){  // the function takes the argument scores, which is the array of Ranking structures
    FILE *file = fopen("ranking.txt", "r"); // open ranking.txt in read mode
    if(file){ 
        for(int i = 0; i < 3; i++){
            if(fscanf(file, "%s %d", scores[i].name, &scores[i].highScore) != 2){  // read the data from the file
                strcpy(scores[i].name, "None");
                scores[i].highScore = 0; 
                // assigning default values if the program does not read the name or the score
            }
        }
        fclose(file);
    } else { // if the file fails to open, default values are assigned
        for(int i = 0; i < 3; i++) {
            strcpy(scores[i].name, "None");
            scores[i].highScore = 0;
        }
    }
}

void saveRanking(Ranking scores[3]) {
    FILE *file = fopen("ranking.txt", "w"); // open ranking.txt in write mode
    if(file){
        for(int i = 0; i < 3; i++){
            fprintf(file, "%s %d\n", scores[i].name, scores[i].highScore); // write the player's name and score into the file
        }
        fclose(file);
    }
}

void updateRanking(Ranking scores[3], int currentScore, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Renderer *renderer, SDL_Event event) {
    for(int i = 0; i < 3; i++){
        if(currentScore > scores[i].highScore){ 
            for(int j = 2; j > i; j--){ // making space for the new score in the ranking
                scores[j] = scores[j - 1];
            }

            SDL_StartTextInput();

            char playerName[MAX_NAME_LENGTH] = ""; // a string to store the player's name
            bool typing = true; // flag to check whether the player is still typing his name

            while(typing){
                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
                
                char text[128];
                snprintf(text, sizeof(text), "New High Score: %d!", currentScore);
                DrawString(screen, 10, 10, text, charset);

                snprintf(text, sizeof(text), "Enter your name: %s", playerName);
                DrawString(screen, 10, 30, text, charset);

                snprintf(text, sizeof(text), "Press Enter to confirm");
                DrawString(screen, 10, 50, text, charset);

                SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                SDL_RenderPresent(renderer);

                while(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                        typing = false;
                        strncpy(playerName, "Unknown", sizeof(playerName)); // if the user quits the program, the name is set to Unknown
                        break;
                    } else if(event.type == SDL_KEYDOWN){
                        if(event.key.keysym.sym == SDLK_BACKSPACE && strlen(playerName) > 0) {
                            playerName[strlen(playerName) - 1] = '\0'; // functionality of a backspace key
                        } else if(event.key.keysym.sym == SDLK_RETURN){ 
                            typing = false; // the loop ends when the player clicks "Enter"
                        }
                    } else if(event.type == SDL_TEXTINPUT) {
                        if(strlen(playerName) < sizeof(playerName) - 1){ // add the letter to the name, as long as it does not exceed the maximum size
                            strcat(playerName, event.text.text);
                        }
                    }
                }
            }

            SDL_StopTextInput();

            // updating the high score
            strncpy(scores[i].name, playerName, sizeof(scores[i].name));
            scores[i].name[sizeof(scores[i].name) - 1] = '\0';
            scores[i].highScore = currentScore;
            break;
        }
    }
}

BlueDot* createBlueDot(snakeNode** head) {
    BlueDot* dot = (BlueDot*)malloc(sizeof(BlueDot));
    snakeNode* current;

    bool validPosition = false; 

    while(validPosition == false){
        // randomly generate the coordinates of the dot so that they align with the grid set by the snake's head size
        dot->x = (rand() % (BOARD_WIDTH / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE; 
        dot->y = (rand() % ((BOARD_HEIGHT - STATUS_HEIGHT) / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE + STATUS_HEIGHT; // adjusted by the status' height

        validPosition = true;
        current = *head;

        while(current != NULL){ // iterate through the snake's nodes to check if the dot does not appear on the snake
            if(dot->x == current->x && dot->y == current->y){
                validPosition = false;
                break;
            }
            current = current->next;
        }
    }

    return dot;
}

void drawBlueDot(SDL_Surface* screen, BlueDot* dot, Colors *colors){
    DrawRectangle(screen, dot->x, dot->y, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, colors->blue, colors->blue);
}

void checkBlueDotCollision(snakeNode** head, BlueDot* dot, SDL_Surface* screen, Parameters* parameters){
    if((*head)->x == dot->x && (*head)->y == dot->y){ // if the snake's head collides with the blue dot
        snakeNode* current = *head;
        while(current->next != NULL){ // iterate through the linked list of the snake until the last node is reached
            current = current->next;
        }
        snakeNode* newTail = createNode(current->x, current->y); // a new node is create at the tail
        current->next = newTail;
        parameters->score+=BLUE_DOT_POINTS; // increment the score

        // regenerate the blue dot (again, make sure it does not appear on the snake)
        bool validPosition = false;

        while(validPosition == false){
            dot->x = (rand() % (BOARD_WIDTH / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE;
            dot->y = (rand() % ((BOARD_HEIGHT - STATUS_HEIGHT) / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE + STATUS_HEIGHT;

            validPosition = 1;
            current = *head;

            while(current != NULL){
                if(dot->x == current->x && dot->y == current->y){
                    validPosition = 0;
                    break;
                }
                current = current->next;
            }
        }
    }
}

RedDot* createRedDot(snakeNode** head){
    RedDot* dot = (RedDot*)malloc(sizeof(RedDot));
    snakeNode* current;

    bool validPosition = false;

    // make sure that the dot does not appear on the snake
    while (!validPosition) {
        dot->x = (rand() % (BOARD_WIDTH / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE;
        dot->y = (rand() % ((BOARD_HEIGHT - STATUS_HEIGHT) / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE + STATUS_HEIGHT;

        validPosition = true;
        current = *head;

        while (current != NULL){
            if (dot->x == current->x && dot->y == current->y) {
                validPosition = false;
                break;
            }
            current = current->next;
        }
    }

    dot->isActive = false;

    return dot;
}

void drawRedDot(SDL_Surface* screen, RedDot* dot, Colors *colors){
    if(dot->isActive == false){
        int c = rand() % 100; // number between 0 and 99 is drawn in each iteration
        if(c < RED_DOT_PROBABILITY){ // if the number is less than a set number, the red dot appears
            DrawRectangle(screen, dot->x, dot->y, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, colors->red, colors->red);
            dot->isActive = true; // flag to mark the red dot to appear
        }
    }
}

void removeRedDot(SDL_Surface* screen, RedDot* dot, Parameters* parameters, snakeNode** head, Colors *colors){
    static double lastWorldTime = 0;
    if(dot->isActive == false){
        lastWorldTime = parameters->worldTime; // when the red dot is not yet shown, the lastworldtime is initialized with current game time
    }
    if(dot->isActive == true && parameters->worldTime - lastWorldTime >= RED_DOT_DURATION){ // if the dot is drawn and specific time interval elapses 
        DrawRectangle(screen, dot->x, dot->y, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, colors->black, colors->black); // draw a black rectangle over the red dot 
        dot->isActive = false; // set the red dot as inactive

        snakeNode* current;

        bool validPosition = false;

        // make sure that the dot does not appear on the snake
        while (!validPosition){
            dot->x = (rand() % (BOARD_WIDTH / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE;
            dot->y = (rand() % ((BOARD_HEIGHT - STATUS_HEIGHT) / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE + STATUS_HEIGHT;

            validPosition = true;
            current = *head;

            while(current != NULL){
                if(dot->x == current->x && dot->y == current->y){
                    validPosition = false;
                    break;
                }
                current = current->next;
            }
        }
        lastWorldTime = parameters->worldTime;
    }
}

void checkRedDotCollision(snakeNode** head, RedDot* dot, SDL_Surface* screen, Parameters* parameters, Colors *colors){
    int c = rand() % 2; // randomly draw one of the two bonuses

    int snakeLength = 0; // we calculate current snake's length
    snakeNode* temp = *head;
    while(temp->next != NULL) {
        snakeLength++;
        temp = temp->next;
    }

    if ((*head)->x == dot->x && (*head)->y == dot->y && dot->isActive == true){
        parameters->score+=RED_DOT_POINTS; // increment the score
        if(c == 0 || snakeLength <= NODES_TO_SHORTEN){ // 50% probability for either bonus
            parameters->delay *= (100 + DELAY_INCREASE_FACTOR)/100.0; // increase the delay (so decrease the speed)
        } else if(c == 1 && snakeLength > NODES_TO_SHORTEN){
            int removedUnits = 0; // tracks how many nodes have been removed from the snake

            while(removedUnits < NODES_TO_SHORTEN){ 
                snakeNode* current = *head;
                snakeNode* previous = NULL;

                while(current->next != NULL){
                    previous = current;
                    current = current->next;
                }

                if(previous != NULL){ // ensure the snake has more than one node
                    DrawRectangle(screen, current->x, current->y, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, colors->black, colors->black); // draw a black node over the last segment 
                    free(current);
                    previous->next = NULL; // the new tail
                } else {
                    break; // do not remove if the snake has only one segment
                }
                removedUnits++;
            }
        }

        // generate a new position for the red dots
        snakeNode* current;

        bool validPosition = false;

        // make sure that the dot does not appear on the snake
        while(!validPosition){
            dot->x = (rand() % (BOARD_WIDTH / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE;
            dot->y = (rand() % ((BOARD_HEIGHT - STATUS_HEIGHT) / SNAKE_HEAD_SIZE)) * SNAKE_HEAD_SIZE + STATUS_HEIGHT;

            validPosition = true;
            current = *head;

            while(current != NULL){
                if(dot->x == current->x && dot->y == current->y){
                    validPosition = false;
                    break;
                }
            current = current->next;
            }
        }
    dot->isActive = false;
    }
}

void createProgressBar(SDL_Surface* screen, RedDot* dot, Parameters* parameters, Colors *colors){
    static double lastWorldTime = 0;

    // position and height of the progress bar
    int barX = 575; 
    int barY = 20;
    int barHeight = 20;
    int barMaxWidth = 200; // width of the progress bar 

    if(dot->isActive){
        if(lastWorldTime == 0){ // if the red dot is about to be activated
            lastWorldTime = parameters->worldTime; // lastworldtime is set to current time
        }

        double elapsed = parameters->worldTime - lastWorldTime; // time since the red dot has become active
        double remainingTime = RED_DOT_DURATION - elapsed; // remainig time before the dot expires

        if(remainingTime > 0){
            int progressBarWidth = (int)((remainingTime / RED_DOT_DURATION) * barMaxWidth); // draw the portion of the progress bar signaling the remaining time before the dot expires
            DrawRectangle(screen, barX, barY, barMaxWidth, barHeight, colors->white, colors->white); // a white rectangle is drawn to show the time that has elapsed
            DrawRectangle(screen, barX, barY, progressBarWidth, barHeight, colors->red, colors->red); // a red rectangle is drawn to represent the remaining time
        } else { // if the dot expires
            lastWorldTime = 0; 
            DrawRectangle(screen, barX, barY, barMaxWidth, barHeight, colors->blue, colors->blue); // the progress bar is cleared
        }
    } else { // if the red dot is inactive
        lastWorldTime = 0; 
        DrawRectangle(screen, barX, barY, barMaxWidth, barHeight, colors->blue, colors->blue);  // the progress bar is filled with blue (so no progress bar is visible)
    }
}

snakeNode* createNode(int x, int y){
    snakeNode* newNode = (snakeNode*)malloc(sizeof(snakeNode)); 
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL; // to indicate that the node does not link to any other node yet, needed for the end of the snake
    return newNode; // return the pointer to the new node
}

snakeNode* createSnake(int length, int startX, int startY){
    snakeNode* head = createNode(startX, startY); // the head is created on the given coordinates

    snakeNode* current = head; // the 'current' pointer will be used to traverse the snake
    for(int i = 0; i < length; i++){ // traverse the snake to create additional nodes
        snakeNode* newNode = createNode(current->x, current->y + SNAKE_HEAD_SIZE); // initially, the snake gorws downwards, as the snake's initial position is vertical 
        current->next = newNode; 
        current = newNode; 
    }
    return head; // return the head, which is the beginning of the linked list
}

void handleKeys(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, snakeNode *head, Ranking scores[3], Colors *colors){
    switch(event.key.keysym.sym)
        {
			case SDLK_ESCAPE: 
				parameters->running = false; // quit the game
				break;
            case SDLK_n:
				resetGame(screen, scrtex, charset, window, renderer, event, parameters, head, scores, colors); // start over
				break;
            case SDLK_DOWN:
				if(parameters->direction != UP && head->y != BOARD_HEIGHT - SNAKE_HEAD_SIZE){ // unless the snake moves upwards or is at the bottom border
                parameters->direction = DOWN;
				}
                break;
            case SDLK_UP:
				if(parameters->direction != DOWN && head->y != STATUS_HEIGHT){ // unless the snake moves downwards or is at the upper border 
                parameters->direction = UP;
				}
                break;
            case SDLK_LEFT:
				if(parameters->direction != RIGHT && head->x != 0){ // unless the snake moves to the right or is at the left border
                parameters->direction = LEFT;
				}
                break;
            case SDLK_RIGHT:
				if(parameters->direction != LEFT && head->x != BOARD_WIDTH - SNAKE_HEAD_SIZE){ // unless the snake moves to the left or is at the right border
                parameters->direction = RIGHT;
				}
                break;
        }
}

void moveSnake(snakeNode** head, Parameters *parameters, SDL_Surface* screen, Colors *colors){

    // determine the new coordinates of the snake's head
    // currently, they are set to the current snake's head's coordinates
    int newX = (*head)->x;
    int newY = (*head)->y;

    switch(parameters->direction){ // depending on the current direction, new head's coordinates are determined
        case UP:
            newY -= SNAKE_HEAD_SIZE;
            break;
        case DOWN:
            newY += SNAKE_HEAD_SIZE;
            break;
        case LEFT:
            newX -= SNAKE_HEAD_SIZE;
            break;
        case RIGHT:
            newX += SNAKE_HEAD_SIZE;
            break;
    }

    snakeNode* newHead = createNode(newX, newY); // new head is created at a calculated position
    newHead->next = *head; 
    *head = newHead;  

        snakeNode* current = *head;

        while(current->next->next != NULL){ // the snake is traversed to find the second-to-last node
            current = current->next;
        }

        snakeNode* tail = current->next; // the tail pointer points to the last node

        DrawRectangle(screen, tail->x, tail->y, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, colors->black, colors->black);  // the tail is filled with black, visually making it disappear

        current->next = NULL; // remove the reference to the previous tail
        free(tail);
    
}

void drawSnake(SDL_Surface* screen, snakeNode* head, Colors *colors){
    snakeNode* current = head;
    while(current != NULL){ // used to traverse the snake - as long as there is a node, a green rectangle is drawn
        DrawRectangle(screen, current->x, current->y, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, colors->green, colors->green);
        current = current->next;
    }
}

void initBorder(SDL_Surface *screen, Colors *colors){ // initialize the borders of the board
	DrawLine(screen, 0, STATUS_HEIGHT, BOARD_WIDTH, 1, 0, colors->red);
	DrawLine(screen, 0, BOARD_HEIGHT - 1, BOARD_WIDTH, 1, 0, colors->red);
	DrawLine(screen, 0, STATUS_HEIGHT, BOARD_HEIGHT, 0, 1, colors->red);
	DrawLine(screen, BOARD_WIDTH - 1, STATUS_HEIGHT, BOARD_WIDTH, 0, 1, colors->red);
}

void hitBorder(snakeNode **head, Parameters *parameters){ 
	if(parameters->direction == RIGHT && (*head)->x >= BOARD_WIDTH - SNAKE_HEAD_SIZE){ // if the snake hits the right border
		if((*head)->y == BOARD_HEIGHT - SNAKE_HEAD_SIZE)
			parameters->direction = UP; // move up if the snake is at the bottom border
		else{
			parameters->direction = DOWN; // by default, move down
		}
	}
	if(parameters->direction == LEFT && (*head)->x <= 0){ // if the snake hits the left border
		if((*head)->y == STATUS_HEIGHT){
			parameters->direction = DOWN; // move down if the snake is at the upper border
		}
		else{
			parameters->direction = UP; // by default, move up
		}
	}
	if(parameters->direction == DOWN && (*head)->y >= BOARD_HEIGHT - SNAKE_HEAD_SIZE){ // if the snake hits the bottom border
		if((*head)->x == 0){
			parameters->direction = RIGHT; // move right if the snake is at the left border
		}
		else{
			parameters->direction = LEFT; // by default, move left
		}
	}
	if(parameters->direction == UP && (*head)->y <= STATUS_HEIGHT){ // if the snake hits the upper border
		if((*head)->x == BOARD_WIDTH - SNAKE_HEAD_SIZE){
			parameters->direction = LEFT; // move left if the snake is at the right border
		}
		else{
			parameters->direction = RIGHT; // by default, move right
		}
	}
}

int checkCollision(snakeNode* head){
    snakeNode* current = head->next;
    while(current != NULL){ // traverse the snake's body to check for collision with any of its segments
        if(head->x == current->x && head->y == current->y){ 
            return 1; // return 1 in case of a collision
        }
        current = current->next;
    }
    return 0; // return 0 if no collision is detected
}

void calculateTime(Parameters *parameters){
    // here t2-t1 is the time in milliseconds since the last screen was drawn
    // delta is the same time in seconds
	parameters->t2 = SDL_GetTicks(); 
	parameters->delta = (parameters->t2 - parameters->t1) * 0.001;
	parameters->t1 = parameters->t2;
    parameters->worldTime += parameters->delta;
}

void displayStatus(SDL_Surface *screen, SDL_Surface *charset, Parameters *parameters, RedDot* reddot, Colors *colors){
    char text[128];
    DrawRectangle(screen, 4, 4, BOARD_WIDTH - 8, STATUS_HEIGHT - 4, colors->red, colors->blue); // draw a status zone
    // display info about the game
    snprintf(text, sizeof(text), "Elapsed time = %.1lf s", parameters->worldTime);
	DrawString(screen, 8, 8, text, charset);
    snprintf(text, sizeof(text), "Current score: %d", parameters->score);
	DrawString(screen, 8, 20, text, charset);
	snprintf(text, sizeof(text), "Esc - exit");
	DrawString(screen, 8, 32, text, charset);
    snprintf(text, sizeof(text), "Implemented requirements: 1-4, A, B, C, D, F");
    DrawString(screen, 200, 8, text, charset);

    createProgressBar(screen, reddot, parameters, colors); // call the progress bar function
}

void initParameters(Parameters *parameters){
    parameters->direction = 0;
    parameters->running = true;
	parameters->t1 = SDL_GetTicks();
	parameters->worldTime = 0;
    parameters->score = 0;
    parameters->speed = INITIAL_SNAKE_SPEED;
    parameters->delay = 1000/parameters->speed;
}

void resetGame(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, snakeNode *head, Ranking scores[3], Colors *colors){
    // free the memory for the snake's body, except for the head, which is needed to reinitialize the snake 
    snakeNode *current = head->next;
    while(current != NULL){
        snakeNode *temp = current;
        current = current->next;
        free(temp);
    }
    initParameters(parameters); // reinitialize the game parameters

    startGame(screen, scrtex, charset, window, renderer, event, parameters, scores, colors); // reinitialize the game loop
}

void speedUp(Parameters* parameters) {
    static double lastWorldTime = 0; // keep track of the last time the speedUp was applied

    if(parameters->worldTime - lastWorldTime >= DELAY_INTERVAL && parameters->delay > MIN_DELAY){ // if enough time has passed since the last speedUp and the delay is not at its minimum yet 
        parameters->delay *= (100 - SPEEDUP_FACTOR)/100.0; // decrease the delay by the set factor, which effectively increases the speed
        lastWorldTime = parameters->worldTime; // update the lastworldtime
    }
}

void startGame(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, Ranking scores[3], Colors *colors){
    SDL_SetColorKey(charset, true, 0x000000); // black pixels will be transparent

    // create the snake and dots
    snakeNode* snakeHead = createSnake(INIT_SNAKE_LENGTH, SNAKE_INIT_POS_X, SNAKE_INIT_POS_Y); 
    BlueDot* bluedot = createBlueDot(&snakeHead);
    RedDot* reddot = createRedDot(&snakeHead);

    SDL_FillRect(screen, NULL, colors->black); // clear the screen 

    while(parameters->running){
        initBorder(screen, colors);
        calculateTime(parameters);
        displayStatus(screen, charset, parameters, reddot, colors);

        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderCopy(renderer, scrtex, NULL, NULL);

        drawSnake(screen, snakeHead, colors);
        moveSnake(&snakeHead, parameters, screen, colors);

        drawBlueDot(screen, bluedot, colors);
        checkBlueDotCollision(&snakeHead, bluedot, screen, parameters);
        drawRedDot(screen, reddot, colors);
        checkRedDotCollision(&snakeHead, reddot, screen, parameters, colors);
        removeRedDot(screen, reddot, parameters, &snakeHead, colors);

        speedUp(parameters);
        hitBorder(&snakeHead, parameters);

        if(checkCollision(snakeHead) == 1){ // handle the collision of a snake with itself
            SDL_Delay(100);
            youLost(screen, scrtex, charset, window, renderer, event, snakeHead, parameters, scores, colors);
            parameters->running = false;
        }

        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)) {
            handleKeys(screen, scrtex, charset, window, renderer, event, parameters, snakeHead, scores, colors);
        }
        
        SDL_Delay(parameters->delay);
    }

    free(bluedot);
    free(reddot);
    free(snakeHead);
}

void youLost(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, snakeNode *snakeHead, Parameters *parameters, Ranking scores[3], Colors *colors){
    char text[128];

    // handle the ranking update
    updateRanking(scores, parameters->score, screen, scrtex, charset, renderer, event);
    saveRanking(scores);
    
    while(parameters->running){ // while the game is running
        SDL_FillRect(screen, NULL, colors->black); // clear the screen

        // display info
        snprintf(text, sizeof(text), "You lost");
	    DrawString(screen, 1, 0, text, charset);
        snprintf(text, sizeof(text), "Your score: %d", parameters->score);
        DrawString(screen, 1, 15, text, charset);

        DrawString(screen, 1, 30, "High Scores:", charset);
        for(int i = 0; i < 3; i++){
            snprintf(text, sizeof(text), "%d %s - %d", i + 1, scores[i].name, scores[i].highScore);
            DrawString(screen, 1, 45 + (i * 15), text, charset); 
        }
        snprintf(text, sizeof(text), "Press n to play again");
        DrawString(screen, 1, 90, text, charset);
        snprintf(text, sizeof(text), "Press Esc to exit");
        DrawString(screen, 1, 105, text, charset);

        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderCopy(renderer, scrtex, NULL, NULL);
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)){
            handleKeys(screen, scrtex, charset, window, renderer, event, parameters, snakeHead, scores, colors);
        }
    }
}

void showMenu(SDL_Surface *screen, SDL_Texture *scrtex, SDL_Surface *charset, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, Parameters *parameters, Ranking scores[3], Colors *colors){
    char text[128];

    initParameters(parameters); 
    
    while(parameters->running){
        SDL_FillRect(screen, NULL, colors->black);
        // display info
        snprintf(text, sizeof(text), "Welcome to the Snake!");
        DrawString(screen, 1, 0, text, charset);
        snprintf(text, sizeof(text), "Press n to START");
        DrawString(screen, 1, 15, text, charset);
        snprintf(text, sizeof(text), "Press Esc to EXIT");
        DrawString(screen, 1, 30, text, charset);

        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderCopy(renderer, scrtex, NULL, NULL);
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_n){ // start the game loop
                    startGame(screen, scrtex, charset, window, renderer, event, parameters, scores, colors);
                }
                if(event.key.keysym.sym == SDLK_ESCAPE){ // quit
                    parameters->running = false;
                    return;
                }
            }
        }
    }
}

int main(int argc, char **argv){
    SDL_Event event;
    SDL_Surface *screen, *charset;
    SDL_Texture *scrtex;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Parameters *parameters = (Parameters*)malloc(sizeof(Parameters));
    Colors *colors = (Colors*)malloc(sizeof(Colors));
    Ranking scores[3];
    loadRanking(scores);

    srand(time(NULL)); 

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    if(parameters == NULL){
        printf("Failed to allocate memory for parameters\n");
        return 1;
    }

    if(colors == NULL){
        printf("Memory allocation for colors failed\n");
        return 1;
    }

    parameters->rc = SDL_CreateWindowAndRenderer(BOARD_WIDTH, BOARD_HEIGHT, 0, &window, &renderer);

    if (parameters->rc != 0) {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, BOARD_WIDTH, BOARD_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_SetWindowTitle(window, "SNAKE, s203290, Jan Matusiak");

    screen = SDL_CreateRGBSurface(0, BOARD_WIDTH, BOARD_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, BOARD_WIDTH, BOARD_HEIGHT);

    if(screen == NULL || scrtex == NULL) {
        printf("Failed to initialize screen or scrtex\n");
        return 1;
    }

    SDL_ShowCursor(SDL_DISABLE); // disable the cursor

    charset = SDL_LoadBMP("./cs8x8.bmp");
    if (charset == NULL) {
        printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
        SDL_FreeSurface(screen);
        SDL_DestroyTexture(scrtex);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    }

    initColors(screen, colors);
    showMenu(screen, scrtex, charset, window, renderer, event, parameters, scores, colors); 

    // free allocated resources
    SDL_FreeSurface(charset);
    SDL_FreeSurface(screen);
    SDL_DestroyTexture(scrtex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free(parameters);
    free(colors);

    SDL_Quit();
    return 0;
}

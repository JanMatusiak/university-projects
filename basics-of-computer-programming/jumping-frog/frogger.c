#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#define GAME_WIDTH 200 // size of the board
#define GAME_HEIGHT 50
#define GAME_Y_COORD 10 // initial coordinates of the game window 
#define GAME_X_COORD 5
#define NUMBER_OF_LANES 8 // excluding the top and bottom safe zone
#define MAX_COLOR_LENGTH 7 // the longest name of a color supported by ncurses is magenta of length 7

/* declaring structs that target different parts of the game */
typedef struct { // struct that contains the window with the main board as well as some parameters of the game
    WINDOW* window;  
    char lane_color[MAX_COLOR_LENGTH];
    char safe_color[MAX_COLOR_LENGTH];
    int lane_height; // calculated based on GAME_HEIGHT and NUMBER_OF_LANES
} GAME;

typedef struct { // struct that contains the parameters of the frog
    WINDOW* window;
    int position_x; // coordinates of the frog
    int position_y;
    int size;
    char frog_color[MAX_COLOR_LENGTH];
} FROG;

typedef struct { // struct that contains the parameters of individual cars
    WINDOW* window; 
    int pos_x; // coordinates of a car
    int pos_y;
    int og_pos_y; // store the original lane (for cars that disappear)
    int speed;
    int og_speed; // store the original speed (for cars that disappear or stop their movement when the frog is close)
    int direction; // whether it moves from the left or from the right
    int delay; // time that passes since the beginning of the game before the car appears on the screen
    int is_moving; // indicates whether the car is already in movement, to prevent the delay in subsequent routes
} CAR;

typedef struct { // struct that contains the parameters that are the same for all cars, as well as a pointer to an array of pointers to CAR structures, which represent individual cars
    int car_length;
    int car_height;
    int max_speed;
    char car_color[MAX_COLOR_LENGTH];
    CAR **car; // a pointer to an array of pointers to CAR structures
} CARS;

typedef struct { // struct that contains the parameters to create a status window
    WINDOW *window;
    int status_height; 
    int status_width;
    int time_limit; // how much time the player has to move the frog
} STATUS;

/* declaring functions that take care of different parts of the game */
void freeMemory(GAME *game, CARS *cars, FROG *frog, STATUS *status); // free dynamically allocated memory for all structs
void loadConfigurations(GAME *game, FROG *frog, CARS *cars, STATUS *status); // load the parameters from the separate configuration file
void initValues(GAME *game, FROG *frog, CARS *cars); // set the values that do not change and/or are predefined
int getColor(char *color_name); // read and set the color 
void initStatus(time_t start_time, STATUS *status); // create the timer
void timeElapsed(GAME *game, FROG *frog, CARS *cars, STATUS *status); // display the ending screen in case the time elapses (the player fails to move within certain time)
void collision(GAME *game, FROG *frog, CARS *cars, STATUS *status); // display the ending screen in case of collision
int checkForLoss(GAME *game, FROG *frog, CARS *cars, STATUS *status, time_t current_time, time_t last_input_time); // check if the player lost (so whether time elapsed or collision happened)
void youWin(GAME *game, FROG *frog, CARS *cars, STATUS *status); // display the ending screen in case of reaching the end of the board
int checkForWin(GAME *game, FROG *frog, CARS *cars, STATUS *status); // check if the player won
void resetTheGame(GAME *game, FROG *frog, CARS *cars, STATUS *status);  // reset the game to the initial state after the player wins or loses
void initObstacle(GAME *game); // draw the obstacle on the middle safe lane
void initLanes(GAME *game, FROG *frog); // draw the lanes 
void initFrog(FROG *frog); // create the frog
void moveFrog(GAME *game, FROG *frog, int direction); // allow for the movement of the frog
void initCars(GAME *game, CARS *cars); // create cars
void wrapping(GAME *game, CARS *cars, int index); // ensure that the cars are wrapping when reaching the edge of the board
void stopMovement(GAME *game, FROG *frog, CARS *cars); // stop cars on lane 2 and 4 if the frog is close to them
void moveCars(GAME *game, FROG *frog, CARS *cars, time_t start_time); // take care of the random and constant movement of cars
int checkCollision(GAME *game, FROG *frog, CARS *cars);  // check for collisions between a frog and cars
void randomCarIndexes(GAME *game, int *a, int *b, int *c, int *d); // randomly generate which cars will have their speed increased and which will disappear
void modifyCars(GAME *game, CARS *cars, int elapsed_time, int *increased, int *disappeared, int *reappeared, time_t *disappear_time_c, time_t *disappear_time_d, int a, int b, int c, int d); // handle functions increaseSpeed and disappearCar
void increaseSpeed(GAME *game, CARS *cars, int elapsed_time, int *increased, int a, int b); // increase the speed of certain cars
void removeCar(CARS *cars, int index); // remove a certain car when it reaches the border
void handleDisappearance(GAME *game, CARS *cars, int elapsed_time, int *disappeared, time_t *disappear_time_c, time_t *disappear_time_d, int c, int d); // control when the cars are removed
void showCar(GAME *game, CARS *cars, int new_pos_x, int index); // recreate the car that disappeared at a random position within that lane
void handleReappearance(GAME *game, CARS *cars, int *disappeared, int *reappeared, time_t *disappear_time_c, time_t *disappear_time_d, int c, int d, int new_pos_xc, int new_pos_xd); // control when the cars reappear
void disappearCar(GAME *game, CARS *cars, int elapsed_time, int *disappeared, int *reappeared, time_t *disappear_time_c, time_t *disappear_time_d, int c, int d); // combine the previous four functions to control when certain cars disappear and reappear
void setUp(GAME *game, FROG *frog, CARS *cars, time_t start_time); // update the game setup after each loop in the initGame function
void initGame(GAME *game, FROG *frog, CARS *cars, STATUS *status); // initialize the board with all its elements
void start(GAME *game, FROG *frog, CARS *cars, STATUS *status); // display the starting screen


void freeMemory(GAME *game, CARS *cars, FROG *frog, STATUS *status){
    free(game); // free the GAME struct
    free(frog); // free the frog struct
    free(status); // free the status struct
    for(int i = 0; i < NUMBER_OF_LANES; i++){
        if(i != 3){
            free(cars->car[i]); // free each individual car
        }
    }
    free(cars->car); // free the array of CAR pointers
    free(cars); // free the CARS struct
}

void loadConfigurations(GAME *game, FROG *frog, CARS *cars, STATUS *status){
    FILE *file = fopen("config.txt", "r"); // open the file "config.txt" where the configurations are
    if(!file){
        printf("Error while opening the file\n"); // display a message if error occurs
        exit(1);
    }
    fscanf(file, "status_height = %d\n", &status->status_height);
    fscanf(file, "status_width = %d\n", &status->status_width);
    fscanf(file, "time_limit = %d\n", &status->time_limit);
    fscanf(file, "car_length = %d\n", &cars->car_length);
    fscanf(file, "max_speed = %d\n", &cars->max_speed);
    fscanf(file, "car_color = %s\n", cars->car_color);
    fscanf(file, "safe_color = %s\n", game->safe_color);
    fscanf(file, "frog_color = %s\n", frog->frog_color);
    fclose(file); 
}

void initValues(GAME *game, FROG *frog, CARS *cars){
    game->lane_height = GAME_HEIGHT/(NUMBER_OF_LANES + 2); // = 5
    frog->size = game->lane_height - 1; // = 4
    frog->position_x = GAME_X_COORD + (GAME_WIDTH - frog->size)/2; // = 103
    frog->position_y = GAME_Y_COORD + GAME_HEIGHT - frog->size; // = 56
    cars->car_height = frog->size; // = 4
}

int getColor(char* color_name){
    if(color_name == NULL){ // ensure that the colors were read from the file
        printf("The color wasn't read from the file\n");
        return COLOR_BLACK;
    }

    // set the color based on what was read from the file
    if(strcmp(color_name, "black") == 0){
        return COLOR_BLACK;
    } else if(strcmp(color_name, "red") == 0){
        return COLOR_RED;
    } else if(strcmp(color_name, "green") == 0){
        return COLOR_GREEN;
    } else if(strcmp(color_name, "yellow") == 0){
        return COLOR_YELLOW;
    } else if(strcmp(color_name, "blue") == 0){
        return COLOR_BLUE;
    } else if(strcmp(color_name, "magenta") == 0){
        return COLOR_MAGENTA;
    } else if(strcmp(color_name, "cyan") == 0){
        return COLOR_CYAN;
    } else if(strcmp(color_name, "white") == 0){ 
        return COLOR_WHITE;
    } else{ // set the default color to black
        return COLOR_BLACK;
    }
}

void initStatus(time_t start_time, STATUS *status){
    status->window = newwin(status->status_height, status->status_width, 0, 0); // create a window in the upper corner for status 
    box(status->window, '#', '#');
    time_t current_time = time(NULL); // read the current time
    int elapsed_time = (int)difftime(current_time, start_time); // store the difference between the start time and the current time (so the time that elapsed from the beginning of the game)

    /* display the content of the status window */
    mvwprintw(status->window, 1, 1, "Time: %d s", elapsed_time); 
    mvwprintw(status->window, 2, 1, "Jan Matusiak");
    mvwprintw(status->window, 3, 1, "s203290");
    mvwprintw(status->window, 4, 1, "GDANSK TU");

    wrefresh(status->window);
}


void timeElapsed(GAME *game, FROG *frog, CARS *cars, STATUS *status){
    clear(); // clear the whole screen to display the message
    int height, width;
    getmaxyx(stdscr, height, width); // read the total height and width of the terminal window

    /* display the message in the middle of the screen in case time elapses */
    mvwprintw(stdscr, height/2 - 1, width/2 - 20, "TIME HAS ELAPSED!");
    mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY AGAIN, PRESS 's'");
    mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
    refresh(); 

    while(1){
        int c = getch();
        if(c != ERR){ // display the message until some input is entered
            if(c == 's'){ 
                clear();
                refresh();
                resetTheGame(game, frog, cars, status); // reset the game if the player presses 's'
                break;
            }
            else if(c == 'q'){
                break; // exit the loop if the player presses 'q' 
            }
            else{
                /* if the input is other than 's' or 'q', the message that asks for a valid input is displayed */
                mvwprintw(stdscr, height/2 + 2, width/2 - 20, "Invalid input, please press 's' or 'q'."); 
                refresh();
                usleep(100000); 
                clear(); // after 0.1 seconds, the whole message disappears and the initial message is displayed again
                // it gives the effect of the 4th line appearing for just a brief moment below the message that is always there
                mvwprintw(stdscr, height/2 - 1, width/2 - 20, "TIME HAS ELAPSED!");
                mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY AGAIN, PRESS 's'");
                mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
                refresh();
            }
        }
    }
}

void collision(GAME *game, FROG *frog, CARS *cars, STATUS *status){ // same working mechanism as timeElapsed function, hence no comments
    clear();
    int height, width;
    getmaxyx(stdscr, height, width);
    mvwprintw(stdscr, height/2 - 1, width/2 - 20, "YOU HIT THE CAR!");
    mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY AGAIN, PRESS 's'");
    mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
    refresh();

    while(1){
        int c = getch();
        if(c != ERR){
            if(c == 's'){
                clear();
                refresh();
                resetTheGame(game, frog, cars, status);
                break;
            }
            else if(c == 'q'){
                break;
            }
            else{
                mvwprintw(stdscr, height/2 + 2, width/2 - 20, "Invalid input, please press 's' or 'q'.");
                refresh();
                usleep(100000);
                clear();  
                mvwprintw(stdscr, height/2 - 1, width/2 - 20, "YOU HIT THE CAR!");
                mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY AGAIN, PRESS 's'");
                mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
                refresh();
            }
        }
    }
}

int checkForLoss(GAME *game, FROG *frog, CARS *cars, STATUS *status, time_t current_time, time_t last_input_time){
    /* checkCollision function returns 1 in case of a collision */
    if(checkCollision(game, frog, cars)){
        timeout(2000); // wait with reading input to prevent stacking 
        collision(game, frog, cars, status);
        return 1; // return 1 if the player lost
    }
    if(difftime(current_time, last_input_time) >= status->time_limit){
        timeout(2000);
        timeElapsed(game, frog, cars, status);
        return 1; 
    }
    return 0; // return 0 if the player didn't lose
}

void youWin(GAME *game, FROG *frog, CARS *cars, STATUS *status){ // same working mechanism as timeElapsed function, hence no comments
    clear();
    int height, width;
    getmaxyx(stdscr, height, width);
    mvwprintw(stdscr, height/2 - 1, width/2 - 20, "YOU WIN!");
    mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY AGAIN, PRESS 's'");
    mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
    refresh();
    
    while(1){
        int c = getch();
        if(c != ERR){
            if(c == 's'){
                clear();
                refresh();
                resetTheGame(game, frog, cars, status);
                break;
            }
            else if(c == 'q'){
                break;
            }
            else{
                mvwprintw(stdscr, height/2 + 2, width/2 - 20, "Invalid input, please press 's' or 'q'.");
                refresh();
                usleep(100000);
                clear();  
                mvwprintw(stdscr, height/2 - 1, width/2 - 20, "YOU WIN!");
                mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY AGAIN, PRESS 's'");
                mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
                refresh();
            }
        }
    }
}

int checkForWin(GAME *game, FROG *frog, CARS *cars, STATUS *status){
    if(frog->position_y <= GAME_Y_COORD + frog->size){ // check if the player has reached the uppermost safe zone
        timeout(2000);
        youWin(game, frog, cars, status);
        return 1; // return 1 if the player won
    }
    return 0; // return 0 if the player lost
}

void resetTheGame(GAME *game, FROG *frog, CARS *cars, STATUS *status){
    clear();
    /* setting the frog to its initial position */
    frog->position_x = GAME_X_COORD + (GAME_WIDTH - frog->size + 1)/2; 
    frog->position_y = GAME_HEIGHT + GAME_Y_COORD - frog->size;
    initGame(game, frog, cars, status); // reinitalize the game
}

void initObstacle(GAME *game){ 
    for(int i = 0; i < GAME_WIDTH; i++){
        for(int j = GAME_HEIGHT - 5*game->lane_height + 1; j < 6*game->lane_height; j++){ // set the obstacles only in the middle safe zone
            if((i > 21 && i < 58) || (i > 85 && i < 126) || (i > 161 && i < 200)){ // the obstacle is set in a specific place, the same for every game
                mvwprintw(game->window, j, i, "#");
            }
        }
    }
}

void initLanes(GAME *game, FROG *frog){
    init_pair(0, COLOR_BLACK, COLOR_BLACK); // lanes are always black
    init_pair(1, getColor(game->safe_color), getColor(game->safe_color)); // read the color for the safe zones
    /* loop going over the whole game window that initializes the lanes and colors */
    for(int i = 0; i < GAME_WIDTH; i++){
        for(int j = 0; j < GAME_HEIGHT; j++){
            if(j < game->lane_height || j >= GAME_HEIGHT - game->lane_height + 1 || (j < 6*game->lane_height && j >= GAME_HEIGHT - 5*game->lane_height + 1)){
                // set the color for the safe zones for the upper, lower and middle lane
                wattron(game->window, COLOR_PAIR(1)); 
                mvwprintw(game->window, j, i, " ");
                wattroff(game->window, COLOR_PAIR(1));
            }
            else if(j % game->lane_height == 0){ // initialize the borders between lanes
                mvwprintw(game->window, j, i, "-");
            }
            else{ //
                wattron(game->window, COLOR_PAIR(0)); 
                mvwprintw(game->window, j, i, " ");
                wattroff(game->window, COLOR_PAIR(0));
            }
        }
        initObstacle(game); // initialize the obstacles
    }
    wrefresh(game->window);
}

void initFrog(FROG *frog){
    init_pair(2, getColor(frog->frog_color), getColor(frog->frog_color));
    frog->window = newwin(frog->size, frog->size, frog->position_y, frog->position_x);
    wbkgd(frog->window, COLOR_PAIR(2));
    wrefresh(frog->window);  
}

void moveFrog(GAME *game, FROG *frog, int direction){
    int step_y = game->lane_height; // set such a vertical step that the frog can only move in between the borders of the lanes
    int step_x = frog->size; // horizontal step

        switch(direction){
            case KEY_UP: // check whether the player is below the upper boundary or is not jumping onto the obstacle
                if(frog->position_y > GAME_Y_COORD && (mvwinch(game->window, frog->position_y - 3*step_y, frog->position_x - step_x) != '#')){ 
                    frog->position_y-=step_y;
                } 
                break;
            case KEY_DOWN: // check whether the player is not at the lowest lane or is not jumping onto the obstacle
                if(frog->position_y < GAME_HEIGHT + frog->size && (mvwinch(game->window, frog->position_y - step_y, frog->position_x - step_x) != '#')){
                    frog->position_y+=step_y;
                }
                break;
            case KEY_LEFT: // check whether the player is not at the left border or is not jumping onto the obstacle
                if(frog->position_x > GAME_X_COORD + frog->size && (mvwinch(game->window, frog->position_y - 2*step_y, frog->position_x - 2*step_x) != '#')){
                        frog->position_x-=step_x; 
                }
                break;
            case KEY_RIGHT: // check whether the player is not at the right border or is not jumping onto the obstacle
                if(frog->position_x < GAME_WIDTH - frog->size && (mvwinch(game->window, frog->position_y - 2*step_y, frog->position_x) != '#')){
                    frog->position_x+=step_x;
                }
                break;
            }
    mvwin(frog->window, frog->position_y, frog->position_x); // update the frog's position
    wrefresh(frog->window); 
}

void initCars(GAME *game, CARS *cars){
    init_pair(3, getColor(cars->car_color), getColor(cars->car_color));
    /* loop that goes over all the lanes to create a car on each */
    for(int i = 0; i < NUMBER_OF_LANES; i++){
        if(i != 3){  // except for this lane, where the middle safe zone is
            cars->car[i] = malloc(sizeof(CAR)); // allocate memory for each car
            if(cars->car[i] == NULL){
                printf("Memory allocation failed\n");
                break;
            }
            cars->car[i]->pos_y = GAME_HEIGHT - i * game->lane_height + 1;
            cars->car[i]->og_pos_y = cars->car[i]->pos_y;
            cars->car[i]->direction = (i % 2 == 0) ? 1 : -1; // cars on even lanes will move in a different direction to those on odd lanes
            cars->car[i]->pos_x = (cars->car[i]->direction == 1) ? GAME_WIDTH - cars->car_length : GAME_X_COORD + 3; // starting position for each car - cars with direction 1 move from right to left
            cars->car[i]->speed = rand() % 3 + cars->max_speed - 2; // speed can be max_speed - 2, max_speed - 1 or max_speed
            cars->car[i]->og_speed = cars->car[i]->speed;
            cars->car[i]->delay = rand() % 4 + 1; // the cars will appear with a delay of at most 4 seconds
            cars->car[i]->is_moving = 0; // flag to track whether the car has begun its movement
            // create a window to represent each car
            cars->car[i]->window = newwin(cars->car_height, cars->car_length, cars->car[i]->pos_y, cars->car[i]->pos_x);
            wbkgd(cars->car[i]->window, COLOR_PAIR(3));
        }
    }
}

void wrapping(GAME *game, CARS *cars, int index){
/* when the car reaches the border, it reappears on another side (+ 3 is added for smoothness) */
    if(cars->car[index]->direction == 1 && cars->car[index]->pos_x <= GAME_X_COORD + 3){
        cars->car[index]->pos_x = GAME_WIDTH - cars->car_length;
    }
    if(cars->car[index]->direction == -1 && cars->car[index]->pos_x >= GAME_WIDTH - cars->car_length){
        cars->car[index]->pos_x = GAME_X_COORD + 3;
    }
}

void stopMovement(GAME *game, FROG *frog, CARS *cars){
    /* the cars on lanes 2 and 4 will stop if the frog is on its lane and is within the horizontal distance of 10 from the car */
    if(frog->position_y == cars->car[2]->pos_y && abs(cars->car[2]->pos_x - frog->position_x) <= 10){ 
        cars->car[2]->speed = 0;
    }
    else{
        if(cars->car[2]->speed == 0){
            cars->car[2]->speed = cars->car[2]->og_speed; // they resume their movement with the same speed as they had before stopping
        }
    }
    if(frog->position_y == cars->car[4]->pos_y && abs(cars->car[4]->pos_x - frog->position_x) <= 10){
        cars->car[4]->speed = 0;
    }
    else{
        if(cars->car[4]->speed == 0){
            cars->car[4]->speed = cars->car[4]->og_speed;
        }
    }
}

void moveCars(GAME *game, FROG *frog, CARS *cars, time_t start_time){
    init_pair(3, getColor(cars->car_color), getColor(cars->car_color));
    for(int i = 0; i < NUMBER_OF_LANES; i++){
        if(i != 3 && cars->car[i]->window != NULL){ // memory for index 3 was not allocated
        // we also check if the window is not empty, which happens when the car disappeared; we don't want to update its position then
            time_t current_time = time(NULL); // read the current time
            int elapsed_time = (int)difftime(current_time, start_time); // store the time since the beginning of the game 

            if(cars->car[i]->is_moving == 0 && elapsed_time >= cars->car[i]->delay){ // if the car is not yet moving and more time has passed since the beginning of the game than the set delay for a car, the car is set to moving
                cars->car[i]->is_moving = 1;
            }
            if(cars->car[i]->is_moving){ // movement begins only when the car has been set to moving 
                delwin(cars->car[i]->window); // delete the previous window of a car
                cars->car[i]->pos_x += (cars->car[i]->direction == 1 ? -cars->car[i]->speed : cars->car[i]->speed); // calculate the new position
                cars->car[i]->window = newwin(cars->car_height, cars->car_length, cars->car[i]->pos_y, cars->car[i]->pos_x); // create a new car window at a new position
                wbkgd(cars->car[i]->window, COLOR_PAIR(3));
                    
                wrapping(game, cars, i); 
                stopMovement(game, frog, cars);

                wrefresh(cars->car[i]->window);
            }
        }
    }
}

int checkCollision(GAME *game, FROG *frog, CARS *cars){
    // declare the boundary points of a frog window 
    int frog_left = frog->position_x;
    int frog_right = frog->position_x + frog->size - 1;
    int frog_top = frog->position_y;
    int frog_bottom = frog->position_y + frog->size - 1;

    // declare the boundary points of each car window
    for(int i = 0; i < NUMBER_OF_LANES; i++){
        if(i != 3){
            int car_left = cars->car[i]->pos_x;
            int car_right = car_left + cars->car_length - 1;
            int car_top = cars->car[i]->pos_y + 1; 
            int car_bottom = car_top + cars->car_height - 1;

            // if the positions overlap, the collision is detected
            if(frog_right >= car_left && frog_left <= car_right && frog_bottom >= car_top && frog_top <= car_bottom){ 
                return 1; // if collision is detected
            }
        }
    }
    return 0; // if no collision is detected
}

void randomCarIndexes(GAME *game, int *a, int *b, int *c, int *d){
    /* generate 4 different car indexes - two to increase speed, two to disappear */
    *a = rand() % NUMBER_OF_LANES;
    *b = rand() % NUMBER_OF_LANES;
    *c = rand() % NUMBER_OF_LANES;
    *d = rand() % NUMBER_OF_LANES;
    /* numbers are to be unique to ensure that unique cars disappear and have their speed increased, as well as cars which stop their movement are not chosen */
    while(*a == 4 || *a == 3 || *a == 2){
        *a = rand() % NUMBER_OF_LANES;
    }
    while(*b == *a || *b == 4 || *b == 3 || *b == 2){
        *b = rand() % NUMBER_OF_LANES;
    }
    while(*c == *a || *c == *b || *c == 4 || *c == 3 || *c == 2){
        *c = rand() % NUMBER_OF_LANES;
    }
    while(*d == *a || *d == *b || *d == *c || *d == 4 || *d == 3 || *d == 2){
        *d = rand() % NUMBER_OF_LANES;
    }
}
void modifyCars(GAME *game, CARS *cars, int elapsed_time, int *increased, int *disappeared, int *reappeared, time_t *disappear_time_c, time_t *disappear_time_d, int a, int b, int c, int d){ 
    increaseSpeed(game, cars, elapsed_time, increased, a, b);
    disappearCar(game, cars, elapsed_time, disappeared, reappeared, disappear_time_c, disappear_time_d, c, d);
}

void increaseSpeed(GAME *game, CARS *cars, int elapsed_time, int *increased, int a, int b){
    // if 5 seconds passed and the speed has not yet been increased, the speed of the first car increases 
    if(elapsed_time > 5 && *increased == 0){
        cars->car[a]->speed+=1;
        *increased = 1; // flag that the speed has increased once
    }
    // if 10 seconds elapsed and the speed has only been increased once, the speed of the second car increases 
    if(elapsed_time > 10 && *increased == 1){
        cars->car[b]->speed+=1;
        *increased = 2; // flag that the speed has increased twice
    }
}

void removeCar(CARS *cars, int index){
    delwin(cars->car[index]->window); // delete the car window 
    cars->car[index]->window = NULL; // set so that the position of this car is not updated in the moveCars function
}

void handleDisappearance(GAME *game, CARS *cars, int elapsed_time, int *disappeared, time_t *disappear_time_c, time_t *disappear_time_d, int c, int d){
    // if 5 seconds elapsed, the car is at one of the borders and no car has yet disappeared
    if(elapsed_time > 5 && (cars->car[c]->pos_x == GAME_X_COORD + 3 || cars->car[c]->pos_x == GAME_WIDTH - cars->car_length) && *disappeared == 0){
        removeCar(cars, c); // remove the car
        *disappeared = 1; // flag that one car has already disappeared       
        *disappear_time_c = time(NULL); // read the time at which the first car disappeared
    }
    // if 10 seconds elapsed, the car is at one of the borders and only one car has disappeared so far
    if(elapsed_time > 10 && (cars->car[d]->pos_x == GAME_X_COORD + 3 || cars->car[d]->pos_x == GAME_WIDTH - cars->car_length) && *disappeared == 1){
        removeCar(cars, d); 
        *disappeared = 2; // two cars have already disappeared
        *disappear_time_d = time(NULL); // read the time at which the second car disappeared
    }
}

void showCar(GAME *game, CARS *cars, int new_pos_x, int index){
    cars->car[index]->window = newwin(cars->car_height, cars->car_length, cars->car[index]->og_pos_y, new_pos_x); // recreating a car at a new position
    wbkgd(cars->car[index]->window, COLOR_PAIR(3));
    // restore the parameters of the car
    cars->car[index]->pos_x = new_pos_x; 
    cars->car[index]->pos_y = cars->car[index]->og_pos_y;
    cars->car[index]->direction = (index % 2 == 0) ? 1 : -1;
    cars->car[index]->speed = cars->car[index]->og_speed;
    cars->car[index]->is_moving = 1; // so that moveCars function resumes updating car's position
}

void handleReappearance(GAME *game, CARS *cars, int *disappeared, int *reappeared, time_t *disappear_time_c, time_t *disappear_time_d, int c, int d, int new_pos_xc, int new_pos_xd){
    /* if only one car has disappeared so far, no car has reappeared yet and 4 seconds have passed since the first car has disappeared */
    if(*disappeared == 1 && *reappeared == 0 && difftime(time(NULL), *disappear_time_c) >= 4){  
        showCar(game, cars, new_pos_xc, c);
        *reappeared = 1; // flag that one car has already reappeared
        wrefresh(cars->car[c]->window);
    }
    /* if two cars have disappeared so far, one car has already reappeared and 4 seconds have passed since the second car has disappeared */
    if(*disappeared == 2 && *reappeared == 1 && difftime(time(NULL), *disappear_time_d) >= 4){ 
        showCar(game, cars, new_pos_xd, d);
        *reappeared = 2; // two cars have already disappeared
        wrefresh(cars->car[d]->window);
    }
}

void disappearCar(GAME *game, CARS *cars, int elapsed_time, int *disappeared, int *reappeared, time_t *disappear_time_c, time_t *disappear_time_d, int c, int d){
    /* the cars will reappear at a random positions within their lanes */
    int new_pos_xc = GAME_X_COORD + 3 + rand() % (GAME_WIDTH - cars->car_length - 3); //+3 and -3 added for smoothness
    int new_pos_xd = GAME_X_COORD + 3 + rand() % (GAME_WIDTH - cars->car_length - 3);

    handleDisappearance(game, cars, elapsed_time, disappeared, disappear_time_c, disappear_time_d, c, d);
    handleReappearance(game, cars, disappeared, reappeared, disappear_time_c, disappear_time_d, c, d, new_pos_xc, new_pos_xd);
    wrefresh(game->window);
}

void setUp(GAME *game, FROG *frog, CARS *cars, time_t start_time){
    initLanes(game, frog); 
    initFrog(frog);
    moveCars(game, frog, cars, start_time);
    wrefresh(game->window);
}

void initGame(GAME *game, FROG *frog, CARS *cars, STATUS *status){
    initCars(game, cars);
    int a, b, c, d;
    randomCarIndexes(game, &a, &b, &c, &d);
    keypad(game->window, true); // allow for player's input
    nodelay(game->window, true); // allow for the movement of the cars and timer independent of the user's input

    time_t start_time = time(NULL); // read the starting time (so when the board is initialized)
    time_t last_input_time = start_time; // set starting time as the time of the player's last input
    initStatus(start_time, status);
    int increased = 0, disappeared = 0, reappeared = 0; // variables that monitor how many times a speed of the car has increased so far, how many times the cars have disappeared, or reappeared (initalizing at 0)

    time_t disappear_time_c = 0; // store the time when the first car has disappeared
    time_t disappear_time_d = 0; // when the second car has disappeared
    
    while(1){  
        setUp(game, frog, cars, start_time);
        int e = wgetch(game->window); // read player's input
        time_t current_time = time(NULL); // read the current time
        int elapsed_time = (int)difftime(current_time, start_time); // read how much time elapsed since the beginning of the game
        modifyCars(game, cars, elapsed_time, &increased, &disappeared, &reappeared, &disappear_time_c, &disappear_time_d, a, b, c, d);
        if(checkForLoss(game, frog, cars, status, current_time, last_input_time)){ 
            break; // exit the loop if the player lost
        }
        if(e != ERR){  
            last_input_time = current_time; // update last input time to current time whenever player enters some input
            if(e == 'q'){ // 'q' leaves the game
                break;
            } 
            else if(e == KEY_UP || e == KEY_DOWN || e == KEY_LEFT || e == KEY_RIGHT){ // read the arrows and move the frog accordingly
                moveFrog(game, frog, e);
                if(checkForWin(game, frog, cars, status)){ 
                    break; // exit the loop if the player won
                }
            }
        }
        initStatus(start_time, status); // update status
        usleep(10000); // delay the loop to control the speed game
    }
    wclear(game->window);
    wrefresh(game->window);
}

void start(GAME *game, FROG *frog, CARS *cars, STATUS *status){

    game->window = newwin(GAME_HEIGHT, GAME_WIDTH, GAME_Y_COORD, GAME_X_COORD);  // create the window where the actual game will take place
    /* display the initial game menu; it works the same way as the TimeElapsed function, hence no comments */
    int height, width;
    getmaxyx(stdscr, height, width);
    mvwprintw(stdscr, height/2 - 1, width/2 - 20, "WELCOME TO THE FROGGER!");
    mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY THE GAME, PRESS 's'");
    mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
    refresh();
    
    while(1){
        int c = getch();
        if(c != ERR){
            if(c == 's'){
                clear();
                refresh();
                initGame(game, frog, cars, status);
                break;
            }
            else if(c == 'q'){
                break;
            }
            else
            {
                mvwprintw(stdscr, height/2 + 2, width/2 - 20, "Invalid input, please press 's' or 'q'.");
                refresh();
                sleep(1);
                clear();  
                mvwprintw(stdscr, height/2 - 1, width/2 - 20, "WELCOME TO THE FROGGER!");
                mvwprintw(stdscr, height/2, width/2 - 20, "IF YOU WANT TO PLAY THE GAME, PRESS 's'");
                mvwprintw(stdscr, height/2 + 1, width/2 - 20, "IF YOU WANT TO EXIT THE GAME, PRESS 'q'");
                refresh();
            }
        }
    }
}

int main(int argc, char **argv){
    initscr();
    cbreak(); // input processed immediately
    noecho(); // prevent input from being displayed on the screen
    curs_set(0); // hide the cursor

    start_color(); // initialize color functionalities
    srand(time(NULL)); // seed the random number generator with the current time

    GAME *game = malloc(sizeof(GAME)); // allocate memory for the GAME struct
    FROG *frog = malloc(sizeof(FROG)); // allocate memory for the FROG struct
    CARS *cars = malloc(sizeof(CARS)); // allocate memory for the CARS struct
    cars->car = malloc(sizeof(CAR*) * NUMBER_OF_LANES); // allocate memory for an array of pointers to individual cars
    STATUS *status = malloc(sizeof(STATUS)); // allocate memory for the STATUS struct
    loadConfigurations(game, frog, cars, status);
    initValues(game, frog, cars);

    if(game == NULL || frog == NULL || cars == NULL || cars->car == NULL || status == NULL){ // ensure the memory was allocated correctly
        printf("Memory allocation failed\n");
        return 1;
    }

    start(game, frog, cars, status); // start the game (display the menu)

    freeMemory(game, cars, frog, status); // free the memory
    endwin(); // terminal cleanup
    return 0;
}
#include "stdio.h"
#include "stdlib.h"
#include "sdl.h"
#include "SDL2_gfxPrimitives.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;
int A(int argc, char ** argv){

    int quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = SDL_LoadBMP("01.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dstrect = { 5, 5, 320, 240 };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    while (quit == 0)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_BUTTON_LEFT:
            printf("QQQQQQQQQQQQQQQQQQQQQQQQ");
            quit = 1;
            break;
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("AAAAAAAAAAAAAAAAAAAAa");
    return 0;
}


int main(int argc, char** argv) {
    //A(argc,argv);

    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor, front_right_sensor = 0;
    int left_sensor = 0;
    clock_t start_time, end_time;
    int msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
// maze construction
 //main.c

 //BORDER
    // maze construction
//Original Maze

// below paste in main.c
// maze construction
	//main.c

 //main.c

 //BORDER
    // maze construction
// main.c

  //Maze 1  robot.c

 //  Maze 1  main.c
//Setting up the maze structure with for loops for diagonal walls...
 //main.c

  /* Outside border */
    // main.c

 //entrance
// Borders
 insertAndSetFirstWall(&head, 2,  640-10-220, 400, 10, 80);
    insertAndSetFirstWall(&head, 2,  640-200-20, 400, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-20, 50, 10, 350);
    insertAndSetFirstWall(&head, 2,  640-280-20, 50, 280, 10);
    insertAndSetFirstWall(&head, 2,  640-10-300, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-110-300, 150, 110, 10);
    insertAndSetFirstWall(&head, 2,  640-10-400, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-400-220, 50, 220, 10);
    insertAndSetFirstWall(&head, 2,  640-10-620, 50, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-620-20, 340, 20, 10);


    insertAndSetFirstWall(&head, 1,  640-10-320, 300, 10, 180);
    insertAndSetFirstWall(&head, 2,  640-200-120, 300, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-120, 150, 10, 150);
    insertAndSetFirstWall(&head, 2,  640-80-120, 150, 80, 10);
    insertAndSetFirstWall(&head, 2,  640-10-200, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-310-200, 250, 310, 10);
    insertAndSetFirstWall(&head, 2,  640-10-500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-20-500, 150, 20, 10);
    insertAndSetFirstWall(&head, 2,  640-10-520, 150, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-120-520, 440, 120, 10);
    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;

    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, left_sensor);
        robotMotorMove(&robot);

        //Check if robot reaches endpoint. and check sensor values
        if (checkRobotReachedEnd(&robot, 0, 340, 10, 100)){
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }
        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {
            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            if (front_left_sensor>0)
                printf("Getting close on the right. Score = %d\n", front_left_sensor);

            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            if (front_right_sensor>0)
                printf("Getting close on the front. Score = %d\n", front_right_sensor);

            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);

            if (left_sensor>0)
                printf("Getting close on the left. Score = %d\n", left_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}

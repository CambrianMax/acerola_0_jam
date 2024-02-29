

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#ifdef __EMSCRIPTEN__
#include <SDL2/SDL_opengles2.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengl.h>
#include <emscripten.h>
#else
#include <GL/glew.h>
#endif 
#include <SDL2/SDL_opengl.h>


#define STB_TRUETYPE_IMPLEMENTATION
#include "3rd_party/stb_truetype.h"
#include "3rd_party/json.h"

#include "prodefs.h"  //imports the type names i like to use
#include "util.h"  //simple utility functions
#include "m_math.h"  // some math functions and structs
#include "input.h"  //has a controller struct for input handling

//global vars for platform setup
SDL_Window *window;
u32 current_time = 0;
u32 last_time_updated = 0;
GameInput input[2] = {0};
GameInput *new_input;
GameInput *old_input;
GameControllerInput* new_controller;
GameControllerInput* old_controller;
u32 loop_time = 0;


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



#include "assets.h"
#include "sprites.h"
#include "entity.h"
#include "render.h"
#include "game.h"

#include "render.c"
#include "sprites.c"
#include "entity.c"
#include "entity_sim.c"
#include "game.c"

void
desktop_loop()
{
    
    SDL_Event event;
    int quit = 0;
    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = 1;
        }
        
        //get input
        *new_input = (GameInput){0};
        
        new_controller = &new_input->controller;
        old_controller = &old_input->controller;
        
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        
        process_key_press(&new_controller->move_left, &old_controller->move_left, currentKeyStates[SDL_SCANCODE_LEFT]);
        process_key_press(&new_controller->move_right, &old_controller->move_right, currentKeyStates[SDL_SCANCODE_RIGHT]);
        process_key_press(&new_controller->move_up, &old_controller->move_up, currentKeyStates[SDL_SCANCODE_UP]);
        process_key_press(&new_controller->move_down, &old_controller->move_down, currentKeyStates[SDL_SCANCODE_DOWN]);
        process_key_press(&new_controller->action_right, &old_controller->action_right, currentKeyStates[SDL_SCANCODE_C]);
        process_key_press(&new_controller->start, &old_controller->start, currentKeyStates[SDL_SCANCODE_Z]);
        
        
        current_time = SDL_GetTicks();
        new_input->elapsed_seconds = ((f32)current_time - (f32)last_time_updated)/1000.0f;
        
        //printf("curr: %d last: %d elsaped: %f \n",current_time, last_time_updated, new_input->elapsed_seconds);
        //update game
        game_update(new_input);
        
        SDL_GL_SwapWindow(window);
        
        GameInput *temp = new_input;
        new_input = old_input;
        old_input = temp;
        
        
        
        //take a nap game
        last_time_updated = current_time;
        local_persist i32 sleep_time;
        loop_time = SDL_GetTicks() - last_time_updated;
        sleep_time = (1000 / 60) -(loop_time); 
        if(sleep_time > 0)
        {
            
            //printf("loop_time %d, sleep_time: %d\n",loop_time, sleep_time);
            SDL_Delay(sleep_time);
        }
    }
}

void
emscripten_loop()
{
    //get input
    *new_input = (GameInput){0};
    
    new_controller = &new_input->controller;
    old_controller = &old_input->controller;
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    process_key_press(&new_controller->move_left, &old_controller->move_left, currentKeyStates[SDL_SCANCODE_LEFT]);
    process_key_press(&new_controller->move_right, &old_controller->move_right, currentKeyStates[SDL_SCANCODE_RIGHT]);
    process_key_press(&new_controller->move_up, &old_controller->move_up, currentKeyStates[SDL_SCANCODE_UP]);
    process_key_press(&new_controller->move_down, &old_controller->move_down, currentKeyStates[SDL_SCANCODE_DOWN]);
    process_key_press(&new_controller->action_right, &old_controller->action_right, currentKeyStates[SDL_SCANCODE_C]);
    process_key_press(&new_controller->start, &old_controller->start, currentKeyStates[SDL_SCANCODE_Z]);
    
    
    current_time = SDL_GetTicks();
    new_input->elapsed_seconds = ((f32)current_time - (f32)last_time_updated)/1000.0f;
    
    //printf("curr: %d last: %d elsaped: %f \n",current_time, last_time_updated, new_input->elapsed_seconds);
    //update game
    game_update(new_input);
    
    SDL_GL_SwapWindow(window);
    
    GameInput *temp = new_input;
    new_input = old_input;
    old_input = temp;
    
    
    
    //take a nap game
    last_time_updated = current_time;
    local_persist i32 sleep_time;
    loop_time = SDL_GetTicks() - last_time_updated;
    sleep_time = (1000 / 60) -(loop_time); 
    if(sleep_time > 0)
    {
        
        //printf("loop_time %d, sleep_time: %d\n",loop_time, sleep_time);
        SDL_Delay(sleep_time);
    }
    
}



int main() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    Mix_Init(MIX_INIT_OGG);
    
    //4096 seems to work best for the web for some reason
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }
    
    //Create SDL window
    window = SDL_CreateWindow("Acerola_0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* icon = IMG_Load("assets/mini_hog.ico");
    SDL_SetWindowIcon(window, icon);
    
#ifdef __EMSCRIPTEN__
    // Create OpenGL ES context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else 
    // create normie opengl 3.3 context lol
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#endif
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
        
    }
    
    
#ifdef __EMSCRIPTEN__
#else
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(glewError));
        
    }
#endif
    
    
    init_gl();
    
    
    
    
    new_input = &input[0];
    old_input = &input[1];
    new_controller = &new_input->controller;
    old_controller = &old_input->controller;
    
    
    current_time = SDL_GetTicks();
    last_time_updated = SDL_GetTicks();
    
    
    //init game
    game_init();
    
    // Run main loop
#ifdef __EMSCRIPTEN__
    //emscripten loop
    emscripten_set_main_loop(emscripten_loop, 0, 1);
#else
    //normie desktop loop
    desktop_loop();
#endif
    
    game_cleanup();
    // Clean up
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    
    SDL_GL_DeleteContext(glContext);
    
    SDL_DestroyWindow(window);
    SDL_FreeSurface(icon);
    
    SDL_Quit();
    
    return 0;
}

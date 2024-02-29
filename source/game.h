/* date = February 29th 2024 0:13 am */

#ifndef GAME_H
#define GAME_H


#define NUM_ENTITIES 500

typedef struct
{
    Entity entities[500];
    
    u32 num_entities;
    r32 total_time;
}GameState;

GameState gs = {0};
GameInput* gi = NULL;

#endif //GAME_H

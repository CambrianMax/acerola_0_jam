/* date = February 29th 2024 0:13 am */

#ifndef GAME_H
#define GAME_H


#define MAX_ENTITIES 500
#define SORT_BUFFER_SIZE 3000
#define TOTAL_TILES 3000

typedef struct
{
    Entity entities[MAX_ENTITIES];
    Entity* player;
    i32 num_entities;
    
    SortPair sort_buffer[SORT_BUFFER_SIZE];
    i32 num_sort_pairs;
    
    f32 z_location;
    
    f32 paralax_zoom;
    
    
    r32 total_time;
    
    u32 tiles [TOTAL_TILES];
    i32 level_dim_x;
    i32 level_dim_y;
    i32 tile_count;
    f32 level_z;
    
    f32 scale;
    f32 hscale;
    //stuff to free
    
    
}GameState;

GameState gs = {0};
GameInput* gi = NULL;

#endif //GAME_H

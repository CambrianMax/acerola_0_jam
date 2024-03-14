/* date = February 29th 2024 0:13 am */

#ifndef GAME_H
#define GAME_H


#define MAX_ENTITIES 600
#define SORT_BUFFER_SIZE 3000
#define TOTAL_TILES 3000

typedef struct
{
    Entity entities[MAX_ENTITIES];
    Entity* player;
    Entity* witch;
    i32 num_entities;
    
    SortPair sort_buffer[SORT_BUFFER_SIZE];
    i32 num_sort_pairs;
    
    r32 total_time;
    
    u32 tiles [TOTAL_TILES];
    u32 top_tiles [TOTAL_TILES];
    i32 level_dim_x;
    i32 level_dim_y;
    i32 tile_count;
    
    b32 devil_dead;
    b32 platform_mode;
    
    i32 pause_entities;
    i32 pause_collision;
    
    
    i32 tele_x;
    i32 tele_y;
    RoomId tele_room;
    
    b32 transition;
    b32 faded;
    f32 black_alpha;
    
    i32 music_id;
    i32 requested_music;
    i32 music_faded;
    f32 music_fade_timer;
    b32 music_active;
    b32 playing_music;
    
    i32 dialouge_id;
    f32 dialouge_alpha;
    f32 dia_info_alpha;
    i32 dialouge_end;
    b32 dialouge_active;
    b32 fade_dialouge;
    //stuff to free
    
    b32 witch_active;
    b32 reached_home;
    b32 bink_dead;
    
}GameState;

GameState gs = {0};
GameInput* gi = NULL;

void setup_intro();
void abrupt_music_change(i32);
void stop_music();

#endif //GAME_H

/* date = February 29th 2024 0:29 am */

#ifndef SPRITES_H
#define SPRITES_H



typedef struct
{
    u32 image_id;
    i32 offset_x,offset_y;
    i32 width, height;
    u32 frame_count;
    u32 fps;
}Sprite;

typedef enum
{
    TEST_SPR,
    GRASS_TILE_SPR,
    PLAYER_IDLE_SPR,
    PLAYER_WALK_SPR,
    PARALAX_TEST_SPR,
    TOTAL_SPRITES,
}SpriteId;

const Sprite sprites[TOTAL_SPRITES] = 
{
    [TEST_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 0,
    },
    
    [GRASS_TILE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 32,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 5,
    },
    
    [PLAYER_IDLE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 32,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 5,
    },
    
    [PLAYER_WALK_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 32,
        .width = 32, 
        .height = 32,
        .frame_count = 5,
        .fps = 24,
    },
    
    [PARALAX_TEST_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 64,
        .width = 200, 
        .height = 125,
        .frame_count = 0,
        .fps = 24,
    },
    
};

const Sprite*
get_sprite(SpriteId);




void update_sprites();


#endif //SPRITES_H

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
    TOTAL_SPRITES,
}SpriteId;

const Sprite sprites[TOTAL_SPRITES] = 
{
    [TEST_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 0,
        .width = 500,
        .height = 530,
        .frame_count = 0,
        .fps = 0,
    },
    
};

const Sprite*
get_sprite(SpriteId);




void update_sprites();


#endif //SPRITES_H

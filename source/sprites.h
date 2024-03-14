/* date = February 29th 2024 0:29 am */

#ifndef SPRITES_H
#define SPRITES_H


#define TILE_SIZE 32


#define SPRITES \
X(TEST_SPR) \
X(GRASS_TILE_SPR) \
X(PLAYER_FI_SPR) \
X(PLAYER_RI_SPR) \
X(PLAYER_BI_SPR) \
X(PLAYER_LI_SPR) \
X(PLAYER_FW_SPR) \
X(PLAYER_RW_SPR) \
X(PLAYER_BW_SPR) \
X(PLAYER_LW_SPR) \
X(PLAYER_PRI_SPR) \
X(PLAYER_PLI_SPR) \
X(PLAYER_PRW_SPR) \
X(PLAYER_PLW_SPR) \
X(PLAYER_PRJ_SPR) \
X(PLAYER_PLJ_SPR) \
X(BINK_BLAST_SPR) \
X(BINK_BLAST_FINISH_SPR) \
X(WIFE_SPR) \
X(SON_SPR) \
X(JOURNAL_SPR) \
X(SIGN_SPR) \
X(SHRUB_SPR) \
X(TREE_SPR) \
X(ROCK_SPR) \
X(ROCK_FADE_SPR) \
X(PARTICLE_SPR) \
X(BLACK_SPR) \
X(WITCH_BLOCK_SPR) \
X(WITCH_BLOCK_2_SPR) \
X(WITCH_CASTER_D_SPR)\
X(WITCH_CASTER_L_SPR)\
X(WITCH_CASTER_R_SPR)\
X(WITCH_CASTER_U_SPR)\
X(DAVE_SPR)\
X(DINK_SPR)\
X(JANE_SPR)\
X(BILLY_SPR)\
X(SHELLY_SPR)\
X(WITCH_I_SPR) \
X(WITCH_P_SPR) \
X(WITCH_T_SPR) \
X(WITCH_DIES_SPR) \
X(W_BULLET_SPR) \
X(DEVIL_TREE_SPR) \
X(DEVIL_DIES_SPR) \
X(TITLE_SPR) \
X(TITLE_BG_SPR) \


typedef struct
{
    u32 image_id;
    i32 offset_x,offset_y;
    i32 width, height;
    u32 frame_count;
    u32 fps;
    b32 col;
    f32 w,h, y_offset;
}Sprite;



#define X(name) name,
typedef enum
{
    SPRITES
        TOTAL_SPRITES,
}SpriteId;
#undef X




#define X(name) [name] = STRINGIFY(name),
char* sprite_str [] = 
{
    SPRITES
};
#undef X


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
    
    
    [PLAYER_FI_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 2,
    },
    
    [PLAYER_RI_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 2,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 2,
    },
    
    [PLAYER_BI_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 4,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 2,
    },
    
    
    [PLAYER_LI_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 6,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 2,
    },
    
    
    [PLAYER_FW_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 8,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 4,
        .fps = 20,
    },
    
    [PLAYER_RW_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 12,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 4,
        .fps = 20,
    },
    
    
    [PLAYER_BW_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 16,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 4,
        .fps = 20,
    },
    
    [PLAYER_LW_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 20,
        .offset_y = 0,
        .width = 32, 
        .height = 32,
        .frame_count = 4,
        .fps = 20,
    },
    
    [PLAYER_PRI_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 0,
        .offset_y = TILE_SIZE,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 2,
    },
    
    [PLAYER_PLI_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 2,
        .offset_y = TILE_SIZE,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 2,
    },
    
    
    [PLAYER_PRW_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 4,
        .offset_y = TILE_SIZE,
        .width = 32, 
        .height = 32,
        .frame_count = 5,
        .fps = 20,
    },
    
    [PLAYER_PLW_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 9,
        .offset_y = TILE_SIZE,
        .width = 32, 
        .height = 32,
        .frame_count = 5,
        .fps = 20,
    },
    
    [PLAYER_PRJ_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 14,
        .offset_y = TILE_SIZE,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 20,
    },
    
    [PLAYER_PLJ_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 15,
        .offset_y = TILE_SIZE,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 20,
    },
    
    
    [BINK_BLAST_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = TILE_SIZE*2,
        .width = 32, 
        .height = 32,
        .frame_count = 20,
        .fps = 24,
    },
    
    
    [BINK_BLAST_FINISH_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE*22,
        .offset_y = TILE_SIZE*2,
        .width = 32, 
        .height = 32,
        .frame_count = 9,
        .fps = 24,
    },
    
    
    [WIFE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 1,
    },
    
    [SON_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 2,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 2,
    },
    
    [JOURNAL_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 4,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
    },
    
    
    [SIGN_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 5,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
    },
    
    [ROCK_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 6,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .w = 14,
        .h = 14,
    },
    /*
    [ROCK_FADE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 7,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 13,
        .fps = 2,
        .w = 14,
        .h = 14,
    },
    */
    
    [PARTICLE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 7,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .w = 10,
        .h = 10,
    },
    
    
    [BLACK_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 8,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .w = 10,
        .h = 10,
    },
    
    [WITCH_BLOCK_2_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 9,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 10,
        .y_offset = 10,
    },
    
    
    [WITCH_BLOCK_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 9,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 10,
        .y_offset = 10,
    },
    
    
    
    [WITCH_CASTER_D_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 10,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 10,
        .y_offset = 10,
    },
    
    [WITCH_CASTER_L_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 11,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 10,
        .y_offset = 10,
    },
    
    [WITCH_CASTER_R_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 12,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 10,
        .y_offset = 10,
    },
    
    [WITCH_CASTER_U_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 13,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 10,
        .y_offset = 10,
    },
    
    
    [DAVE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 14,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 1,
        .col = true,
        .w = 8,
        .h = 8,
        .y_offset = 10,
    },
    
    
    [DINK_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 16,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 1,
        .col = true,
        .w = 8,
        .h = 8,
        .y_offset = 10,
    },
    
    [JANE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 18,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 1,
        .col = true,
        .w = 8,
        .h = 8,
        .y_offset = 10,
    },
    
    
    [BILLY_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 20,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 1,
        .col = true,
        .w = 8,
        .h = 8,
        .y_offset = 10,
    },
    
    
    [SHELLY_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = TILE_SIZE * 22,
        .offset_y = TILE_SIZE * 3,
        .width = 32, 
        .height = 32,
        .frame_count = 2,
        .fps = 1,
        .col = true,
        .w = 8,
        .h = 8,
        .y_offset = 10,
    },
    
    
    
    
    
    
    [SHRUB_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = TILE_SIZE * 4,
        .width = 70, 
        .height = 64,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 30,
        .h = 14,
        .y_offset = 23,
    },
    
    [TREE_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = TILE_SIZE * 6,
        .width = 128, 
        .height = 128,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 8,
        .h = 50,
        .y_offset = 50,
    },
    
    [WITCH_I_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 322,
        .width = 55, 
        .height = 102,
        .frame_count = 1,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 30,
        //.y_offset = 50,
    },
    
    
    [WITCH_DIES_SPR] = 
    {
        .image_id = FNASTY_IMG,
        .offset_x = 0,
        .offset_y = 708,
        .width = 128, 
        .height = 128,
        .frame_count = 20,
        .fps = 20,
        .col = true,
        .w = 10,
        .h = 30,
    },
    
    
    [WITCH_P_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 55,
        .offset_y = 322,
        .width = 55, 
        .height = 102,
        .frame_count = 1,
        .fps = 1,
        .col = true,
    },
    
    
    [WITCH_T_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 445,
        .width = 128, 
        .height = 115,
        .frame_count = 6,
        .fps = 40,
        .col = true,
        //.w = 8,
        //.h = 50,
        //.y_offset = 50,
    },
    
    
    [W_BULLET_SPR] = 
    {
        .image_id = TEST_IMG,
        .offset_x = 0,
        .offset_y = 557,
        .width = 32, 
        .height = 32,
        .frame_count = 20,
        .fps = 24,
        .col = true,
        .w = 5,
        .h = 5,
    },
    
    [DEVIL_TREE_SPR] = 
    {
        .image_id = FNASTY_IMG,
        .offset_x = 0,
        .offset_y = 576,
        .width = 68, 
        .height = 118,
        .frame_count = 0,
        .fps = 1,
        .col = true,
        .w = 10,
        .h = 50,
    },
    
    [DEVIL_DIES_SPR] = 
    {
        .image_id = FNASTY_IMG,
        .offset_x = 69,
        .offset_y = 576,
        .width = 90, 
        .height = 128,
        .frame_count = 10,
        .fps = 10,
        .col = true,
        .w = 10,
        .h = 50,
    },
    
    
    [TITLE_SPR] = 
    {
        .image_id = TITLE_IMG,
        .offset_x = 0,
        .offset_y = 0,
        .width = 150, 
        .height = 150,
        .frame_count = 30,
        .fps = 22,
    },
    
    [TITLE_BG_SPR] = 
    {
        .image_id = FNASTY_IMG,
        .offset_x = 0,
        .offset_y = 0,
        .width = 768, 
        .height = 576,
        .frame_count = 1,
        .fps = 0,
    },
};

const Sprite*
get_sprite(SpriteId);

void update_sprites();





SpriteId str_to_sprite_id(char* str)
{
    for(i32 i = 0; i < TOTAL_SPRITES; i++)
    {
        if(!strcmp(sprite_str[i], str))
            return i;
    }
    return -1;
}

#endif //SPRITES_H

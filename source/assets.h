/* date = February 29th 2024 0:19 am */

#ifndef ASSETS_H
#define ASSETS_H


#define START_GLYPH ' '
#define END_GLYPH '~'

#define TOTAL_GLYPHS (END_GLYPH - START_GLYPH + 1)



#define FONT_ATLAS_WIDTH 1024
#define FONT_ATLAS_HIEGHT 1024
//#define FONT_SIZE 100
#define FONT_SIZE 25

#define BITMAP_BYTES_PER_PIXEL 4


typedef struct
{
    i32 minx, maxx, miny, maxy, advance;
    u32 x, y;
    u32 width, height;
}GlyphInfo;

typedef struct
{
    i32  ascent, descent, line_gap, line_advance;
    r32 scale;
    char* filename;
    stbtt_bakedchar* char_data;
    r32* kern_data;
    i32 width;
    i32 height;
    b32 loaded;
    u32 gpu_info;
}FontAsset;


typedef struct
{
    char* filename;
    b32 loaded;
    u32 gpu_info;
    i32 width;
    i32 height;
}ImageAsset;


typedef enum
{
    IMG_ASSET,
    FONT_ASSET,
    SND_ASSET,
    LEVEL_ASSET,
    TOTAL_ASSETS
}AssetType;


typedef enum
{
    SPRITE_IMAGE,
    FONT_IMAGE,
    TILE_IMAGE,
    TOTAL_IMAGE_TYPES
}ImageType;


typedef struct
{
    char* filename;
    b32 loaded;
    Mix_Music* mus;
    
}MusicAsset;


typedef struct
{
    char* filename;
    b32 loaded;
    Mix_Chunk* sfx;
    
}SfxAsset;

#define FONT_ASSETS \
X(TEST_FNT, "assets/VT323-Regular.ttf") \


#define IMAGE_ASSETS \
X(TEST_IMG, "assets/sprite_sheet.png") \
X(TITLE_IMG, "assets/title.png") \
X(FNASTY_IMG, "assets/fnasty.png") \


#define MUSIC_ASSETS \
X(INVALID_MUS, "assets/bink_home.ogg") \
X(INTRO_MUS, "assets/intro.ogg") \
X(BINKS_HOUSE_MUS, "assets/bink_home.ogg") \
X(QUEST_MUS, "assets/quest.ogg") \
X(CAVE_MUS, "assets/cave_sounds.ogg") \
X(WITCH_MUS, "assets/witches_rage.ogg") \


#define SFX_ASSETS \
X(BB_SFX, "assets/bblast.ogg") \
X(BBF_SFX, "assets/bbfinish.ogg") \
X(BINK_JUMP_SFX, "assets/jmp.ogg") \
X(DIA_SFX, "assets/dia_start.ogg") \
X(CRUMBLE_SFX, "assets/rock.ogg") \
X(TELE_SFX, "assets/tel.ogg") \
X(TREE_DEATH_SFX, "assets/tree_death.ogg") \
X(BINK_DEATH_SFX, "assets/p_death.ogg") \
X(WITCH_LAUGH_SFX, "assets/w_laugh.ogg") \







#define X(name, path) name,
typedef enum
{
    IMAGE_ASSETS
        TOTAL_IMAGE_ASSETS,
}ImageId;

typedef enum
{
    FONT_ASSETS
        TOTAL_FONT_ASSETS,
}FontId;


typedef enum
{
    MUSIC_ASSETS
        TOTAL_MUSIC_ASSETS,
}MusicId;


typedef enum
{
    SFX_ASSETS
        TOTAL_SFX_ASSETS,
}SfxId;

#undef X


#define X(name, path) [name] = {.filename = path,},
ImageAsset image_assets [TOTAL_IMAGE_ASSETS] = 
{
    IMAGE_ASSETS
};

FontAsset font_assets [TOTAL_FONT_ASSETS] = 
{
    FONT_ASSETS
};


MusicAsset music_assets [TOTAL_MUSIC_ASSETS] = 
{
    MUSIC_ASSETS
};


SfxAsset sfx_assets [TOTAL_SFX_ASSETS] = 
{
    SFX_ASSETS
};

#undef X

ImageAsset* get_image_asset(ImageId id)
{
    return &image_assets[id];
}


FontAsset* get_font_asset(FontId id)
{
    return &font_assets[id];
}

void
set_image_dim(ImageType type, u32 asset_id, i32* width, i32* height)
{
    switch(type)
    {
        case FONT_IMAGE:
        {
            *width = font_assets[asset_id].width;
            *height = font_assets[asset_id].height;
        }break;
        
        case SPRITE_IMAGE:
        case TILE_IMAGE:
        default:
        {
            *width = image_assets[asset_id].width;
            *height = image_assets[asset_id].height;
        }break;
    }
}


void play_music(i32 id);
void free_music(i32 id);



#endif //ASSETS_H

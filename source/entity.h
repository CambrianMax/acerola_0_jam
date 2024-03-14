/* date = February 29th 2024 0:27 am */

#ifndef ENTITY_H
#define ENTITY_H


#define LIST_OF_ENT_SUBTYPES \
X(STANDARD_TYPE) \
X(TELE_BOX) \
X(DEATH_RESPAWNER) \
X(LONG_TEXTY) \
X(INIT_SCREEN) \
X(WITCH_START) \
X(EVIL_WITCH) \
X(WITCH_CASTER) \
X(DIA_HELPER) \



#define LIST_OF_ENTITY_TYPES \
X(INVALID_ENT) \
X(PLAYER_ENT) \
X(DECOR_ENT) \
X(TEMP_ENT) \
X(MISC_ENT) \
X(PARTICLE_ENT) \
X(COLLECTABLE_ENT) \
X(S_COLLISION_ENT) \
X(DESTRUCTIBLE_ENT) \
X(BAD_BULLET_ENT) \
X(DIALOUGE_ENT) \
X(TEXTY_ENT) \
X(BINK_BLAST_ENT) \



#define X(name) name,
typedef enum
{
    LIST_OF_ENTITY_TYPES
        TOTAL_ENTITY_TYPES
}EntityType;

typedef enum
{
    LIST_OF_ENT_SUBTYPES
        TOTAL_ENT_SUBTYPES
}Subtype;

#undef X


#define X(name) [name] = STRINGIFY(name),
char* subtypes_str [] = 
{
    LIST_OF_ENT_SUBTYPES
};
#undef X


i32
str_to_subtype(char* str)
{
    for(i32 i = 0; i < TOTAL_ENT_SUBTYPES; i++)
    {
        if(!strcmp(subtypes_str[i], str))
            return i;
    }
    return -1;
}


typedef struct
{
    
    b32 jump_desired;
    b32 grounded;
    b32 gravity;
    f32 time_moving;
    f32 jump_buffer; //buffer_jumps
    f32 coyate_time; //
    b32 collide_check;
    f32 bb_cooldown;
    f32 trail_cooldown;
    f32 dash_cooldown;
    f32 dash_modifer;
}PlayerInfo;

typedef struct
{
    
    i32 room_id;
    i32 tele_x, tele_y;
    //witch
    i32 health, frame_hit;
    f32 pain_cooldown;
    f32 phase_cooldown;
    f32 bullet_cooldown;
}ColBoxInfo;



typedef struct
{
    f32 emit_cooldown;
}DecorInfo;


typedef struct
{
    b32 talking;
}DialougeInfo;

typedef struct
{
    b32 fade_switch;
}TextyInfo;

typedef struct
{
    f32 respawn_timer;
    f32 witch_timer;
}MiscInfo;

typedef struct
{
    EntityType type;
    Subtype subtype;
    i32 info_id;
    V2 velocity;
    AABB aabb;
    SpriteId sprite_id;
    r32 frame_time;
    u32 frame;
    i32 d_layer;
    V2 initial_pos;
    b32 death_marked;
    f32 alpha;
    f32 scale;
    i32 color;
    i32 shader_id;
    b32 invisible;
    b32 intangible;
    
    union
    {
        PlayerInfo p;
        DecorInfo dec;
        ColBoxInfo c;
        DialougeInfo d;
        TextyInfo t;
        MiscInfo m;
    };
    
    
    
    
}Entity;


#define X(name) void name##_sim(Entity* );
LIST_OF_ENTITY_TYPES
#undef X


#define X(name) [name] = &name##_sim,
void (* entity_sims[TOTAL_ENTITY_TYPES])(Entity*) = 
{
    LIST_OF_ENTITY_TYPES
};
#undef X



void entities_apply(void (*f) (Entity*));



void set_entity_sprite(Entity*, SpriteId );

Entity* add_entity(Entity* e);

Entity* add_temp_entity(f32, f32, SpriteId);

Entity* add_particle_entity(f32 , f32, i32 , i32, f32);
Entity* add_misc_entity(i32);

void death_mark_witch_blocks(Entity* e)
{
    if(e->type == DECOR_ENT && (e->sprite_id == WITCH_BLOCK_SPR || e->sprite_id == WITCH_BLOCK_2_SPR))
        e->death_marked = true;
    else if(e->type == S_COLLISION_ENT && e->subtype == EVIL_WITCH)
        e->death_marked = true;
}


#endif //ENTITY_H
